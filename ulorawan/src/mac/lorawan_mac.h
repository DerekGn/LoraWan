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

#ifndef LORAWAN_MAC_H_
#define LORAWAN_MAC_H_

/**
 * \brief LoraWan Mac frame types
 */
enum lorawan_mac_frame_type {
  FRAME_TYPE_JOIN_REQ = 0x00,
  FRAME_TYPE_JOIN_ACCEPT = 0x01,
  FRAME_TYPE_DATA_UNCONFIRMED_UP = 0x02,
  FRAME_TYPE_DATA_UNCONFIRMED_DOWN = 0x03,
  FRAME_TYPE_DATA_CONFIRMED_UP = 0x04,
  FRAME_TYPE_DATA_CONFIRMED_DOWN = 0x05,
  FRAME_TYPE_REJOIN = 0x06,
  FRAME_TYPE_PROPRIETARY = 0x07
};

union lorawan_mac_header {};

#endif /* LORAWAN_MAC_H_ */
