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

#define ULORAWAN_MAC_MTYPE_OFFSET 5

#define ULORAWAN_MHDR_INIT(_type, _version)         \
  { _type << ULORAWAN_MAC_MTYPE_OFFSET | _version }

/**
 * @brief An ulorawan mac frame context.
 *
 * The context used for reading and writing a ulorawan mac frame.
 */
struct ulorawan_mac_frame_context {
  uint8_t buf[ULORAWAN_MAC_BUF_SIZE]; /**< The sequential byte buffer that a
                                              frame is read and written too. */
  size_t eof;                         /**< The current end of frame marker. */
};

/**
 * \brief Read a message header from the context.
 *
 * \param[in] ctx The context to read from.
 * \param[out] fhdr The frame header to read.
 *
 * \return Operation status.
 * \retval ULORAWAN_ERR_NONE Operation executed successfully.
 * \retval ULORAWAN_MAC_ERR_INDEX The eof index is invalid.
 */
int32_t ulorawan_mac_read_fhdr(struct ulorawan_mac_frame_context *const ctx,
                               struct ulorawan_mac_fhdr *const fhdr);

/**
 * \brief Read the fport from a the context.
 *
 * \param[in] ctx The context to read from.
 * \param[out] fport The fport value.
 *
 * \return Operation status.
 * \retval ULORAWAN_ERR_NONE Operation executed successfully.
 * \retval ULORAWAN_MAC_ERR_INDEX The eof index is invalid.
 */
int32_t ulorawan_mac_read_fport(struct ulorawan_mac_frame_context *const ctx,
                                uint8_t *const fport);

/**
 * \brief
 *
 * \param[in] ctx The context to read from.
 * \param[out] payload The payload read.
 * \param[in] len The length of payload in bytes to read.
 *
 * \return Operation status.
 * \retval ULORAWAN_MAC_ERR_NONE Operation executed successfully.
 * \retval ULORAWAN_MAC_ERR_INDEX The eof index is invalid.
 */
int32_t
ulorawan_mac_read_frmpayload(struct ulorawan_mac_frame_context *const ctx,
                             uint8_t *const payload, size_t *const len);

/**
 * \brief Read the message header from the context.
 *
 * \param[in] ctx The context to read from.
 * \param[out] mhdr The message header read.
 *
 * \return Operation status.
 * \retval ULORAWAN_MAC_ERR_NONE Operation executed successfully.
 * \retval ULORAWAN_MAC_ERR_INDEX The eof index is invalid.
 */
int32_t ulorawan_mac_read_mhdr(struct ulorawan_mac_frame_context *const ctx,
                               union ulorawan_mac_mhdr *const mhdr);

/**
 * \brief Write the frame header to the context.
 *
 * \param[in] ctx The context to write to.
 * \param[in] fhdr The frame header to write.
 *
 * \return Operation status.
 * \retval ULORAWAN_MAC_ERR_NONE Operation executed successfully.
 * \retval ULORAWAN_MAC_ERR_INDEX The eof index is invalid.
 */
int32_t ulorawan_mac_write_fhdr(struct ulorawan_mac_frame_context *const ctx,
                                const struct ulorawan_mac_fhdr const *fhdr);

/**
 * \brief Write the fport value to the context.
 *
 * \param[in] ctx The context to write to.
 * \param[in] fport The fport val;ue to write.
 *
 * \return Operation status.
 * \retval ULORAWAN_MAC_ERR_NONE Operation executed successfully.
 * \retval ULORAWAN_MAC_ERR_INDEX The eof index is invalid.
 */
int32_t ulorawan_mac_write_fport(struct ulorawan_mac_frame_context *const ctx,
                                 uint8_t fport);

/**
 * \brief Write the frame a payload to the context.
 *
 * \param[in] ctx The context to write to.
 * \param[in] payload The payload bytes to write.
 * \param[in] len The length in bytes of the payload.
 *
 * \return Operation status.
 * \retval ULORAWAN_MAC_ERR_NONE Operation executed successfully.
 */
int32_t
ulorawan_mac_write_frmpayload(struct ulorawan_mac_frame_context *const ctx,
                              const uint8_t const *payload, size_t len);

/**
 * \brief
 *
 * \param[in] ctx The context to write to.
 * \param[in] request The join request.
 *
 * \return Operation status.
 */
int32_t
ulorawan_mac_write_join_req(struct ulorawan_mac_frame_context *const ctx,
                            const struct ulorawan_mac_join_req *const request);

/**
 * \brief Write a message header to the context.
 *
 * \param[in] ctx The context to write to.
 * \param[in] mhdr The message header to write.
 *
 * \return Operation status.
 * \retval ULORAWAN_MAC_ERR_NONE Operation executed successfully.
 * \retval ULORAWAN_MAC_ERR_INDEX The eof index is invalid.
 */
int32_t ulorawan_mac_write_mhdr(struct ulorawan_mac_frame_context *const ctx,
                                const union ulorawan_mac_mhdr *const mhdr);

/**
 * \brief Write the message integrity code to the context,
 *
 * \param[in] ctx The context to write to.
 * \param[in] mic The Message Integrity Code to write
 *
 * \return Operation status.
 * \retval ULORAWAN_ERR_NONE Operation executed successfully.
 */
int32_t ulorawan_mac_write_mic(struct ulorawan_mac_frame_context *const ctx,
                               uint32_t mic);

#ifdef __cplusplus
}
#endif

#endif /* ULORAWAN_MAC_H_ */
