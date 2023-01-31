/**
 * \file
 *
 * \brief The ulorawan error codes
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

#ifndef ULORAWAN_ERROR_CODES_H_
#define ULORAWAN_ERROR_CODES_H_

#ifdef __cplusplus
extern "C" {
#endif

//! No error occurred.
#define ULORAWAN_ERR_NONE 0
//! ulorawan not initialised.
#define ULORAWAN_ERR_INIT -1
//! ulorawan not in correct state for operation.
#define ULORAWAN_ERR_STATE -2
//! No channel available.
#define ULORAWAN_ERR_NO_CHANNEL -3
//! Invalid parameters.
#define ULORAWAN_ERR_PARAMS -4
//! Error initialising the rand source.
#define ULORAWAN_ERR_RAND -5
//! Error initialising the queue.
#define ULORAWAN_ERR_QUEUE -6
//! Error invalid activation type.
#define ULORAWAN_ERR_ACTIVATION -7
//! Error invalid read of nonce.
#define ULORAWAN_ERR_NVM -8
//! Error context write failure.
#define ULORAWAN_ERR_CTX -9
//! Error cmac compute error.
#define ULORAWAN_ERR_CMAC -10
//! Error radio error.
#define ULORAWAN_ERR_RADIO -11
//! Error region error.
#define ULORAWAN_ERR_REGION -12
//! Error timer error.
#define ULORAWAN_ERR_TIMER -13

#ifdef __cplusplus
}
#endif

#endif /* ULORAWAN_ERROR_CODES_H_ */
