/**
 * \file
 *
 * \brief The ulorawan function implementations
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
#include <stddef.h>

#include "osal.h"
#include "radio_hal.h"
#include "rand_hal.h"
#include "ulorawan.h"
#include "ulorawan_region.h"

static struct ulorawan_session session = {ULORAWAN_STATE_INIT};
static struct osal_queue event_queue;

SESSION_ACCESS ulorawan_get_session() { return &session; }

int32_t ulorawan_init(enum ulorawan_device_class class, struct ulorawan_device_security security) {
  if (rand_hal_init() != RAND_HAL_ERR_NONE) {
    return ULORAWAN_ERR_RAND;
  }

  if (!osal_queue_create(&event_queue)) {
    return ULORAWAN_ERR_QUEUE;
  }

  session.state = ULORAWAN_STATE_IDLE;
  session.security = security;
  session.class = class;

  return ULORAWAN_ERR_NONE;
}

int32_t ulorawan_join() {
  if (session.state == ULORAWAN_STATE_INIT) {
    return ULORAWAN_ERR_INIT;
  }

  const struct ulorawan_channel *channel = ulorawan_region_get_channel();

  if (channel == NULL) {
    return ULORAWAN_ERR_NO_CHANNEL;
  }

  // create join request

  // encrypt join request

  // radio_hal_configure();

  // radio tx

  return ULORAWAN_ERR_NONE;
}

int32_t ulorawan_radio_irq(const enum radio_hal_irq_flags flags) {
  if (session.state == ULORAWAN_STATE_INIT) {
    return ULORAWAN_ERR_INIT;
  }

  // osal_queue_send();

  return ULORAWAN_ERR_NONE;
}

int32_t ulorawan_task() {
  if (session.state == ULORAWAN_STATE_INIT) {
    return ULORAWAN_ERR_INIT;
  }

  while (1) {
    // if ( !osal_queue_receive(event_queue, &event, timeout_ms) ) return;
  };

  return ULORAWAN_ERR_NONE;
}

union version ulorawan_version() {
  union version v;

  v.value = ULORAWAN_VERSION;

  return v;
}
