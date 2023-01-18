/**
 * \file
 *
 * \brief LoraWan MAC frame types
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

#ifndef ULORAWAN_MAC_FRAME_H_
#define ULORAWAN_MAC_FRAME_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "crosscompile.h"

//! FOpts maximum field size
#define ULORAWAN_MAC_FHDR_F_OPTS_MAX_SIZE 15

//! The size of the globally unique end-device identifier
#define ULORAWAN_MAC_DEV_EUI_SIZE 8

//! The size of the globally unique join-server identifier
#define ULORAWAN_MAC_JOIN_EUI_SIZE 8

/**
 * \brief LoraWan Mac frame control
 */
union __CROSS_ATTR_PACKED ulorawan_mac_fctrl {
  //! The value
  uint8_t value;
  struct __CROSS_ATTR_PACKED {
    //! Frame options
    uint8_t fopts_len : 4;
    //! Frame pending bit for downlink frames or Class B bit on uplink frames
    uint8_t fpending_classb : 1;
    uint8_t ack : 1;
    //! ADR acknowledgment request bit
    uint8_t adr_ack_req : 1;
    //! Adaptive Data Rate
    uint8_t adr : 1;
  } bits;
};

/**
 * \brief LoraWan Mac frame header
 */
struct __CROSS_ATTR_PACKED ulorawan_mac_fhdr {
  //! The device address
  uint32_t dev_addr;
  //! The frame control
  union ulorawan_mac_fctrl fctrl;
  //! The frame counter
  uint16_t fcnt;
  //! The frame options
  uint8_t fopts[ULORAWAN_MAC_FHDR_F_OPTS_MAX_SIZE];
};

/**
 * \brief LoraWan Mac frame types
 */
enum __CROSS_ATTR_PACKED ulorawan_mac_ftype {
  //! A Join Request
  FRAME_TYPE_JOIN_REQ = 0x00,
  //! A Join Accepted
  FRAME_TYPE_JOIN_ACCEPT = 0x01,
  //! Unconfirmed data uplink
  FRAME_TYPE_DATA_UNCONFIRMED_UP = 0x02,
  //! Unconfirmed data downlink
  FRAME_TYPE_DATA_UNCONFIRMED_DOWN = 0x03,
  //! Confirmed data uplink
  FRAME_TYPE_DATA_CONFIRMED_UP = 0x04,
  //! confirmed data downlink
  FRAME_TYPE_DATA_CONFIRMED_DOWN = 0x05,
  //! RFU
  FRAME_TYPE_RFU = 0x06,
  //! Proprietary
  FRAME_TYPE_PROPRIETARY = 0x07
};

/**
 * \brief LoraWan Mac join request
 */
struct __CROSS_ATTR_PACKED ulorawan_mac_join_req {
  //! The JoinEUI
  uint8_t join_eui[ULORAWAN_MAC_JOIN_EUI_SIZE];
  //! The DevEUI
  uint8_t device_eui[ULORAWAN_MAC_JOIN_EUI_SIZE];
  //! The device nonce
  uint16_t device_nonce;
};

/**
 * \brief LoraWan Mac header
 */
union __CROSS_ATTR_PACKED ulorawan_mac_mhdr {
  //! The value
  uint8_t value;
  struct __CROSS_ATTR_PACKED {
    //! The major version of the frame format of LoraWan layer specification
    uint8_t major : 2;
    //! Reserved
    uint8_t rfu : 3;
    //! The frame type
    enum ulorawan_mac_ftype ftype : 3;
  } bits;
};

#ifdef __cplusplus
}
#endif

#endif /* ULORAWAN_MAC_FRAME_H_ */
