/**
 * \file
 *
 * \brief LoraWan MAC types
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

#ifndef LORAWAN_MAC_H_
#define LORAWAN_MAC_H_

#ifdef __cplusplus
extern "C" {
#endif

///< FOpts maximum field size
#define LORAMAC_FHDR_F_OPTS_MAX_SIZE 15

///< The end-device is connected to an external power source.
#define LORAWAN_MAC_BATTERY_EXTERNAL_SOURCE 0

///< The end-device was not able to measure the battery level.
#define LORAWAN_MAC_BATTERY_UNABLE_TO_MEASURE 0xFF

///< The size of frequency field in bytes
#define LORAMAC_MAC_FREQ_SIZE 3

/**
 * \brief LoraWan Mac LinkADRAns payload
 */
union lorawan_mac_adr_ans {
  uint8_t value;
  struct bits {
    ///< The channel mask acknowledge
    uint8_t ch_mask_ack : 1;
    ///< The data rate acknowledge
    uint8_t data_rate_ack : 1;
    ///< The power level acknowledge
    uint8_t power_ack : 1;
    ///< Reserved
    uint8_t rfu : 5;
  };
};

/**
 * \brief LoraWan Mac frame types
 */
enum lorawan_mac_frame_type {
  ///< A Join Request
  FRAME_TYPE_JOIN_REQ = 0x00,
  ///< A Join Accepted
  FRAME_TYPE_JOIN_ACCEPT = 0x01,
  ///< Unconfirmed data uplink
  FRAME_TYPE_DATA_UNCONFIRMED_UP = 0x02,
  ///< Unconfirmed data downlink
  FRAME_TYPE_DATA_UNCONFIRMED_DOWN = 0x03,
  ///< Confirmed data uplink
  FRAME_TYPE_DATA_CONFIRMED_UP = 0x04,
  ///< confirmed data downlink
  FRAME_TYPE_DATA_CONFIRMED_DOWN = 0x05,
  ///< RFU
  FRAME_TYPE_RFU = 0x06,
  ///< Proprietary
  FRAME_TYPE_PROPRIETARY = 0x07
};

/**
 * \brief LoraWan end device commands
 */
enum lorawan_mac_dev_cmds {
  ///< Used by an end-device to validate its connectivity to a network.
  DEV_MAC_LINK_CHECK_REQ = 0x02,
  ///< Acknowledges a LinkADRReq command.
  DEV_MAC_LINK_ADR_ANS = 0x03,
  ///< Acknowledges a DutyCycleReq command.
  DEV_MAC_DUTY_CYCLE_ANS = 0x04,
  ///< Acknowledges a RXParamSetupReq command.
  DEV_MAC_RX_PARAM_SETUP_ANS = 0x05,
  ///< Returns the status of the end-device, namely its battery level and its
  ///< radio status.
  DEV_MAC_DEV_STATUS_ANS = 0x06,
  ///< Acknowledges NewChannelReq command.
  DEV_MAC_NEW_CHANNEL_ANS = 0x07,
  /// < Acknowledges RXTimingSetupReq command.
  DEV_MAC_RX_TIMING_SETUP_ANS = 0x08,
  ///< Acknowledges a TXParamSetupReq command.
  DEV_MAC_TX_PARAM_SETUP_ANS = 0x09,
  ///< Acknowledges a DlChannelReq command.
  DEV_MAC_DL_CHANNEL_ANS = 0x0A,
  ///< Answers a DeviceTimeReq command.
  DEV_MAC_DEV_TIME_ANS = 0x0D
};

/**
 * \brief LoraWan server commands
 */
enum lorawan_mac_srv_cmds {
  ///< Answers LinkCheckReq. Contains the received signal power
  ///< estimation, which indicates the quality of reception (link
  ///< margin) to the end-device.
  SRV_MAC_LINK_CHECK_ANS = 0x02,
  ///< Requests the end-device to change data rate, TX power, redundancy, or
  ///< channel  mask.
  SRV_MAC_LINK_ADR_REQ = 0x03,
  ///< Sets the maximum aggregated transmit duty cycle of an end-device.
  SRV_MAC_DUTY_CYCLE_REQ = 0x04,
  ///< Sets the reception slot parameters.
  SRV_MAC_RX_PARAM_SETUP_REQ = 0x05,
  ///< Requests the status of the end-device.
  SRV_MAC_DEV_STATUS_REQ = 0x06,
  ///< Creates or modifies the definition of a radio channel
  SRV_MAC_NEW_CHANNEL_REQ = 0x07,
  ///< Sets the timing of the reception slots.
  SRV_MAC_RX_TIMING_SETUP_REQ = 0x08,
  ///< Used by a Network Server to set the maximum allowed dwell time and
  ///< MaxEIRP of end-device, based on local regulations.
  SRV_MAC_TX_PARAM_SETUP_REQ = 0x09,
  ///< Modifies the definition of a downlink RX1 radio channel by shifting the
  ///< downlink frequency from the uplink frequencies (i.e. creating an
  ///< asymmetric channel)
  SRV_MAC_DL_CHANNEL_REQ = 0x0A,
  ///< Used by an end-device to request the current GPS time.
  SRV_MAC_DEV_TIME_REQ = 0x0D,
};

/**
 * \brief LoraWan Mac header
 */
union lorawan_mac_hdr {
  uint8_t value;
  struct bits {
    ///< The major version of the frame format of LoraWan layer specification
    uint8_t major : 2;
    ///< Reserved
    uint8_t rfu : 2;
    ///< The frame type
    enum lorawan_mac_frame_type ftype : 3;
  };
};

/**
 * \brief LoraWan Mac frame control
 */
