/**
 * \file
 *
 * \brief The HAL prototypes for abstracting the Timer
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

#ifndef TIMER_HAL_H_
#define TIMER_HAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#define TIMER_HAL_ERR_NONE 0
#define TIMER_HAL_ERR_FAIL -1

enum timer_hal_timer
{
    TIMER0,
    TIMER1
};

/**
 * \brief Start a timer instance in one shot mode.
 * 
 * \param timer The timer instance.
 * \param interval The interval for the timer
 * 
 * \return Operation status.
 */
int32_t timer_hal_start(enum timer_hal_timer timer, uint32_t interval);

/**
 * \brief Stop a timer instance.
 * 
 * \param timer The timer instance.
 * 
 * \return Operation status.
 */
int32_t timer_hal_stop(enum timer_hal_timer timer);

#ifdef __cplusplus
}
#endif

#endif /* TIMER_HAL_H_ */