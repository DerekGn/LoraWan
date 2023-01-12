/**
 * \file
 *
 * \brief LoraWan MAC function implementations
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
#include <string.h>

#include "ulorawan_mac.h"
#include "ulorawan_mac_frame.h"

int32_t
ulorawan_mac_write_fhdr(struct ulorawan_mac_frame_context *const context,
                        const struct ulorawan_mac_fhdr const *fhdr) {
  if (context->eof != sizeof(union ulorawan_mac_mhdr)) {
    return ULORAWAN_MAC_ERR_INDEX;
  }

  uint8_t i = sizeof(struct ulorawan_mac_fhdr);
  memcpy(context->buf + context->eof, fhdr, i);
  context->eof += i;

  return ULORAWAN_MAC_ERR_NONE;
}

int32_t
ulorawan_mac_write_mhdr(struct ulorawan_mac_frame_context *const context,
                        const union ulorawan_mac_mhdr const *mhdr) {
  if (context->eof != 0) {
    return ULORAWAN_MAC_ERR_INDEX;
  }

  context->eof = sizeof(union ulorawan_mac_mhdr);
  memcpy(context->buf, mhdr, context->eof);

  return ULORAWAN_MAC_ERR_NONE;
}
