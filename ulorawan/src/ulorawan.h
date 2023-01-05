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

#include "ulorawan_common.h"

#ifdef __cplusplus
extern "C" {
#endif

///< The ulorawan version.
#define ULORAWAN_VERSION 0x01000400

///<
enum ulorawan_error {
  ULORAWAN_ERROR_OK,
  ULORAWAN_ERROR_INIT,
  ULORAWAN_ERROR_STATE,
  ULORAWAN_ERROR_CHANNEL,
};

///< The ulorawan state
enum ulorawan_state {
  ///< The ulorawan stack is initalised
  ULORAWAN_STATE_INIT,
  ///< The ulorawan stack is idle
  ULORAWAN_STATE_IDLE,
};

struct ulorawan_session {
  enum ulorawan_state state;
};

#ifdef TEST
#define SESSION_ACCESS const struct ulorawan_session * const
#else
#define SESSION_ACCESS const struct ulorawan_session *
#endif // TEST

SESSION_ACCESS ulorawan_get_session();

enum ulorawan_error ulorawan_join();

/**
 * \brief Get the ulorawan implementation version
 *
 *
 * \return struct version
 */
union version ulorawan_version();

#ifdef __cplusplus
}
#endif

#endif /* ULORAWAN_H_ */
