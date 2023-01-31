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
#include "ulorawan_irq.h"
#include "ulorawan_session.h"
#include "ulorawan_error_codes.h"

#include "mock_timer_hal.h"
#include "mock_ulorawan_downlink.h"

TEST_FILE("log_console.c")

static void ulorawan_radio_irq_handler_tx_state_timer_test(
    enum timer_hal_timer timer,
    uint32_t interval,
    int32_t timer_return,
    int32_t expected_result);

void setUp(void) {}

void tearDown(void) {}

void test_ulorawan_radio_irq_handler_invalid_state()
{
    // Arrange
    struct ulorawan_session session;
    session.state = ULORAWAN_STATE_IDLE;
    
    // Act
    int32_t result = ulorawan_radio_irq_handler(&session, RADIO_HAL_IRQ_RX_DONE);

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_STATE, result);
}

void test_ulorawan_radio_irq_handler_state_tx_timer0_error()
{
    ulorawan_radio_irq_handler_tx_state_timer_test(TIMER0, 100, TIMER_HAL_ERR_FAIL, ULORAWAN_ERR_TIMER);
}

void test_ulorawan_radio_irq_handler_state_tx_timer1_error()
{
    ulorawan_radio_irq_handler_tx_state_timer_test(TIMER0, 100, TIMER_HAL_ERR_FAIL, ULORAWAN_ERR_TIMER);
}

void test_ulorawan_radio_irq_handler_state_tx_success()
{
    // Arrange
    struct ulorawan_session session;
    session.state = ULORAWAN_STATE_TX;
    session.region_params.rx_delay_1 = 100;
    session.region_params.rx_delay_2 = 200;

    timer_hal_start_ExpectAndReturn(TIMER0, 100, TIMER_HAL_ERR_NONE);
    timer_hal_start_ExpectAndReturn(TIMER1, 200, TIMER_HAL_ERR_NONE);

    // Act
    int32_t result = ulorawan_radio_irq_handler(&session, RADIO_HAL_IRQ_TX_DONE);

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_NONE, result);
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_STATE_RX1, session.state);
}

void test_ulorawan_radio_irq_handler_state_rx1_timer_error()
{
    // Arrange
    struct ulorawan_session session;
    session.state = ULORAWAN_STATE_RX1;
    
    timer_hal_stop_ExpectAndReturn(TIMER1, TIMER_HAL_ERR_FAIL);

    // Act
    int32_t result = ulorawan_radio_irq_handler(&session, RADIO_HAL_IRQ_RX_DONE);

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_TIMER, result);
}

void test_ulorawan_radio_irq_handler_state_rx1_downlink_error()
{
    // Arrange
    struct ulorawan_session session;
    session.state = ULORAWAN_STATE_RX1;

    timer_hal_stop_ExpectAnyArgsAndReturn(TIMER_HAL_ERR_NONE);

    ulorawan_downlink_handler_ExpectAndReturn(NULL, ULORAWAN_ERR_PARAMS);
    ulorawan_downlink_handler_IgnoreArg_session();

    // Act
    int32_t result = ulorawan_radio_irq_handler(&session, RADIO_HAL_IRQ_RX_DONE);

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_PARAMS, result);
}

void test_ulorawan_radio_irq_handler_state_rx1_success()
{
    // Arrange
    struct ulorawan_session session;
    session.state = ULORAWAN_STATE_RX1;

    timer_hal_stop_ExpectAnyArgsAndReturn(TIMER_HAL_ERR_NONE);

    ulorawan_downlink_handler_ExpectAndReturn(NULL, ULORAWAN_ERR_NONE);
    ulorawan_downlink_handler_IgnoreArg_session();

    // Act
    int32_t result = ulorawan_radio_irq_handler(&session, RADIO_HAL_IRQ_RX_DONE);

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_NONE, result);
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_STATE_IDLE, session.state);
}

void test_ulorawan_radio_irq_handler_state_rx2_timeout()
{
    // Arrange
    struct ulorawan_session session;
    session.state = ULORAWAN_STATE_RX2;

    // Act
    int32_t result = ulorawan_radio_irq_handler(&session, RADIO_HAL_IRQ_RX_TIMEOUT);

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_NONE , result);
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_STATE_IDLE, session.state);
}

void test_ulorawan_radio_irq_handler_state_rx2_downlink_error()
{
    // Arrange
    struct ulorawan_session session;
    session.state = ULORAWAN_STATE_RX2;

    ulorawan_downlink_handler_ExpectAndReturn(NULL, ULORAWAN_ERR_PARAMS);
    ulorawan_downlink_handler_IgnoreArg_session();

    // Act
    int32_t result = ulorawan_radio_irq_handler(&session, RADIO_HAL_IRQ_RX_DONE);

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_PARAMS, result);
}

void test_ulorawan_radio_irq_handler_state_rx2_success()
{
    // Arrange
    struct ulorawan_session session;
    session.state = ULORAWAN_STATE_RX2;

    ulorawan_downlink_handler_ExpectAndReturn(NULL, ULORAWAN_ERR_NONE);
    ulorawan_downlink_handler_IgnoreArg_session();

    // Act
    int32_t result = ulorawan_radio_irq_handler(&session, RADIO_HAL_IRQ_RX_DONE);

    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_ERR_NONE, result);
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_STATE_IDLE, session.state);
}

void ulorawan_radio_irq_handler_tx_state_timer_test(
    enum timer_hal_timer timer,
    uint32_t interval,
    int32_t timer_result,
    int32_t expected_result)
{
    // Arrange
    struct ulorawan_session session;
    session.state = ULORAWAN_STATE_TX;
    session.region_params.rx_delay_1 = interval;
    session.region_params.rx_delay_2 = interval;

    timer_hal_start_ExpectAndReturn(timer, interval, timer_result);

    // Act
    int32_t result = ulorawan_radio_irq_handler(&session, RADIO_HAL_IRQ_TX_DONE);

    // Assert
    TEST_ASSERT_EQUAL_HEX8(expected_result, result);
}