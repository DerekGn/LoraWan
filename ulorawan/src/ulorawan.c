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

#include <string.h>

#include "nvm_hal.h"
#include "ulorawan.h"
#include "ulorawan_mac.h"
#include "ulorawan_region.h"
#include "ulorawan_mac_cmds.h"

static struct ulorawan_session session = {ULORAWAN_STATE_INIT};
static struct osal_queue event_queue;

SESSION_ACCESS ulorawan_get_session() { return &session; }

int32_t ulorawan_init(enum ulorawan_device_class class,
                      struct ulorawan_device_security security) {

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

  if (session.security.type != ACTIVATION_OTAA) {
    return ULORAWAN_ERR_ACTIVATION;
  }

  const struct ulorawan_channel *channel = ulorawan_region_get_channel();

  if (channel == NULL) {
    return ULORAWAN_ERR_NO_CHANNEL;
  }

  // create join request
  struct ulorawan_mac_join_req join_req;

  //if (!nvm_hal_read_join_nonce(&join_req.device_nonce)) {
    //return ULORAWAN_ERR_READ_NONCE;
  //}

  memcpy(join_req.join_eui, session.security.context.otaa.join_eui,
         ULORAWAN_JOIN_EUI_SIZE);
  memcpy(join_req.device_eui, session.security.context.otaa.dev_eui,
         ULORAWAN_DEV_EUI_SIZE);

  // encrypt join request
  struct ulorawan_mac_frame_context context;

  union ulorawan_mac_mhdr mhdr = {FRAME_TYPE_JOIN_REQ | LORAWAN_MAJOR_R1};

  if (!ulorawan_mac_write_mhdr(&context, &mhdr)) {
    return ULORAWAN_ERR_CTX_WRITE;
  }

  if (!ulorawan_mac_write_join_req(&context, &join_req)) {
    return ULORAWAN_ERR_CTX_WRITE;
  }

  // ulorawan_mac_message(&context, &join_req,
  // sizeof(struct ulorawan_mac_join_req));

  // radio_hal_configure();

  session.state = ULORAWAN_STATE_TX;
  // radio tx

  if (!nvm_hal_write_join_nonce(join_req.device_nonce)) {
    return ULORAWAN_ERR_WRITE_NONCE;
  }

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
