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

#define BYTE_0(value)                                                          \
  ((uint8_t)value & 0xff) /**< Mask byte 0 from a value. \ \ \ \ \                                                                             \
                           */
#define BYTE_1(value)                                                          \
  ((uint8_t)(value >> 8) & 0xff) /**< Mask byte 1 from a value. */
#define BYTE_2(value)                                                          \
  ((uint8_t)(value >> 16) & 0xff) /**< Mask byte 2 from a value. */
#define BYTE_3(value)                                                          \
  ((uint8_t)(value >> 24) & 0xff) /**< Mask byte 3 from a value. */

int32_t ulorawan_mac_read_fhdr(struct ulorawan_mac_frame_context *const ctx,
                               struct ulorawan_mac_fhdr *const fhdr) {
  if (ctx->eof != sizeof(union ulorawan_mac_mhdr)) {
    return ULORAWAN_MAC_ERR_INDEX;
  }

  fhdr->dev_addr = ctx->buf[ctx->eof++];
  fhdr->dev_addr |= ctx->buf[ctx->eof++] << 8;
  fhdr->dev_addr |= ctx->buf[ctx->eof++] << 16;
  fhdr->dev_addr |= ctx->buf[ctx->eof++] << 24;

  fhdr->fctrl.value = ctx->buf[ctx->eof++];

  fhdr->fcnt = ctx->buf[ctx->eof++];
  fhdr->fcnt |= ctx->buf[ctx->eof++] << 8;

  for (size_t i = 0; i < fhdr->fctrl.bits.fopts_len; i++) {
    fhdr->fopts[i] = ctx->buf[ctx->eof++];
  }

  return ULORAWAN_MAC_ERR_NONE;
}

int32_t ulorawan_mac_read_fport(struct ulorawan_mac_frame_context *const ctx,
                                uint8_t *const fport) {
  if (ctx->eof <
      sizeof(union ulorawan_mac_mhdr) + sizeof(struct ulorawan_mac_fhdr)) {
    return ULORAWAN_MAC_ERR_INDEX;
  }

  *fport = ctx->buf[ctx->eof++];

  return ULORAWAN_MAC_ERR_NONE;
}

int32_t
ulorawan_mac_read_frmpayload(struct ulorawan_mac_frame_context *const ctx,
                             uint8_t *const payload, size_t *const len) {
  if (ctx->eof <
      sizeof(union ulorawan_mac_mhdr) + sizeof(struct ulorawan_mac_fhdr)) {
    return ULORAWAN_MAC_ERR_INDEX;
  }

  memcpy(payload, &ctx->buf[ctx->eof], *len);
  ctx->eof += *len;

  return ULORAWAN_MAC_ERR_NONE;
}

int32_t ulorawan_mac_read_mhdr(struct ulorawan_mac_frame_context *const ctx,
                               union ulorawan_mac_mhdr *const mhdr) {
  if (ctx->eof != 0) {
    return ULORAWAN_MAC_ERR_INDEX;
  }

  mhdr->value = ctx->buf[ctx->eof++];

  return ULORAWAN_MAC_ERR_NONE;
}

int32_t ulorawan_mac_write_fhdr(struct ulorawan_mac_frame_context *const ctx,
                                const struct ulorawan_mac_fhdr const *fhdr) {
  if (ctx->eof != sizeof(union ulorawan_mac_mhdr)) {
    return ULORAWAN_MAC_ERR_INDEX;
  }

  // Ensure little endian order
  ctx->buf[ctx->eof++] = BYTE_0(fhdr->dev_addr);
  ctx->buf[ctx->eof++] = BYTE_1(fhdr->dev_addr);
  ctx->buf[ctx->eof++] = BYTE_2(fhdr->dev_addr);
  ctx->buf[ctx->eof++] = BYTE_3(fhdr->dev_addr);

  ctx->buf[ctx->eof++] = fhdr->fctrl.value;
  ctx->buf[ctx->eof++] = BYTE_0(fhdr->fcnt);
  ctx->buf[ctx->eof++] = BYTE_1(fhdr->fcnt);

  for (size_t i = 0; i < fhdr->fctrl.bits.fopts_len; i++) {
    ctx->buf[ctx->eof++] = fhdr->fopts[i];
  }

  return ULORAWAN_MAC_ERR_NONE;
}

int32_t ulorawan_mac_write_fport(struct ulorawan_mac_frame_context *const ctx,
                                 uint8_t fport) {
  if (ctx->eof <
      sizeof(union ulorawan_mac_mhdr) + sizeof(struct ulorawan_mac_fhdr)) {
    return ULORAWAN_MAC_ERR_INDEX;
  }

  ctx->buf[ctx->eof++] = fport;

  return ULORAWAN_MAC_ERR_NONE;
}

int32_t
ulorawan_mac_write_frmpayload(struct ulorawan_mac_frame_context *const ctx,
                              const uint8_t const *payload, size_t len) {

  memcpy(&ctx->buf[ctx->eof], payload, len);
  ctx->eof += len;

  return ULORAWAN_MAC_ERR_NONE;
}

int32_t
ulorawan_mac_write_join_req(struct ulorawan_mac_frame_context *const ctx,
                            const struct ulorawan_mac_join_req *const req) {
  if (ctx->eof != sizeof(union ulorawan_mac_mhdr)) {
    return ULORAWAN_MAC_ERR_INDEX;
  }

  for (size_t i = 0; i < ULORAWAN_MAC_JOIN_EUI_SIZE; i++) {
    ctx->buf[ctx->eof++] = req->join_eui[i];
  }

  for (size_t i = 0; i < ULORAWAN_MAC_DEV_EUI_SIZE; i++) {
    ctx->buf[ctx->eof++] = req->device_eui[i];
  }

  ctx->buf[ctx->eof++] = BYTE_0(req->device_nonce);
  ctx->buf[ctx->eof++] = BYTE_1(req->device_nonce);

  return ULORAWAN_MAC_ERR_NONE;
}

int32_t ulorawan_mac_write_mhdr(struct ulorawan_mac_frame_context *const ctx,
                                const union ulorawan_mac_mhdr *const mhdr) {
  if (ctx->eof != 0) {
    return ULORAWAN_MAC_ERR_INDEX;
  }

  ctx->buf[ctx->eof++] = mhdr->value;

  return ULORAWAN_MAC_ERR_NONE;
}

int32_t ulorawan_mac_write_mic(struct ulorawan_mac_frame_context *const ctx,
                               uint32_t mic) {
  ctx->buf[ctx->eof++] = BYTE_0(mic);
  ctx->buf[ctx->eof++] = BYTE_1(mic);
  ctx->buf[ctx->eof++] = BYTE_2(mic);
  ctx->buf[ctx->eof++] = BYTE_3(mic);

  return ULORAWAN_MAC_ERR_NONE;
}
