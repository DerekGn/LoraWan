/**
 * \file
 *
 * \brief The abstraction layer functions for abstracting the underlying OS
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

#ifndef OSAL_QUEUE_H_
#define OSAL_QUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#define OSAL_QUEUE_ERR_NONE 0
#define OSAL_QUEUE_ERR_FAIL -1

struct osal_queue {
    void *queue;
};

/**
 * \brief 
 * 
 * \param queue
 * 
 * \return int32_t
 */
int32_t osal_queue_create(const struct osal_queue *const queue);

bool osal_queue_empty(const struct osal_queue *const queue);

int32_t osal_queue_receive(const struct osal_queue *const queue, void* data);

int32_t osal_queue_send(const struct osal_queue *const queue, void const * data);

#ifdef __cplusplus
}
#endif

#endif /* OSAL_QUEUE_H_ */
