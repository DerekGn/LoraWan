/**
 * \file
 *
 * \brief 
 *
 * Copyright (c) 2022 Derek Goslin
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
#include "ulorawan_err_codes.h"
#include "mock_rand_hal.h"
#include "mock_radio_hal.h"
#include "mock_ulorawan_region.h"

static void radio_irq_callback(const enum radio_hal_irq_flags irq_flags)
{
}

void test_ulorawan_get_session()
{
    // Arrange
    const struct ulorawan_session *session_ptr;
    
    // Act
    session_ptr = ulorawan_get_session();

    // Assert
    TEST_ASSERT_NOT_NULL(session_ptr);
}

void test_ulorawan_init_cb_param_error()
{
    // Arrange

    // Act
    uint32_t result = ulorawan_init(NULL);

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_PARAMS, result);
}

void test_ulorawan_init_rand_init_error()
{
    // Arrange
    rand_hal_init_ExpectAndReturn(RAND_HAL_ERR_INIT);

    // Act
    uint32_t result = ulorawan_init(radio_irq_callback);

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_RAND, result);
}

void test_ulorawan_init_radio_init_error()
{
    // Arrange
    rand_hal_init_ExpectAndReturn(RAND_HAL_ERR_NONE);
    radio_hal_irq_register_ExpectAndReturn(radio_irq_callback, RADIO_HAL_ERROR_PARAM);

    // Act
    uint32_t result = ulorawan_init(radio_irq_callback);

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_RADIO, result);
}

void test_ulorawan_init()
{
    // Arrange
    rand_hal_init_ExpectAndReturn(RAND_HAL_ERR_NONE);
    radio_hal_irq_register_ExpectAndReturn(radio_irq_callback, 0);

    // Act
    uint32_t result = ulorawan_init(radio_irq_callback);

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_NONE, result);
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

void test_ulorawan_join_state_nochannel()
{
    // Arrange
    ulorawan_region_get_channel_ExpectAndReturn(NULL);
    struct ulorawan_session *session_ptr = ulorawan_get_session();
    session_ptr->state = ULORAWAN_STATE_IDLE;

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