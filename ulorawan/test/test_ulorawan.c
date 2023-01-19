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
#include "mock_osal.h"
#include "mock_nvm_hal.h"
#include "mock_rand_hal.h"
#include "mock_radio_hal.h"
#include "mock_crypto_hal.h"
#include "mock_ulorawan_mac.h"
#include "mock_ulorawan_region.h"

static struct ulorawan_device_security device_security;

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

void test_ulorawan_init_queue_create_error()
{
    // Arrange
    osal_queue_create_ExpectAnyArgsAndReturn(OSAL_ERR_FAIL);
    
    // Act
    uint32_t result = ulorawan_init(DEVICE_CLASS_A, device_security);

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_QUEUE, result);
}

void test_ulorawan_init_radio_mode_error()
{
    // Arrange
    osal_queue_create_ExpectAnyArgsAndReturn(OSAL_ERR_NONE);

    radio_hal_set_mode_ExpectAndReturn(MODE_SLEEP, RADIO_HAL_ERR_PARAM);

    // Act
    uint32_t result = ulorawan_init(DEVICE_CLASS_A, device_security);

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_RADIO, result);
}

void test_ulorawan_init_success()
{
    // Arrange
    osal_queue_create_ExpectAnyArgsAndReturn(OSAL_ERR_NONE);

    radio_hal_set_mode_ExpectAndReturn(MODE_SLEEP, RADIO_HAL_ERR_NONE);

    // Act
    uint32_t result = ulorawan_init(DEVICE_CLASS_B, device_security);

    // Assert
    struct ulorawan_session *session_ptr = ulorawan_get_session();
    
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_NONE, result);
    TEST_ASSERT_EQUAL_HEX8(DEVICE_CLASS_B, session_ptr->class);
}

void test_ulorawan_join_not_init()
{
    // Arrange
    struct ulorawan_session *session_ptr = ulorawan_get_session();
    session_ptr->state = ULORAWAN_STATE_INIT;

    // Act
    uint32_t result = ulorawan_join();

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_INIT, result);
}

void test_ulorawan_join_invalid_activation()
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

void test_ulorawan_join_state_nochannel()
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

void test_ulorawan_join_nonce_error()
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

void test_ulorawan_join_context_error_mhdr()
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

void test_ulorawan_join_context_error_join_req()
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