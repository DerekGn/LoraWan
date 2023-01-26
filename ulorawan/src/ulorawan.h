/**
 * \file
 *
 * \brief The ulorawan function prototypes
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

#ifndef ULORAWAN_H_
#define ULORAWAN_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "radio_hal.h"
#include "timer_hal.h"
#include "osal_queue.h"
#include "ulorawan_common.h"
#include "ulorawan_session.h"

//! The ulorawan specification version
#define ULORAWAN_VERSION 0x01000400

#ifdef TEST
#define SESSION_ACCESS struct ulorawan_session *const
#else
#define SESSION_ACCESS const struct ulorawan_session *const
#endif // TEST

SESSION_ACCESS ulorawan_get_session();

/**
 * \brief Initialise the ulorawan stack
 *
 * \param[in] class The device operation class.
 * \param[in] security The device security configuration.
 *
 * \return Operation status.
 * \retval ULORAWAN_ERR_RAND The rand initalisation failed.
 * \retval ULORAWAN_ERR_QUEUE The queue initalisation failed.
 * \retval ULORAWAN_ERR_NONE Operation executed successfully.
 */
int32_t ulorawan_init(enum ulorawan_device_class class,
                      struct ulorawan_device_security security);

/**
 * \brief Execute lorawan join operation.
 *
 * \return Operation status.
 * \retval ULORAWAN_ERR_INIT The ulorawan stack has not been initialised.
 * \retval ULORAWAN_ERR_STATE The ulorawan stack in not in the correct state.
 * \retval ULORAWAN_ERR_NO_CHANNEL No channel configuration available.
 * \retval ULORAWAN_ERR_NVM Nvm operation failed.
 * \retval ULORAWAN_ERR_CTX Context read/write failed.
 * \retval ULORAWAN_ERR_CMAC Calculating the cmac failed.
 * \retval ULORAWAN_ERR_RADIO_TX Radio tx failed.
 * \retval ULORAWAN_ERR_NONE Operation executed successfully.
 */
int32_t ulorawan_join();

/**
 * \brief Radio irq handling function
 *
 * \param[in] flags The Irq flage
 *
 * \return Operation status.
 * \retval ULORAWAN_ERR_INIT The ulorawan stack has not been initialised.
 * \retval ULORAWAN_ERR_NONE Operation executed successfully.
 */
int32_t ulorawan_radio_irq(const enum radio_hal_irq_flags flags);

/**
 * \brief
 *
 * \param port
 * \param payload
 * \param size
 * \param confirm
 *
 * \return Operation status.
 * \retval ULORAWAN_ERR_NONE Operation executed successfully.
 */
int32_t ulorawan_send_frame(uint8_t port, const uint8_t *const payload, uint8_t size,
                            bool confirm);

/**
 * \brief Process ulorawan events
 *
 * \return Operation status.
 * \retval ULORAWAN_ERR_INIT The ulorawan stack has not been initialised.
 * \retval ULORAWAN_ERR_NONE Operation executed successfully.
 */
int32_t ulorawan_task();


int32_t ulorawan_timer_expired(enum timer_hal_timer timer);

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
