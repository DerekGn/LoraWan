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

#include "osal.h"
#include "radio_hal.h"
#include "ulorawan_common.h"
#include "ulorawan_session.h"

//! The ulorawan version
#define ULORAWAN_VERSION 0x01000400

#define ULORAWAN_ERR_NONE 0
#define ULORAWAN_ERR_INIT -1
#define ULORAWAN_ERR_STATE -2
#define ULORAWAN_ERR_NO_CHANNEL -3
#define ULORAWAN_ERR_PARAMS -4
#define ULORAWAN_ERR_RAND -5
#define ULORAWAN_ERR_QUEUE -6

#ifdef TEST
#define SESSION_ACCESS struct ulorawan_session *const
#else
#define SESSION_ACCESS const struct ulorawan_session *const
#endif // TEST

//! The activation type
enum ulorawan_activation_type {
  //! Activation by personalisation
  ACTIVATION_ABP,
  //! Activation by over the air activation
  ACTIVATION_OTAA
};

//! The device activation
struct ulorawan_device_activation {
  //! The activation type
  enum ulorawan_activation_type type;
  union ulorawan_activation_context {
    struct ulorawan_activation_abp {
        
    } abp;
    struct ulorawan_activation_otaa {
    } otaa;
  } context;
};

SESSION_ACCESS ulorawan_get_session();

/**
 * \brief Initialise the ulorawan stack
 *
 * \param class The class
 *
 * \return Operation status.
 * \retval ULORAWAN_ERR_RAND The rand initalisation failed.
 * \retval ULORAWAN_ERR_NONE Operation done successfully.
 */
int32_t ulorawan_init(enum ulorawan_device_class class);

/**
 * \brief Execute lorawan join operation.
 *
 * \return Operation status.
 * \retval ULORAWAN_ERR_INIT The ulorawan stack has not been initialised.
 * \retval ULORAWAN_STATE_IDLE The ulorawan stack in not idle.
 * \retval ULORAWAN_ERR_NO_CHANNEL No channel configuration available.
 * \retval ULORAWAN_ERR_PARAMS Invalid input parameters.
 * \retval ULORAWAN_ERR_NONE Operation done successfully.
 */
int32_t ulorawan_join();

/**
 * \brief
 *
 * \param flags
 *
 * \return Operation status.
 * \retval ULORAWAN_ERR_INIT The ulorawan stack has not been initialised.
 * \retval ULORAWAN_ERR_NONE Operation done successfully.
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
 * \retval ULORAWAN_ERR_NONE Operation done successfully.
 */
int32_t ulorawan_send_frame(uint8_t port, const uint8_t *payload, uint8_t size,
                            bool confirm);

/**
 * \brief Process ulorawan events
 *
 * \return Operation status.
 * \retval ULORAWAN_ERR_INIT The ulorawan stack has not been initialised.
 * \retval ULORAWAN_ERR_NONE Operation done successfully.
 */
int32_t ulorawan_task();

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
