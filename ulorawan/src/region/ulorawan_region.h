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

int32_t ulorawan_region_get_channel(const struct ulorawan_channel *channel);

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
