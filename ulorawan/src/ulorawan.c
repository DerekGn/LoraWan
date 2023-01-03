/**
 * \file
 *
 * \brief
 *
 * Copyright (c) 2022 Derek Goslin
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

#include "ulorawan.h"
#include "ulorawan_region.h"

///< The ulorawan state
enum ulorawan_state
{
    ///< The ulorawan stack is initalised
    ULORAWAN_STATE_INIT,
    ///< The ulorawan stack is idle
    ULORAWAN_STATE_IDLE,
};

struct ulorawan_session
{
    enum ulorawan_state state;
};

static struct ulorawan_session session = { ULORAWAN_STATE_INIT };

enum ulorawan_error ulorawan_join()
{
    if(session.state == ULORAWAN_STATE_INIT)
    {
        return ULORAWAN_ERROR_INIT;
    }
    
    if(session.state != ULORAWAN_STATE_IDLE)
    {
        return ULORAWAN_ERROR_STATE;
    }

    const struct ulorawan_channel *channel = ulorawan_region_get_channel();

    if(channel == NULL)
    {
        return ULORAWAN_ERROR_CHANNEL;
    }
}

union version ulorawan_version() {
  union version v;

  v.value = ULORAWAN_VERSION;

  return v;
}