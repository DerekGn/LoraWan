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
#include "mock_rand_hal.h"
#include "mock_radio_hal.h"
#include "mock_ulorawan_region.h"

static struct ulorawan_device_security device_security;

void test_ulorawan_get_session()
{
    // Arrange
    const struct ulorawan_session *session_ptr;
    
    // Act
    session_ptr = ulorawan_get_session();

    // Assert
    TEST_ASSERT_NOT_NULL(session_ptr);
}

void test_ulorawan_init_rand_init_error()
{
    // Arrange
    rand_hal_init_ExpectAndReturn(RAND_HAL_ERR_INIT);

    // Act
    uint32_t result = ulorawan_init(DEVICE_CLASS_A, device_security);

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_RAND, result);
}

void test_ulorawan_init_queue_create_error()
{
    // Arrange
    osal_queue_create_IgnoreAndReturn(false);
    rand_hal_init_ExpectAndReturn(RAND_HAL_ERR_NONE);

    // Act
    uint32_t result = ulorawan_init(DEVICE_CLASS_A, device_security);

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_QUEUE, result);
}

void test_ulorawan_init_success()
{
    // Arrange
    osal_queue_create_IgnoreAndReturn(true);
    rand_hal_init_ExpectAndReturn(RAND_HAL_ERR_NONE);

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
    ulorawan_region_get_channel_IgnoreAndReturn(NULL);
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
    ulorawan_region_get_channel_ExpectAndReturn(NULL);
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
    ulorawan_region_get_channel_ExpectAndReturn(NULL);
    struct ulorawan_session *session_ptr = ulorawan_get_session();
    session_ptr->state = ULORAWAN_STATE_IDLE;
    session_ptr->security.type = ACTIVATION_OTAA;

    // Act
    uint32_t result = ulorawan_join();

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_NO_CHANNEL, result);
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