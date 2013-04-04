//
// Copyright (c) 2012 Janick Bergeron
// All Rights Reserved
//
//   Licensed under the Apache License, Version 2.0 (the
//   "License"); you may not use this file except in
//   compliance with the License.  You may obtain a copy of
//   the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in
//   writing, software distributed under the License is
//   distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
//   CONDITIONS OF ANY KIND, either express or implied.  See
//   the License for the specific language governing
//   permissions and limitations under the License.
//

#ifndef __BONELIB_PINMUX__
#define __BONELIB_PINMUX__

namespace BeagleBone {

class pin_fct;

/** Class representing a physical pin */
class pin
{
public:
  typedef enum {IN, OUT} direction_t;
  typedef enum {NONE, PU, PD} pull_t;

  /** Get a connector pin */
  static pin* P8(unsigned char n);
  static pin* P9(unsigned char n);

  /** Return the name of the pin */
  const char* get_name();

  /** Return the current function carried by this pin */
  pin_fct* get_fct();

  /** Return the GPIO function carried by this pin.
   *  or NULL if it does not support a GPIO mode.
   */
  pin_fct* get_gpio();

  /** Export the specified functionality on this pin
   *  Returns TRUE if it was succesful.
   */
  virtual int xport(pin_fct* fct, direction_t dir = IN, pull_t pulls = NONE);

  /** Lock this pin to ensure its muxing cannot be changed.
   *  Returns the key that will unlock it.
   */
  virtual int is_locked();
  virtual int lock(const char* whoami);
  virtual void unlock(int key);


private:
  static pin* m_P8[46];
  static pin* m_P9[46];

  const char* m_name;
  char*       m_dev;
  pin_fct*    m_fct;
  pin_fct*    m_gpio;
  const char* m_locker;
  int         m_key;

protected:
  pin(const char*    name,
      const char*    dev,
      pin_fct* const mode0,
      pin_fct* const mode1,
      pin_fct* const mode2,
      pin_fct* const mode3,
      pin_fct* const mode4,
      pin_fct* const mode5,
      pin_fct* const mode6,
      pin_fct* const mode7,
      int            init,
      direction_t    dir = IN,
      pull_t         pulls = NONE);

private:
  void m_pin_can_do(pin_fct* const fct, unsigned char mode);
};

/** Class representing the functionality of a pin */
class pin_fct {

  friend class pin;

public:

