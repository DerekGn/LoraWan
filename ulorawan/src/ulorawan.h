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

#ifndef ULORAWAN_H_
#define ULORAWAN_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief ulorawan state enumeration
 *
 * The list of possible ulorawan states.
 */
enum ulorawan_state {
  ULORAWAN_STATE_NOT_INIT,
  ULORAWAN_STATE_IDLE,
  ULORAWAN_STATE_TX,
  ULORAWAN_STATE_RX1,
  ULORAWAN_STATE_RX2,
};

/**
 * \name ulorawan functions
 */
//@{
void ulorawan_init();

/**
 * \brief Get the current ulorawan state
 *
 *
 * \return enum ulorawan_state The current active ulorawan state
 */
enum ulorawan_state ulorawan_get_state();

void ulorawan_task();

void ulorawan_join();
//@}

#ifdef __cplusplus
}
#endif

#endif /* ULORAWAN_H_ */
