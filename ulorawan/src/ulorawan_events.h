/**
 * \file
 *
 * \brief The ulorawan event prototypes
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

#ifndef ULORAWAN_EVENTS_H_
#define ULORAWAN_EVENTS_H_

#ifdef __cplusplus
extern "C" {
#endif

//! The ulorawan event type
enum ulorawan_event_type {
    //! Radio Irq 
    EVENT_TYPE_RADIO_IRQ,
    //! Timer expired
    EVENT_TYPE_TIMER_EXPIRE
};

//! The ulorawan event
struct ulorawan_event
{
    //! The event type
    enum ulorawan_event_type type;
    union {
        enum radio_hal_irq_flags flags;
        enum timer_hal_timer timer;
    } data;
};

#ifdef __cplusplus
}
#endif

#endif /* ULORAWAN_EVENTS_H_ */