/**
 * \file
 *
 * \brief The ulorawan irq function implementations
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

#include <stdint.h>

#include "log_hal.h"
#include "radio_hal.h"
#include "timer_hal.h"
#include "ulorawan_downlink.h"
#include "ulorawan_error_codes.h"
#include "ulorawan_session.h"

int32_t ulorawan_radio_irq_handler(struct ulorawan_session *const session,
                                   enum radio_hal_irq_flags flags) {
  log_hal_log_debug("Session state [0x%02X] flags: [0x%02X]", session->state,
                    flags);
  int32_t result = ULORAWAN_ERR_NONE;

  switch (session->state) {
  case ULORAWAN_STATE_FAULT:
  case ULORAWAN_STATE_INIT:
  case ULORAWAN_STATE_IDLE:
    log_hal_log_error("Invalid session state");
    result = ULORAWAN_ERR_STATE;
    break;
  case ULORAWAN_STATE_TX:
    if (flags & RADIO_HAL_IRQ_TX_DONE) {
      log_hal_log_debug("TX state TX done");

      if (timer_hal_start(TIMER0, session->region_params.rx_delay_1) !=
              TIMER_HAL_ERR_NONE ||
          timer_hal_start(TIMER1, session->region_params.rx_delay_2) !=
              TIMER_HAL_ERR_NONE) {
        log_hal_log_error("Failed to start TIMER0 and TIMER1");
        result = ULORAWAN_ERR_TIMER;
        session->state = ULORAWAN_STATE_FAULT;
      }

      session->state = ULORAWAN_STATE_RX1;
    }
    break;
  case ULORAWAN_STATE_RX1:
    if (flags & RADIO_HAL_IRQ_RX_TIMEOUT) {
      session->state = ULORAWAN_STATE_RX2;
      log_hal_log_debug("RX1 state RX timeout");
      // TODO Configure Radio
    } else if (flags & RADIO_HAL_IRQ_RX_DONE) {
      log_hal_log_debug("RX1 state RX done");

      if (timer_hal_stop(TIMER1) != TIMER_HAL_ERR_NONE) {
        log_hal_log_error("Failed to stop TIMER1");
        result = ULORAWAN_ERR_TIMER;
        session->state = ULORAWAN_STATE_FAULT;
      } else {
        result = ulorawan_downlink_handler(session);
        if (result == ULORAWAN_ERR_NONE) {
          session->state = ULORAWAN_STATE_IDLE;
        }
      }
    }
    break;
  case ULORAWAN_STATE_RX2:
    if (flags & RADIO_HAL_IRQ_RX_TIMEOUT) {
      log_hal_log_debug("RX2 state RX timeout");
      session->state = ULORAWAN_STATE_IDLE;
    } else if (flags & RADIO_HAL_IRQ_RX_DONE) {
      log_hal_log_debug("RX2 state RX done");
      result = ulorawan_downlink_handler(session);
      if (result == ULORAWAN_ERR_NONE) {
        session->state = ULORAWAN_STATE_IDLE;
      }
    }
    break;
  default:
    break;
  }

  return result;
}
