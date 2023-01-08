/**
 * \file
 *
 * \brief LoraWan common types
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

#ifndef ULORAWAN_COMMON_H_
#define ULORAWAN_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

///< The size of frequency field in bytes
#define ULORAWAN_FREQ_SIZE 3

///< The lorawan bandwidth
enum ulorawan_bw {
  ///< 125 Khz
  BW_125,
  ///< 250 Khz
  BW_250,
  ///< 500 Khz
  BW_500
};

///< The lorawan data rate ranges
enum ulorawan_datarate {
  DR_0,
  DR_1,
  DR_2,
  DR_3,
  DR_4,
  DR_5,
  DR_6,
  DR_7,
  DR_8,
  DR_9,
  DR_10,
  DR_11,
  DR_12,
  DR_13,
  DR_14,
  DR_15
};

///< The lorawan modulation types
enum ulorawan_modulation {
  ///< Lora modulation
  MODULATION_LORA,
  ///< FSK modulation
  MODULATION_FSK,
  ///< Long-Range Frequency Hopping Spread Spectrum
  MODULATION_LR_FHSS
};

///< The lorawan spread factor
enum ulorawan_sf {
  SPREAD_FACTOR_6,
  SPREAD_FACTOR_7,
  SPREAD_FACTOR_8,
  SPREAD_FACTOR_9,
  SPREAD_FACTOR_10,
  SPREAD_FACTOR_11,
  SPREAD_FACTOR_12
};

///< The version type
union version {
  ///< The version value as an
  uint32_t value;
  struct {
    ///< The revision value
    uint8_t revision;
    ///< The patch value
    uint8_t patch;
    ///< The major value
    uint8_t minor;
    ///< The minor value
    uint8_t major;
  }
  ///< The fields of the version
  fields;
};

#ifdef __cplusplus
}
#endif

#endif /* ULORAWAN_REGION_H_ */