  static pin_fct* const clkout2;
  static pin_fct* const d_can0_rx;
  static pin_fct* const d_can0_tx;
  static pin_fct* const d_can1_rx;
  static pin_fct* const d_can1_tx;
  static pin_fct* const eQEP2A_in;
  static pin_fct* const ecap0_in_pwm0_out;
  static pin_fct* const ecap2_in_pwm2_out;
  static pin_fct* const ehrpwm0A;
  static pin_fct* const ehrpwm0B;
  static pin_fct* const ehrpwm0_synco;
  static pin_fct* const ehrpwm1A;
  static pin_fct* const ehrpwm1B;
  static pin_fct* const ehrpwm1_tripzone_input;
  static pin_fct* const ehrpwm2A;
  static pin_fct* const ehrpwm2B;
  static pin_fct* const ehrpwm2_tripzone_input;
  static pin_fct* const eqep2B_in;
  static pin_fct* const eqep2_index;
  static pin_fct* const eqep2_strobe;
  static pin_fct* const eqep2a_in;
  static pin_fct* const eqep2b_in;
  static pin_fct* const gmii2_rxdv;
  static pin_fct* const gmii2_txd2;
  static pin_fct* const gmii2_txd3;
  static pin_fct* const gmii2_txen;
  static pin_fct* const gpio0_10;
  static pin_fct* const gpio0_11;
  static pin_fct* const gpio0_12;
  static pin_fct* const gpio0_13;
  static pin_fct* const gpio0_14;
  static pin_fct* const gpio0_15;
  static pin_fct* const gpio0_2;
  static pin_fct* const gpio0_20;
  static pin_fct* const gpio0_22;
  static pin_fct* const gpio0_23;
  static pin_fct* const gpio0_26;
  static pin_fct* const gpio0_27;
  static pin_fct* const gpio0_3;
  static pin_fct* const gpio0_30;
  static pin_fct* const gpio0_31;
  static pin_fct* const gpio0_4;
  static pin_fct* const gpio0_5;
  static pin_fct* const gpio0_7;
  static pin_fct* const gpio0_8;
  static pin_fct* const gpio0_9;
  static pin_fct* const gpio1_0;
  static pin_fct* const gpio1_1;
  static pin_fct* const gpio1_12;
  static pin_fct* const gpio1_13;
  static pin_fct* const gpio1_14;
  static pin_fct* const gpio1_15;
  static pin_fct* const gpio1_16;
  static pin_fct* const gpio1_17;
  static pin_fct* const gpio1_18;
  static pin_fct* const gpio1_19;
  static pin_fct* const gpio1_2;
  static pin_fct* const gpio1_28;
  static pin_fct* const gpio1_29;
  static pin_fct* const gpio1_3;
  static pin_fct* const gpio1_30;
  static pin_fct* const gpio1_31;
  static pin_fct* const gpio1_4;
  static pin_fct* const gpio1_5;
  static pin_fct* const gpio1_6;
  static pin_fct* const gpio1_7;
  static pin_fct* const gpio2_1;
  static pin_fct* const gpio2_10;
  static pin_fct* const gpio2_11;
  static pin_fct* const gpio2_12;
  static pin_fct* const gpio2_13;
  static pin_fct* const gpio2_14;
  static pin_fct* const gpio2_15;
  static pin_fct* const gpio2_16;
  static pin_fct* const gpio2_17;
  static pin_fct* const gpio2_22;
  static pin_fct* const gpio2_23;
  static pin_fct* const gpio2_24;
  static pin_fct* const gpio2_25;
  static pin_fct* const gpio2_3;
  static pin_fct* const gpio2_4;
  static pin_fct* const gpio2_5;
  static pin_fct* const gpio2_6;
  static pin_fct* const gpio2_7;
  static pin_fct* const gpio2_8;
  static pin_fct* const gpio2_9;
  static pin_fct* const gpio3_14;
  static pin_fct* const gpio3_15;
  static pin_fct* const gpio3_16;
  static pin_fct* const gpio3_17;
  static pin_fct* const gpio3_19;
  static pin_fct* const gpio3_21;
  static pin_fct* const gpmc_a0;
  static pin_fct* const gpmc_a1;
  static pin_fct* const gpmc_a10;
  static pin_fct* const gpmc_a11;
  static pin_fct* const gpmc_a12;
  static pin_fct* const gpmc_a13;
  static pin_fct* const gpmc_a14;
  static pin_fct* const gpmc_a15;
  static pin_fct* const gpmc_a16;
  static pin_fct* const gpmc_a17;
  static pin_fct* const gpmc_a18;
  static pin_fct* const gpmc_a19;
  static pin_fct* const gpmc_a2;
  static pin_fct* const gpmc_a3;
  static pin_fct* const gpmc_a4;
  static pin_fct* const gpmc_a5;
  static pin_fct* const gpmc_a6;
  static pin_fct* const gpmc_a7;
  static pin_fct* const gpmc_a8;
  static pin_fct* const gpmc_a9;
  static pin_fct* const gpmc_ad0;
  static pin_fct* const gpmc_ad1;
  static pin_fct* const gpmc_ad10;
  static pin_fct* const gpmc_ad11;
  static pin_fct* const gpmc_ad12;
  static pin_fct* const gpmc_ad13;
  static pin_fct* const gpmc_ad14;
  static pin_fct* const gpmc_ad15;
  static pin_fct* const gpmc_ad2;
  static pin_fct* const gpmc_ad3;
  static pin_fct* const gpmc_ad4;
  static pin_fct* const gpmc_ad5;
  static pin_fct* const gpmc_ad6;
  static pin_fct* const gpmc_ad7;
  static pin_fct* const gpmc_ad8;
  static pin_fct* const gpmc_ad9;
  static pin_fct* const gpmc_advn_ale;
  static pin_fct* const gpmc_be1n;
  static pin_fct* const gpmc_ben0_cle;
  static pin_fct* const gpmc_ben1;
  static pin_fct* const gpmc_clk;
  static pin_fct* const gpmc_csn0;
  static pin_fct* const gpmc_csn1;
  static pin_fct* const gpmc_csn2;
  static pin_fct* const gpmc_oen_ren;
  static pin_fct* const gpmc_wait0;
  static pin_fct* const gpmc_wen;
  static pin_fct* const gpmc_wpn;
  static pin_fct* const i2c1_scl;
  static pin_fct* const i2c1_sda;
  static pin_fct* const i2c2_scl;
  static pin_fct* const i2c2_sda;
  static pin_fct* const lcd_ac_bias_en;
  static pin_fct* const lcd_data0;
  static pin_fct* const lcd_data1;
  static pin_fct* const lcd_data10;
  static pin_fct* const lcd_data11;
  static pin_fct* const lcd_data12;
  static pin_fct* const lcd_data13;
  static pin_fct* const lcd_data14;
  static pin_fct* const lcd_data15;
  static pin_fct* const lcd_data16;
  static pin_fct* const lcd_data17;
  static pin_fct* const lcd_data18;
  static pin_fct* const lcd_data19;
  static pin_fct* const lcd_data2;
  static pin_fct* const lcd_data20;
  static pin_fct* const lcd_data21;
  static pin_fct* const lcd_data22;
  static pin_fct* const lcd_data23;
  static pin_fct* const lcd_data3;
  static pin_fct* const lcd_data4;
  static pin_fct* const lcd_data5;
  static pin_fct* const lcd_data6;
  static pin_fct* const lcd_data7;
  static pin_fct* const lcd_data8;
  static pin_fct* const lcd_data9;
  static pin_fct* const lcd_hsync;
  static pin_fct* const lcd_memory_clk_mux;
  static pin_fct* const lcd_pclk;
  static pin_fct* const lcd_vsync;
  static pin_fct* const mcasp0_aclkr;
  static pin_fct* const mcasp0_aclkx;
  static pin_fct* const mcasp0_ahclkr;
  static pin_fct* const mcasp0_ahclkx;
  static pin_fct* const mcasp0_axr0;
  static pin_fct* const mcasp0_axr1;
  static pin_fct* const mcasp0_axr2;
  static pin_fct* const mcasp0_axr3;
  static pin_fct* const mcasp0_fsr;
  static pin_fct* const mcasp0_fsx;
  static pin_fct* const mcasp1_axr1;
  static pin_fct* const mcasp1_fsx;
  static pin_fct* const mii2_col;
  static pin_fct* const mii2_crs;
  static pin_fct* const mii2_rxerr;
  static pin_fct* const mmc0_sdcd;
  static pin_fct* const mmc0_sdwp;
  static pin_fct* const mmc1_clk;
  static pin_fct* const mmc1_cmd;
  static pin_fct* const mmc1_dat0;
  static pin_fct* const mmc1_dat1;
  static pin_fct* const mmc1_dat2;
  static pin_fct* const mmc1_dat3;
  static pin_fct* const mmc1_dat4;
  static pin_fct* const mmc1_dat5;
  static pin_fct* const mmc1_dat6;
  static pin_fct* const mmc1_dat7;
  static pin_fct* const mmc1_sdcd;
  static pin_fct* const mmc1_sdwp;
  static pin_fct* const mmc2_clk;
  static pin_fct* const mmc2_dat0;
  static pin_fct* const mmc2_dat1;
  static pin_fct* const mmc2_dat2;
  static pin_fct* const mmc2_dat3;
  static pin_fct* const mmc2_dat4;
  static pin_fct* const mmc2_dat5;
  static pin_fct* const mmc2_dat6;
  static pin_fct* const mmc2_dat7;
  static pin_fct* const mmc2_sdcd;
  static pin_fct* const mmc2_sdwp;
  static pin_fct* const rgmii2_rctl;
  static pin_fct* const rgmii2_tctl;
  static pin_fct* const rgmii2_td2;
  static pin_fct* const rgmii2_td3;
  static pin_fct* const rmii2_crs_dv;
  static pin_fct* const rmii2_rxerr;
  static pin_fct* const rmii2_txen;
  static pin_fct* const spi0_cs0;
  static pin_fct* const spi0_d0;
  static pin_fct* const spi0_d1;
  static pin_fct* const spi0_sclk;
  static pin_fct* const spi1_cs0;
  static pin_fct* const spi1_cs1;
  static pin_fct* const spi1_d0;
  static pin_fct* const spi1_d1;
  static pin_fct* const spi1_sclk;
  static pin_fct* const uart1_ctsn;
  static pin_fct* const uart1_rtsn;
  static pin_fct* const uart1_rxd;
  static pin_fct* const uart1_txd;
  static pin_fct* const uart2_ctsn;
  static pin_fct* const uart2_rtsn;
  static pin_fct* const uart2_rxd;
  static pin_fct* const uart2_txd;
  static pin_fct* const uart3_ctsn;
  static pin_fct* const uart3_txd;
  static pin_fct* const xdma_event_intr1;
  static pin_fct* const xdma_event_intr2;

  /** Return the name of this functionality
   */
  const char* get_name();

  /** Get the pin that is currently muxed with that functionality.
   *  NULL is none are.
   */
  pin* get_pin();

  /** If not already assigned to a pin, muxes a pin to this function.
   *  Returns the pin if succesful, NULL otherwise.
   */
  virtual pin* xport(pin::direction_t dir = pin::IN, pin::pull_t pulls = pin::NONE);

private:
  /* Pins that CAN be muxed with this function */
  pin*          m_pins[4];
  unsigned char m_mode[4];

  /* Pin currently muxed with this functionality */
  pin* m_pin;

  const char* m_name;

protected:
  pin_fct(const char* name);
};

}

#endif
