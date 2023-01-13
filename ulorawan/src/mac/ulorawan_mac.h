/**
 * \file
 *
 * \brief LoraWan MAC function prototypes
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

#ifndef ULORAWAN_MAC_H_
#define ULORAWAN_MAC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ulorawan_mac_frame.h"
#include <stdint.h>

#define ULORAWAN_MAC_BUF_SIZE                                                  \
  255 /**< The maximum size of an lorawan frame buffer. */

#define LORAWAN_MAJOR_R1 0x00

#define ULORAWAN_MTYPE_OFFSET 5

#define ULORAWAN_MAC_ERR_NONE 0
#define ULORAWAN_MAC_ERR_INDEX -1

/**
 * @brief An ulorawan mac frame context.
 *
 * The context used for reading and writing a ulorawan mac frame.
 */
struct ulorawan_mac_frame_context {
  uint8_t buf[ULORAWAN_MAC_BUF_SIZE]; /**< The sequential byte buffer that a
                                              frame is read and written too. */
  uint8_t eof;                        /**< The current end of frame marker. */
};

/**
 * \brief Read a message header from the context.
 *
 * \param context The context to read from.
 * \param fhdr
 *
 * \return Operation status.
 */
int32_t ulorawan_mac_read_fhdr(struct ulorawan_mac_frame_context *const context,
                               const struct ulorawan_mac_fhdr *fhdr);

/**
 * \brief
 *
 * \param context
 * \param fport
 *
 * \return Operation status.
 */
int32_t
ulorawan_mac_read_fport(struct ulorawan_mac_frame_context const *context,
                        uint8_t fport);

/**
 * \brief Write the frame header
 *
 * \param context The context to write to.
 * \param fhdr The frame header to write
 *
 * \return Operation status.
 */
int32_t
ulorawan_mac_write_fhdr(struct ulorawan_mac_frame_context *const context,
                        const struct ulorawan_mac_fhdr const *fhdr);

/**
 * \brief
 *
 * \param context The context to write to.
 * \param fport The fport
 *
 * \return Operation status.
 */
int32_t
ulorawan_mac_write_fport(struct ulorawan_mac_frame_context const *context,
                         uint8_t fport);

/**
 * \brief
 *
 * \param context The context to write to.
 * \param payload
 * \param pld_len
 *
 * \return Operation status.
 */
int32_t
ulorawan_mac_write_frmpayload(struct ulorawan_mac_frame_context const *context,
                              const uint8_t const *payload, uint8_t pld_len);

/**
 * \brief Write a message header to the context
 *
 * \param context The context to write to.
 * \param mhdr The message header to write.
 *
 * \return Operation status.
 */
int32_t
ulorawan_mac_write_mhdr(struct ulorawan_mac_frame_context *const context,
                        const union ulorawan_mac_mhdr const *mhdr);

/**
 * \brief
 *
 * \param context The context to write to.
 * \param mic
 *
 * \return Operation status.
 */
int32_t ulorawan_mac_write_mic(struct ulorawan_mac_frame_context const *context,
                               uint32_t mic);
#ifdef __cplusplus
}
#endif

#endif /* ULORAWAN_MAC_H_ */
