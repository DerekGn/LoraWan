/**
 * \file
 *
 * \brief The ulorawan activation prototypes
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

#ifndef ULORAWAN_SECURITY_H_
#define ULORAWAN_SECURITY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//! The end device identifier size
#define ULORAWAN_DEV_EUI_SIZE 8
//! The join server identifier size
#define ULORAWAN_JOIN_EUI_SIZE 8
//! The AES-128 application key size
#define ULORAWAN_APP_KEY_SIZE 16

//! The network session key size
#define ULORAWAN_NWK_S_KEY_SIZE 16
//! The application session key size
#define ULORAWAN_APP_S_KEY_SIZE 16

//! The activation type
enum ulorawan_activation_type {
  //! Activation by personalisation
  ACTIVATION_ABP,
  //! Activation by over the air activation
  ACTIVATION_OTAA
};

//! The device activation
struct ulorawan_device_security {
  //! The activation type
  enum ulorawan_activation_type type;
  union {
    struct ulorawan_activation_abp {
      //! A globally unique end-device identifier
      uint8_t dev_eui[ULORAWAN_DEV_EUI_SIZE];
      //| The Join Server identifier
      uint8_t join_eui[ULORAWAN_JOIN_EUI_SIZE];
      //! An AES-128 application key
      uint8_t app_key[ULORAWAN_APP_KEY_SIZE];
    } otaa;
    struct ulorawan_activation_otaa {
      //! End-device address
      uint32_t dev_addr;
      //! Network session key
      uint8_t nwk_s_key[ULORAWAN_NWK_S_KEY_SIZE];
      //! App session key
      uint8_t app_s_key[ULORAWAN_APP_S_KEY_SIZE];
    } abp;
  } context;
};

#ifdef __cplusplus
}
#endif

#endif /* ULORAWAN_SECURITY_H_ */
