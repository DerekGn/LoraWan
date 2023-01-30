/**
 * \file
 *
 * \brief The ulorawan session prototypes
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

#ifndef ULORAWAN_SESSION_H_
#define ULORAWAN_SESSION_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ulorawan_mac.h"
#include "ulorawan_region.h"
#include "ulorawan_security.h"

//! The ulorawan state
enum ulorawan_state {
  //! The ulorawan stack is initalised
  ULORAWAN_STATE_INIT,
  //! The ulorawan stack is idle
  ULORAWAN_STATE_IDLE,
  //! The ulorawan stack is transmitting
  ULORAWAN_STATE_TX,
  //! The ulorawan stack is in first receive window state
  ULORAWAN_STATE_RX1,
  //! The ulorawan stack is in second receive window state
  ULORAWAN_STATE_RX2
};

//! The active lorawan class
enum ulorawan_device_class {
  //! A class A device
  DEVICE_CLASS_A,
  //! A class B device
  DEVICE_CLASS_B,
  //! A class C device
  DEVICE_CLASS_C
};

//! The ulorawan session
struct ulorawan_session {
  //! The last frame size
  size_t frame_size;
  //! The last frame
  uint8_t frame[ULORAWAN_MAC_BUF_SIZE];
  //! The current session state
  enum ulorawan_state state;
  //! The device class
  enum ulorawan_device_class class;
  //! The device security context
  struct ulorawan_device_security security;
  //! The region parameters
  struct ulorawan_region_params region_params;
};

#ifdef __cplusplus
}
#endif

#endif /* ULORAWAN_SESSION_H_ */
