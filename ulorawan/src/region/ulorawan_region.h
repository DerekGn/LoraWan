/**
 * \file
 *
 * \brief The uloraWan region function prototypes
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

#ifndef LORAWAN_REGION_H_
#define LORAWAN_REGION_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ulorawan_common.h"

//! The ulorawan region version.
#define ULORAWAN_REGION_VERSION 0x02010004

#define ULORAWAN_REGION_CHMASK_GROUP_SIZE 2

#define ULORAWAN_REGION_ERR_NONE 0
#define ULORAWAN_REGION_ERR_FAIL -1

//! The default RX1 receive delay
#define ULORAWAN_REGION_RECEIVE_DELAY1 1000
//! The default RX2 receive delay
#define ULORAWAN_REGION_RECEIVE_DELAY2 2000


#ifndef ACTIVE_REGION
#define ACTIVE_REGION REGION_EU868
#endif

//! The Regional Parameter Channel Plan Common Names
enum ulorawan_region {
  REGION_NONE,
  REGION_EU868,
  REGION_US915,
  REGION_CN779,
  REGION_EU433,
  REGION_AU915,
  REGION_CN470,
  REGION_AS923,
  REGION_AS923_2,
  REGION_AS923_3,
  REGION_KR920,
  REGION_IN865,
  REGION_RU864,
  REGION_AS923_4
};

//! The cflist type
enum ulorawan_cflist_type {
  //! Dynamic channel plan type
  CFLIST_TYPE_DYNAMIC,
  //! Fixed channel plan type
  CFLIST_TYPE_FIXED
};

//! The channel frequency list structure
struct ulorawan_cflist {
  union ulorawan_cflist_field {
    struct ulorawan_cflist_dynamic {
      uint8_t freq_0[ULORAWAN_FREQ_SIZE];
      uint8_t freq_1[ULORAWAN_FREQ_SIZE];
      uint8_t freq_2[ULORAWAN_FREQ_SIZE];
      uint8_t freq_3[ULORAWAN_FREQ_SIZE];
      uint8_t freq_4[ULORAWAN_FREQ_SIZE];
    }
    //! The dynamic channel frequencies
    dynamic_list;
    struct ulorawan_cflist_fixed {
      uint8_t chmask_grp0[ULORAWAN_REGION_CHMASK_GROUP_SIZE];
      uint8_t chmask_grp1[ULORAWAN_REGION_CHMASK_GROUP_SIZE];
      uint8_t chmask_grp2[ULORAWAN_REGION_CHMASK_GROUP_SIZE];
      uint8_t chmask_grp3[ULORAWAN_REGION_CHMASK_GROUP_SIZE];
      uint8_t chmask_grp4[ULORAWAN_REGION_CHMASK_GROUP_SIZE];
      uint8_t chmask_grp5[ULORAWAN_REGION_CHMASK_GROUP_SIZE];
      uint8_t rfu[3];
    }
    //! The fixed channel frequencies groups
    fixed_list;
  } value;
  //! The CFLIST type
  enum ulorawan_cflist_type type;
};

//! A ulorawan channel
struct ulorawan_channel {
  //! The channel frequency
  uint32_t frequency;
  //! The channel modulation type
  enum ulorawan_modulation modulation;
};

struct ulorawan_region_params {
    enum ulorawan_region region;
  //! The RX 1 delay
  uint32_t rx_delay_1;
  //! The RX 2 delay
  uint32_t rx_delay_2;
};

int32_t ulorawan_region_get_channel(const struct ulorawan_channel const *channel);

int32_t ulorawan_region_init_params(struct ulorawan_region_params *const params);

int32_t ulorawan_region_update_channels(struct ulorawan_cflist sflist);

/**
 * \brief Get the ulorawan region version
 *
 *
 * \return union version
 */
union version ulorawan_region_version();

#ifdef __cplusplus
}
#endif

#endif /* LORAWAN_REGION_H_ */
