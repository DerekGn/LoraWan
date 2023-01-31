/**
 * \file
 *
 * \brief 
 *
 * Copyright (c) 2023 Derek Goslin
 *
 * @author Derek Goslin
 *
 * \page License
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "unity.h"
#include "ulorawan.h"
#include "ulorawan_events.h"
#include "ulorawan_error_codes.h"

#include "mock_nvm_hal.h"
#include "mock_rand_hal.h"
#include "mock_radio_hal.h"
#include "mock_crypto_hal.h"
#include "mock_osal_queue.h"
#include "mock_ulorawan_mac.h"
#include "mock_ulorawan_irq.h"
#include "mock_ulorawan_region.h"

TEST_FILE("log_console.c")

static struct ulorawan_device_security device_security;

static void ulorawan_task_timer_expire(enum ulorawan_state state, enum timer_hal_timer timer);

void setUp(void) {}

void tearDown(void) {}

void test_ulorawan_get_session()
{
    // Arrange
    const struct ulorawan_session *session_ptr;
    
    // Act
    session_ptr = ulorawan_get_session();

    // Assert
    TEST_ASSERT_NOT_NULL(session_ptr);
}

void test_ulorawan_init_error_queue()
{
    // Arrange
    osal_queue_create_ExpectAnyArgsAndReturn(OSAL_QUEUE_ERR_FAIL);
    
    // Act
    uint32_t result = ulorawan_init(DEVICE_CLASS_A, device_security);

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_QUEUE, result);
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_STATE_FAULT, ulorawan_get_session()->state);
}

void test_ulorawan_init_error_mode()
{
    // Arrange
    osal_queue_create_ExpectAnyArgsAndReturn(OSAL_QUEUE_ERR_NONE);

    radio_hal_set_mode_ExpectAndReturn(MODE_SLEEP, RADIO_HAL_ERR_PARAM);

    // Act
    uint32_t result = ulorawan_init(DEVICE_CLASS_A, device_security);

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_RADIO, result);
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_STATE_FAULT, ulorawan_get_session()->state);
}

void test_ulorawan_init_error_region()
{
    // Arrange
    osal_queue_create_ExpectAnyArgsAndReturn(OSAL_QUEUE_ERR_NONE);
    
    radio_hal_set_mode_ExpectAndReturn(MODE_SLEEP, RADIO_HAL_ERR_NONE);

    ulorawan_region_init_params_ExpectAnyArgsAndReturn(ULORAWAN_REGION_ERR_FAIL);

    // Act
    uint32_t result = ulorawan_init(DEVICE_CLASS_A, device_security);

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_REGION, result);
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_STATE_FAULT, ulorawan_get_session()->state);
}

void test_ulorawan_init_success()
{
    // Arrange
    osal_queue_create_ExpectAnyArgsAndReturn(OSAL_QUEUE_ERR_NONE);

    radio_hal_set_mode_ExpectAndReturn(MODE_SLEEP, RADIO_HAL_ERR_NONE);

    ulorawan_region_init_params_ExpectAnyArgsAndReturn(ULORAWAN_REGION_ERR_NONE);

    // Act
    uint32_t result = ulorawan_init(DEVICE_CLASS_B, device_security);

    // Assert
    struct ulorawan_session *session_ptr = ulorawan_get_session();
    
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_NONE, result);
    TEST_ASSERT_EQUAL_HEX8(DEVICE_CLASS_B, session_ptr->class);
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_STATE_IDLE, ulorawan_get_session()->state);
}

void test_ulorawan_join_error_init()
{
    // Arrange
    struct ulorawan_session *session_ptr = ulorawan_get_session();
    session_ptr->state = ULORAWAN_STATE_INIT;

    // Act
    uint32_t result = ulorawan_join();

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_INIT, result);
}

void test_ulorawan_join_error_activation()
{
    // Arrange
    struct ulorawan_session *session_ptr = ulorawan_get_session();
    session_ptr->state = ULORAWAN_STATE_IDLE;
    session_ptr->security.type = ACTIVATION_ABP;

    // Act
    uint32_t result = ulorawan_join();

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_ACTIVATION, result);
}

void test_ulorawan_join_error_nochannel()
{
    // Arrange
    struct ulorawan_session *session_ptr = ulorawan_get_session();
    session_ptr->state = ULORAWAN_STATE_IDLE;
    session_ptr->security.type = ACTIVATION_OTAA;

    struct ulorawan_channel channel;

    ulorawan_region_get_channel_ExpectAnyArgsAndReturn(ULORAWAN_REGION_ERR_FAIL);

    // Act
    uint32_t result = ulorawan_join();

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_NO_CHANNEL, result);
}

void test_ulorawan_join_error_nonce()
{
    // Arrange
    struct ulorawan_session *session_ptr = ulorawan_get_session();
    session_ptr->state = ULORAWAN_STATE_IDLE;
    session_ptr->security.type = ACTIVATION_OTAA;

    struct ulorawan_channel channel;
    ulorawan_region_get_channel_ExpectAnyArgsAndReturn(ULORAWAN_REGION_ERR_NONE);

    uint16_t nonce;
    nvm_hal_read_join_nonce_ExpectAnyArgsAndReturn(NVM_HAL_ERR_FAIL);

    // Act
    uint32_t result = ulorawan_join();

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_NVM, result);
}

void test_ulorawan_join_error_mhdr()
{
    // Arrange
    struct ulorawan_session *session_ptr = ulorawan_get_session();
    session_ptr->state = ULORAWAN_STATE_IDLE;
    session_ptr->security.type = ACTIVATION_OTAA;

    struct ulorawan_channel channel;
    ulorawan_region_get_channel_ExpectAnyArgsAndReturn(ULORAWAN_REGION_ERR_NONE);

    uint16_t nonce;
    nvm_hal_read_join_nonce_ExpectAnyArgsAndReturn(NVM_HAL_ERR_NONE);

    ulorawan_mac_write_mhdr_ExpectAnyArgsAndReturn(ULORAWAN_MAC_ERR_INDEX);

    // Act
    uint32_t result = ulorawan_join();

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_CTX, result);
}

void test_ulorawan_join_error_join_req()
{
    // Arrange
    struct ulorawan_session *session_ptr = ulorawan_get_session();
    session_ptr->state = ULORAWAN_STATE_IDLE;
    session_ptr->security.type = ACTIVATION_OTAA;

    struct ulorawan_channel channel;
    ulorawan_region_get_channel_ExpectAnyArgsAndReturn(ULORAWAN_REGION_ERR_NONE);

    uint16_t nonce;
    nvm_hal_read_join_nonce_ExpectAnyArgsAndReturn(NVM_HAL_ERR_NONE);

    ulorawan_mac_write_mhdr_ExpectAnyArgsAndReturn(ULORAWAN_MAC_ERR_NONE);

    ulorawan_mac_write_join_req_IgnoreAndReturn(ULORAWAN_MAC_ERR_INDEX);

    // Act
    uint32_t result = ulorawan_join();

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_CTX, result);
}

void test_ulorawan_join_cmac_error()
{
    // Arrange
    struct ulorawan_session *session_ptr = ulorawan_get_session();
    session_ptr->state = ULORAWAN_STATE_IDLE;
    session_ptr->security.type = ACTIVATION_OTAA;

    struct ulorawan_channel channel;
    ulorawan_region_get_channel_IgnoreAndReturn(ULORAWAN_REGION_ERR_NONE);

    uint16_t nonce;
    nvm_hal_read_join_nonce_ExpectAnyArgsAndReturn(NVM_HAL_ERR_NONE);

    ulorawan_mac_write_mhdr_ExpectAnyArgsAndReturn(ULORAWAN_MAC_ERR_NONE);

    ulorawan_mac_write_join_req_ExpectAnyArgsAndReturn(ULORAWAN_MAC_ERR_NONE);
    
    //crypto_hal_aes_cmac_ExpectAndReturn(CRYPTO_HAL_ERR_FAIL);

    // Act
    uint32_t result = ulorawan_join();

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_CTX, result);
}

void test_ulorawan_radio_irq_error_init()
{
    // Arrange
    struct ulorawan_session *session_ptr = ulorawan_get_session();
    session_ptr->state = ULORAWAN_STATE_INIT;

    // Act
    uint32_t result = ulorawan_radio_irq(RADIO_HAL_IRQ_RX_DONE);

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_INIT, result);
}

void test_ulorawan_radio_irq_success()
{
    // Arrange
    struct ulorawan_session *session_ptr = ulorawan_get_session();
    session_ptr->state = ULORAWAN_STATE_IDLE;

    osal_queue_send_ExpectAnyArgsAndReturn(OSAL_QUEUE_ERR_NONE);

    // Act
    uint32_t result = ulorawan_radio_irq(RADIO_HAL_IRQ_RX_DONE);

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_NONE, result);
}

void test_ulorawan_task_error_init()
{
    // Arrange
    struct ulorawan_session *session_ptr = ulorawan_get_session();
    session_ptr->state = ULORAWAN_STATE_INIT;

    // Act
    uint32_t result = ulorawan_task();

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_INIT, result);
}

void test_ulorawan_task_error_queue()
{
    // Arrange
    struct ulorawan_session *session_ptr = ulorawan_get_session();
    session_ptr->state = ULORAWAN_STATE_IDLE;

    osal_queue_empty_IgnoreAndReturn(false);
    osal_queue_empty_IgnoreAndReturn(true);

    osal_queue_receive_ExpectAnyArgsAndReturn(OSAL_QUEUE_ERR_FAIL);

    // Act
    uint32_t result = ulorawan_task();

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_QUEUE, result);
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_STATE_FAULT, ulorawan_get_session()->state);
}

void test_ulorawan_task_timer_expire_timer0()
{
    ulorawan_task_timer_expire(ULORAWAN_STATE_RX1, TIMER0);
}

void test_ulorawan_task_timer_expire_timer1()
{
    ulorawan_task_timer_expire(ULORAWAN_STATE_RX2, TIMER1);
}

void test_ulorawan_task_radio_irq()
{
    // Arrange
    struct ulorawan_session *session_ptr = ulorawan_get_session();
    session_ptr->state = ULORAWAN_STATE_IDLE;

    struct ulorawan_event event;
    event.type = EVENT_TYPE_RADIO_IRQ;
    
    osal_queue_empty_IgnoreAndReturn(false);
    osal_queue_empty_IgnoreAndReturn(true);
    
    osal_queue_receive_ExpectAnyArgsAndReturn(OSAL_QUEUE_ERR_NONE);
    
    osal_queue_receive_ReturnMemThruPtr_data(&event, sizeof(struct ulorawan_event ));
    
    osal_queue_receive_IgnoreArg_queue();

    ulorawan_radio_irq_handler_ExpectAnyArgsAndReturn(ULORAWAN_ERR_NONE);

    // Act
    uint32_t result = ulorawan_task();

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_NONE, result);
}

void test_ulorawan_timer_expired_error_init()
{
    // Arrange
    struct ulorawan_session *session_ptr = ulorawan_get_session();
    session_ptr->state = ULORAWAN_STATE_INIT;

    // Act
    uint32_t result = ulorawan_timer_expired(TIMER0);

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_INIT, result);
}

void test_ulorawan_timer_expired_error_queue()
{
    // Arrange
    struct ulorawan_session *session_ptr = ulorawan_get_session();
    session_ptr->state = ULORAWAN_STATE_IDLE;

    osal_queue_send_ExpectAnyArgsAndReturn(OSAL_QUEUE_ERR_FAIL);

    // Act
    uint32_t result = ulorawan_timer_expired(TIMER0);

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_QUEUE, result);
}

void test_ulorawan_timer_expired_success()
{
    // Arrange
    struct ulorawan_session *session_ptr = ulorawan_get_session();
    session_ptr->state = ULORAWAN_STATE_IDLE;

    osal_queue_send_ExpectAnyArgsAndReturn(OSAL_QUEUE_ERR_NONE);

    // Act
    uint32_t result = ulorawan_timer_expired(TIMER0);

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_NONE, result);
}

void test_ulorawan_version()
{
    //Act
    union version v = ulorawan_version();

    // Assert
    TEST_ASSERT_EQUAL_HEX8(1, v.fields.major);
    TEST_ASSERT_EQUAL_HEX8(0, v.fields.minor);
    TEST_ASSERT_EQUAL_HEX8(4, v.fields.patch);
    TEST_ASSERT_EQUAL_HEX8(0, v.fields.revision);
}

void ulorawan_task_timer_expire(enum ulorawan_state state, enum timer_hal_timer timer)
{
    // Arrange
    struct ulorawan_session *session_ptr = ulorawan_get_session();
    session_ptr->state = state;

    struct ulorawan_event event;
    event.type = EVENT_TYPE_TIMER_EXPIRE;
    event.data.timer = timer;

    osal_queue_empty_IgnoreAndReturn(false);
    osal_queue_empty_IgnoreAndReturn(true);
    
    osal_queue_receive_ExpectAnyArgsAndReturn(OSAL_QUEUE_ERR_NONE);
    
    osal_queue_receive_ReturnMemThruPtr_data(&event, sizeof(struct ulorawan_event ));
    
    osal_queue_receive_IgnoreArg_queue();

    radio_hal_set_mode_ExpectAndReturn(MODE_RX_SINGLE, RADIO_HAL_ERR_NONE);

    // Act
    uint32_t result = ulorawan_task();

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_NONE, result);
}