union lorawan_mac_frame_ctr {
  uint8_t value;
  struct bits {
    ///< Frame options
    uint8_t fopts_len : 4;
    ///< Frame pending bit for downlink frames or Class B bit on uplink frames
    uint8_t fpending_classb : 1;
    uint8_t ack : 1;
    ///< ADR acknowledgment request bit
    uint8_t adr_ack_req : 1;
    ///< Adaptive Data Rate
    uint8_t adr : 1;
  };
};

/**
 * \brief LoraWan Mac frame header
 */
struct lorawan_mac_frame_header {
  ///< The device address
  uint32_t dev_addr;
  ///< The frame control
  struct lorawan_mac_frame_ctr fctrl;
  ///< The frame counter
  uint16_t fcnt;
  ///< The frame options
  uint8_t fopts[LORAMAC_FHDR_F_OPTS_MAX_SIZE];
};

/**
 * \brief LoraWan Mac frame header
 */
struct lorawan_mac_payload {};

/**
 * \brief LoraWan Mac LinkCheckAns payload
 */
struct lorawan_mac_link_check_ans {
  ///< The demodulation margin in the range of 0..254
  uint8_t margin;
  ///< The gateway count (GwCnt) is the number of gateways that received the
  ///< most recent LinkCheckReq command.
  uint8_t gw_cnt;
};

/**
 * \brief LoraWan Mac data rate tx power
 */
union lorawan_mac_dr_tx_power {
  uint8_t value;
  struct bits {
    ///< The tx power
    uint8_t tx_power : 4;
    ///< The data rate
    uint8_t data_rate : 4;
  };
};

union lorawan_mac_redundancy {
  uint8_t value;
  struct bits {
    ///< the number of transmissions for each uplink frame
    uint8_t nbtrans : 4;
    ///< The channel mask control.
    uint8_t ch_mask_ctl : 3;
    ///< Reserved
    uint8_t rfu : 1;
  };
};

/**
 * \brief LoraWan Mac LinkADRReq payload
 */
struct lorawan_mac_link_adr_req {
  ///< The data rate and tx power
  struct lorawan_mac_dr_tx_power tx_power;
  ///< The channel mask
  uint8_t ch_mask;
};

/**
 * \brief LoraWan Mac DutyCycleReq payload
 */
union lorawan_mac_duty_cycle_req {
  uint8_t value;
  struct bits {
    ///< The maximum duty cycle
    uint8_t max_duty_cycle : 4;
    ///< Reserved
    uint8_t rfu : 4;
  };
};

/**
 * \brief LoraWan Mac DLSettings
 */
union lowrawan_mac_dlsettings {
  uint8_t value;
  struct bits {
    ///< Data rate of a downlink using the second receive window
    uint8_t RX2DataRate : 4;
    ///< Offset between up and downlink datarate of first reception slot
    uint8_t RX1DRoffset : 3;
    uint8_t rfu : 1;
  };
};

/**
 * \brief LoraWan Mac RXParamSetupReq payload
 */
union lowrawan_mac_rx_param_setup_req {
  ///< The download settings
  union lowrawan_mac_dlsettings dlsettings;
  ///< The the frequency of the channel used for the second receive window
  uint8_t freq[LORAMAC_MAC_FREQ_SIZE];
};

/**
 * \brief LoraWan Mac RXParamSetupAns payload
 */
union lowrawan_mac_rx_param_setup_ans {
  ///< Acknowledge the channel change
  uint8_t channel_ack : 1;
  ///< Acknowledge the rx2 data rate change
  uint8_t rx2_data_rate_ack : 1;
  ///< Acknowledge the rx1 data offset change
  uint8_t rx1_dr_offset_ack : 1;
  ///< Reserved
  uint8_t rfu : 5;
};

/**
 * \brief LoraWan Mac RadioStatus
 */
union lowrawan_mac_radio_status {
  ///< The signal-to-noise ratio
  uint8_t snr : 6;
  ///< Reserved
  uint8_t rfu : 2;
};

/**
 * \brief LoraWan Mac DevStatusAns payload
 */
struct lorawan_mac_device_status_ans {
  ///< The devices battery level
  uint8_t battry_level;
  ///< The radio status
  union lowrawan_mac_radio_status radio_status;
};

/**
 * \brief LoraWan Mac NewChannelReq payload
 */
struct lorawan_mac_new_channel_req {};

/**
 * \brief LoraWan Mac NewChannelAns payload
 */
struct lorawan_mac_new_channel_ans {};

/**
 * \brief LoraWan Mac DlChannelReq payload
 */
struct lorawan_mac_dl_channel_req {};

/**
 * \brief LoraWan Mac DlChannelAns payload
 */
struct lorawan_mac_dl_channel_ans {};

/**
 * \brief LoraWan Mac RXTimingSetupReq payload
 */
struct lorawan_mac_rx_timing_setup_req {
}

/**
 * \brief LoraWan Mac RXTimingSetupAns payload
 */
struct lorawan_mac_rx_timing_setup_ans {
}

/**
 * \brief LoraWan Mac TXParamSetupReq payload
 */
struct lorawan_mac_tx_param_setup_req {
}

/**
 * \brief LoraWan Mac TXParamSetupAns payload
 */
struct lorawan_mac_tx_param_setup_ans {
}

/**
 * \brief LoraWan Mac DeviceTimeReq payload
 */
struct lorawan_mac_dev_time_req {
}

/**
 * \brief LoraWan Mac DeviceTimeAns payload
 */
struct lorawan_mac_dev_time_ans {
}

/**
 * \brief LoraWan Mac device address
 */
struct lowrawan_mac_dev_address {
};

#ifdef __cplusplus
}
#endif

#endif /* LORAWAN_MAC_H_ */
