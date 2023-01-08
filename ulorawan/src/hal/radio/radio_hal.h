/**
 * \file
 *
 * \brief The HAL functions for abstracting the Radio
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

#ifndef RADIO_HAL_H_
#define RADIO_HAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define RADIO_HAL_ERR_NONE 0
#define RADIO_HAL_ERROR_PARAM -1

// TODO DEFINE IRQ FLAG VALUES
enum radio_hal_irq_flags
{
    RADIO_HAL_IRQ_RX_DONE,
    RADIO_HAL_IRQ_TX_DONE
};

///< The radio IRQ callback type definition
typedef void (* radio_hal_irq_cb_t)(const enum radio_hal_irq_flags irq_flags);

/**
 * \brief Register the radio IRQ callback function.
 * 
 * \param[in] cb Callback function
 * 
 * \return Registration status.
 * \retval RADIO_HAL_ERROR_PARAM Passed parameters were invalid.
 * \retval RADIO_HAL_ERR_NONE The callback registration completed successfully.
 */
int32_t radio_hal_irq_register(radio_hal_irq_cb_t cb);

#ifdef __cplusplus
}
#endif

#endif /* RADIO_HAL_H_ */
