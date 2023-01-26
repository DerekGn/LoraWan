/**
 * \file
 *
 * \brief The HAL prototypes for abstracting the Radio
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

#ifndef RADIO_HAL_H_
#define RADIO_HAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

#define RADIO_HAL_ERR_NONE 0
#define RADIO_HAL_ERR_PARAM -1

//! The radio mode.
enum RADIO_HAL_MODE {
  //! Sleep mode.
  MODE_SLEEP,
  //! Standby mode.
  MODE_STDBY,
  //! Frequency synthesis Tx.
  MODE_FSTX,
  //! Tx mode.
  MODE_TX,
  //! Frequency synthesis Rx.
  MODE_FSRX,
  //! Rx continuous mode.
  MODE_RX_CONT,
  //! Rx single mode.
  MODE_RX_SINGLE,
  //! Rx CAD mode.
  MODE_RX_CAD
};

//! The Radio Irq flags
enum radio_hal_irq_flags {
  //! Radio Rx complete.
  RADIO_HAL_IRQ_RX_DONE,
  //! Radio Tx complete.
  RADIO_HAL_IRQ_TX_DONE,
  //! Radio Rx timed out.
  RADIO_HAL_IRQ_RX_TIMEOUT
};

int32_t radio_hal_configure();

int32_t radio_hal_fifo_read(uint8_t *const buf, size_t *const len);

int32_t radio_hal_fifo_write(const uint8_t *const buf, size_t len);

int32_t radio_hal_set_mode(enum RADIO_HAL_MODE mode);

#ifdef __cplusplus
}
#endif

#endif /* RADIO_HAL_H_ */
