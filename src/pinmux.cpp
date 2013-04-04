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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pinmux.hpp"
#include "gpio.hpp"

//
// Where are the pin control devices?
//
static const char* const devdir = "/sys/kernel/debug/omap_mux";

namespace BeagleBone {

  //
  // Private classes to model non-muxed pins
  //
class unmuxed_fct: public pin_fct
{
public:
  unmuxed_fct(const char * name) :
    pin_fct(name)
  {
  }

  virtual pin* xport(pin::direction_t dir = pin::IN, pin::pull_t pulls = pin::NONE)
  {
    return get_pin();
  }

};

class unmuxed_pin: public pin
{
public:
  unmuxed_pin(const char *     name,
	      unmuxed_fct *    fct,
	      pin::direction_t dir = pin::IN,
	      pin::pull_t      pulls = pin::NONE) :
    pin(name, "", fct, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, dir, pulls)
  {
  }

  virtual int xport(pin_fct* fct, direction_t dir = IN, pull_t pulls = NONE)
  {
    if (fct == get_fct()) return 1;

    fprintf(stderr, "ERROR: Cannot export a different function on non-muxed pin %s.\n", get_name());
    return 0;
  }

  virtual int is_locked()
  {
    return 1;
  }

  virtual int lock(const char* whoami)
  {
    fprintf(stderr, "ERROR: Cannot lock non-muxed pin %s.\n", get_name());
    return 0;
  }

  virtual void unlock(int key)
  {
    fprintf(stderr, "ERROR: Cannot unlock non-muxed pin %s.\n", get_name());
  }
};


static unmuxed_fct GND        = unmuxed_fct("GND");
static unmuxed_fct VDD_3V3EXP = unmuxed_fct("VDD_3V3EXP");
static unmuxed_fct VDD_5V     = unmuxed_fct("VDD_5V");
static unmuxed_fct SYS_5V     = unmuxed_fct("SYS_5V");
static unmuxed_fct PWR_BUT    = unmuxed_fct("PWR_BUT");
static unmuxed_fct SYS_RESETn = unmuxed_fct("SYS_RESETn");
static unmuxed_fct VADC       = unmuxed_fct("VADC");
static unmuxed_fct AGND       = unmuxed_fct("AGND");
static unmuxed_fct AIN0       = unmuxed_fct("AIN0");
static unmuxed_fct AIN1       = unmuxed_fct("AIN1");
static unmuxed_fct AIN2       = unmuxed_fct("AIN2");
static unmuxed_fct AIN3       = unmuxed_fct("AIN3");
static unmuxed_fct AIN4       = unmuxed_fct("AIN4");
static unmuxed_fct AIN5       = unmuxed_fct("AIN5");
static unmuxed_fct AIN6       = unmuxed_fct("AIN6");


  //
  // See utils/pinmux_gen.pl to generate the bulk of this declarative code
  //
  // Note: The OS seems to support pin muxes that are not exported onto the cape
  //       connectors. Similarly, some documented pin functionalities (e.g. timerN)
  //       appear not to be supported by the OS.
  //


pin_fct* const pin_fct::clkout2         = new pin_fct("clkout2");
pin_fct* const pin_fct::d_can0_rx       = new pin_fct("d_can0_rx");
pin_fct* const pin_fct::d_can0_tx       = new pin_fct("d_can0_tx");
pin_fct* const pin_fct::d_can1_rx       = new pin_fct("d_can1_rx");
pin_fct* const pin_fct::d_can1_tx       = new pin_fct("d_can1_tx");
pin_fct* const pin_fct::eQEP2A_in       = new pin_fct("eQEP2A_in");
pin_fct* const pin_fct::ecap0_in_pwm0_out = new pin_fct("ecap0_in_pwm0_out");
pin_fct* const pin_fct::ecap2_in_pwm2_out = new pin_fct("ecap2_in_pwm2_out");
pin_fct* const pin_fct::ehrpwm0A        = new pin_fct("ehrpwm0A");
pin_fct* const pin_fct::ehrpwm0B        = new pin_fct("ehrpwm0B");
pin_fct* const pin_fct::ehrpwm0_synco   = new pin_fct("ehrpwm0_synco");
pin_fct* const pin_fct::ehrpwm1A        = new pin_fct("ehrpwm1A");
pin_fct* const pin_fct::ehrpwm1B        = new pin_fct("ehrpwm1B");
pin_fct* const pin_fct::ehrpwm1_tripzone_input = new pin_fct("ehrpwm1_tripzone_input");
pin_fct* const pin_fct::ehrpwm2A        = new pin_fct("ehrpwm2A");
pin_fct* const pin_fct::ehrpwm2B        = new pin_fct("ehrpwm2B");
pin_fct* const pin_fct::ehrpwm2_tripzone_input = new pin_fct("ehrpwm2_tripzone_input");
pin_fct* const pin_fct::eqep2B_in       = new pin_fct("eqep2B_in");
pin_fct* const pin_fct::eqep2_index     = new pin_fct("eqep2_index");
pin_fct* const pin_fct::eqep2_strobe    = new pin_fct("eqep2_strobe");
pin_fct* const pin_fct::eqep2a_in       = new pin_fct("eqep2a_in");
pin_fct* const pin_fct::eqep2b_in       = new pin_fct("eqep2b_in");
pin_fct* const pin_fct::gmii2_rxdv      = new pin_fct("gmii2_rxdv");
pin_fct* const pin_fct::gmii2_txd2      = new pin_fct("gmii2_txd2");
pin_fct* const pin_fct::gmii2_txd3      = new pin_fct("gmii2_txd3");
pin_fct* const pin_fct::gmii2_txen      = new pin_fct("gmii2_txen");
pin_fct* const pin_fct::gpio0_10        = new pin_fct("gpio0_10");
pin_fct* const pin_fct::gpio0_11        = new pin_fct("gpio0_11");
pin_fct* const pin_fct::gpio0_12        = new pin_fct("gpio0_12");
pin_fct* const pin_fct::gpio0_13        = new pin_fct("gpio0_13");
pin_fct* const pin_fct::gpio0_14        = new pin_fct("gpio0_14");
pin_fct* const pin_fct::gpio0_15        = new pin_fct("gpio0_15");
pin_fct* const pin_fct::gpio0_2         = new pin_fct("gpio0_2");
pin_fct* const pin_fct::gpio0_20        = new pin_fct("gpio0_20");
pin_fct* const pin_fct::gpio0_22        = new pin_fct("gpio0_22");
pin_fct* const pin_fct::gpio0_23        = new pin_fct("gpio0_23");
pin_fct* const pin_fct::gpio0_26        = new pin_fct("gpio0_26");
pin_fct* const pin_fct::gpio0_27        = new pin_fct("gpio0_27");
pin_fct* const pin_fct::gpio0_3         = new pin_fct("gpio0_3");
pin_fct* const pin_fct::gpio0_30        = new pin_fct("gpio0_30");
pin_fct* const pin_fct::gpio0_31        = new pin_fct("gpio0_31");
pin_fct* const pin_fct::gpio0_4         = new pin_fct("gpio0_4");
pin_fct* const pin_fct::gpio0_5         = new pin_fct("gpio0_5");
pin_fct* const pin_fct::gpio0_7         = new pin_fct("gpio0_7");
pin_fct* const pin_fct::gpio0_8         = new pin_fct("gpio0_8");
pin_fct* const pin_fct::gpio0_9         = new pin_fct("gpio0_9");
pin_fct* const pin_fct::gpio1_0         = new pin_fct("gpio1_0");
pin_fct* const pin_fct::gpio1_1         = new pin_fct("gpio1_1");
pin_fct* const pin_fct::gpio1_12        = new pin_fct("gpio1_12");
pin_fct* const pin_fct::gpio1_13        = new pin_fct("gpio1_13");
pin_fct* const pin_fct::gpio1_14        = new pin_fct("gpio1_14");
pin_fct* const pin_fct::gpio1_15        = new pin_fct("gpio1_15");
pin_fct* const pin_fct::gpio1_16        = new pin_fct("gpio1_16");
pin_fct* const pin_fct::gpio1_17        = new pin_fct("gpio1_17");
pin_fct* const pin_fct::gpio1_18        = new pin_fct("gpio1_18");
pin_fct* const pin_fct::gpio1_19        = new pin_fct("gpio1_19");
pin_fct* const pin_fct::gpio1_2         = new pin_fct("gpio1_2");
pin_fct* const pin_fct::gpio1_28        = new pin_fct("gpio1_28");
pin_fct* const pin_fct::gpio1_29        = new pin_fct("gpio1_29");
pin_fct* const pin_fct::gpio1_3         = new pin_fct("gpio1_3");
pin_fct* const pin_fct::gpio1_30        = new pin_fct("gpio1_30");
pin_fct* const pin_fct::gpio1_31        = new pin_fct("gpio1_31");
pin_fct* const pin_fct::gpio1_4         = new pin_fct("gpio1_4");
pin_fct* const pin_fct::gpio1_5         = new pin_fct("gpio1_5");
pin_fct* const pin_fct::gpio1_6         = new pin_fct("gpio1_6");
pin_fct* const pin_fct::gpio1_7         = new pin_fct("gpio1_7");
pin_fct* const pin_fct::gpio2_1         = new pin_fct("gpio2_1");
pin_fct* const pin_fct::gpio2_10        = new pin_fct("gpio2_10");
pin_fct* const pin_fct::gpio2_11        = new pin_fct("gpio2_11");
pin_fct* const pin_fct::gpio2_12        = new pin_fct("gpio2_12");
pin_fct* const pin_fct::gpio2_13        = new pin_fct("gpio2_13");
pin_fct* const pin_fct::gpio2_14        = new pin_fct("gpio2_14");
pin_fct* const pin_fct::gpio2_15        = new pin_fct("gpio2_15");
pin_fct* const pin_fct::gpio2_16        = new pin_fct("gpio2_16");
pin_fct* const pin_fct::gpio2_17        = new pin_fct("gpio2_17");
pin_fct* const pin_fct::gpio2_22        = new pin_fct("gpio2_22");
pin_fct* const pin_fct::gpio2_23        = new pin_fct("gpio2_23");
pin_fct* const pin_fct::gpio2_24        = new pin_fct("gpio2_24");
pin_fct* const pin_fct::gpio2_25        = new pin_fct("gpio2_25");
pin_fct* const pin_fct::gpio2_3         = new pin_fct("gpio2_3");
pin_fct* const pin_fct::gpio2_4         = new pin_fct("gpio2_4");
pin_fct* const pin_fct::gpio2_5         = new pin_fct("gpio2_5");
pin_fct* const pin_fct::gpio2_6         = new pin_fct("gpio2_6");
pin_fct* const pin_fct::gpio2_7         = new pin_fct("gpio2_7");
pin_fct* const pin_fct::gpio2_8         = new pin_fct("gpio2_8");
pin_fct* const pin_fct::gpio2_9         = new pin_fct("gpio2_9");
pin_fct* const pin_fct::gpio3_14        = new pin_fct("gpio3_14");
pin_fct* const pin_fct::gpio3_15        = new pin_fct("gpio3_15");
pin_fct* const pin_fct::gpio3_16        = new pin_fct("gpio3_16");
pin_fct* const pin_fct::gpio3_17        = new pin_fct("gpio3_17");
pin_fct* const pin_fct::gpio3_19        = new pin_fct("gpio3_19");
pin_fct* const pin_fct::gpio3_21        = new pin_fct("gpio3_21");
pin_fct* const pin_fct::gpmc_a0         = new pin_fct("gpmc_a0");
pin_fct* const pin_fct::gpmc_a1         = new pin_fct("gpmc_a1");
pin_fct* const pin_fct::gpmc_a10        = new pin_fct("gpmc_a10");
pin_fct* const pin_fct::gpmc_a11        = new pin_fct("gpmc_a11");
pin_fct* const pin_fct::gpmc_a12        = new pin_fct("gpmc_a12");
pin_fct* const pin_fct::gpmc_a13        = new pin_fct("gpmc_a13");
pin_fct* const pin_fct::gpmc_a14        = new pin_fct("gpmc_a14");
pin_fct* const pin_fct::gpmc_a15        = new pin_fct("gpmc_a15");
pin_fct* const pin_fct::gpmc_a16        = new pin_fct("gpmc_a16");
pin_fct* const pin_fct::gpmc_a17        = new pin_fct("gpmc_a17");
pin_fct* const pin_fct::gpmc_a18        = new pin_fct("gpmc_a18");
pin_fct* const pin_fct::gpmc_a19        = new pin_fct("gpmc_a19");
pin_fct* const pin_fct::gpmc_a2         = new pin_fct("gpmc_a2");
pin_fct* const pin_fct::gpmc_a3         = new pin_fct("gpmc_a3");
pin_fct* const pin_fct::gpmc_a4         = new pin_fct("gpmc_a4");
pin_fct* const pin_fct::gpmc_a5         = new pin_fct("gpmc_a5");
pin_fct* const pin_fct::gpmc_a6         = new pin_fct("gpmc_a6");
pin_fct* const pin_fct::gpmc_a7         = new pin_fct("gpmc_a7");
pin_fct* const pin_fct::gpmc_a8         = new pin_fct("gpmc_a8");
pin_fct* const pin_fct::gpmc_a9         = new pin_fct("gpmc_a9");
pin_fct* const pin_fct::gpmc_ad0        = new pin_fct("gpmc_ad0");
pin_fct* const pin_fct::gpmc_ad1        = new pin_fct("gpmc_ad1");
pin_fct* const pin_fct::gpmc_ad10       = new pin_fct("gpmc_ad10");
pin_fct* const pin_fct::gpmc_ad11       = new pin_fct("gpmc_ad11");
pin_fct* const pin_fct::gpmc_ad12       = new pin_fct("gpmc_ad12");
pin_fct* const pin_fct::gpmc_ad13       = new pin_fct("gpmc_ad13");
pin_fct* const pin_fct::gpmc_ad14       = new pin_fct("gpmc_ad14");
pin_fct* const pin_fct::gpmc_ad15       = new pin_fct("gpmc_ad15");
pin_fct* const pin_fct::gpmc_ad2        = new pin_fct("gpmc_ad2");
pin_fct* const pin_fct::gpmc_ad3        = new pin_fct("gpmc_ad3");
pin_fct* const pin_fct::gpmc_ad4        = new pin_fct("gpmc_ad4");
pin_fct* const pin_fct::gpmc_ad5        = new pin_fct("gpmc_ad5");
pin_fct* const pin_fct::gpmc_ad6        = new pin_fct("gpmc_ad6");
pin_fct* const pin_fct::gpmc_ad7        = new pin_fct("gpmc_ad7");
pin_fct* const pin_fct::gpmc_ad8        = new pin_fct("gpmc_ad8");
pin_fct* const pin_fct::gpmc_ad9        = new pin_fct("gpmc_ad9");
pin_fct* const pin_fct::gpmc_advn_ale   = new pin_fct("gpmc_advn_ale");
pin_fct* const pin_fct::gpmc_be1n       = new pin_fct("gpmc_be1n");
pin_fct* const pin_fct::gpmc_ben0_cle   = new pin_fct("gpmc_ben0_cle");
pin_fct* const pin_fct::gpmc_ben1       = new pin_fct("gpmc_ben1");
pin_fct* const pin_fct::gpmc_clk        = new pin_fct("gpmc_clk");
pin_fct* const pin_fct::gpmc_csn0       = new pin_fct("gpmc_csn0");
pin_fct* const pin_fct::gpmc_csn1       = new pin_fct("gpmc_csn1");
pin_fct* const pin_fct::gpmc_csn2       = new pin_fct("gpmc_csn2");
pin_fct* const pin_fct::gpmc_oen_ren    = new pin_fct("gpmc_oen_ren");
pin_fct* const pin_fct::gpmc_wait0      = new pin_fct("gpmc_wait0");
pin_fct* const pin_fct::gpmc_wen        = new pin_fct("gpmc_wen");
pin_fct* const pin_fct::gpmc_wpn        = new pin_fct("gpmc_wpn");
pin_fct* const pin_fct::i2c1_scl        = new pin_fct("i2c1_scl");
pin_fct* const pin_fct::i2c1_sda        = new pin_fct("i2c1_sda");
pin_fct* const pin_fct::i2c2_scl        = new pin_fct("i2c2_scl");
pin_fct* const pin_fct::i2c2_sda        = new pin_fct("i2c2_sda");
pin_fct* const pin_fct::lcd_ac_bias_en  = new pin_fct("lcd_ac_bias_en");
pin_fct* const pin_fct::lcd_data0       = new pin_fct("lcd_data0");
pin_fct* const pin_fct::lcd_data1       = new pin_fct("lcd_data1");
pin_fct* const pin_fct::lcd_data10      = new pin_fct("lcd_data10");
pin_fct* const pin_fct::lcd_data11      = new pin_fct("lcd_data11");
pin_fct* const pin_fct::lcd_data12      = new pin_fct("lcd_data12");
pin_fct* const pin_fct::lcd_data13      = new pin_fct("lcd_data13");
pin_fct* const pin_fct::lcd_data14      = new pin_fct("lcd_data14");
pin_fct* const pin_fct::lcd_data15      = new pin_fct("lcd_data15");
pin_fct* const pin_fct::lcd_data16      = new pin_fct("lcd_data16");
pin_fct* const pin_fct::lcd_data17      = new pin_fct("lcd_data17");
pin_fct* const pin_fct::lcd_data18      = new pin_fct("lcd_data18");
pin_fct* const pin_fct::lcd_data19      = new pin_fct("lcd_data19");
pin_fct* const pin_fct::lcd_data2       = new pin_fct("lcd_data2");
pin_fct* const pin_fct::lcd_data20      = new pin_fct("lcd_data20");
pin_fct* const pin_fct::lcd_data21      = new pin_fct("lcd_data21");
pin_fct* const pin_fct::lcd_data22      = new pin_fct("lcd_data22");
pin_fct* const pin_fct::lcd_data23      = new pin_fct("lcd_data23");
pin_fct* const pin_fct::lcd_data3       = new pin_fct("lcd_data3");
pin_fct* const pin_fct::lcd_data4       = new pin_fct("lcd_data4");
pin_fct* const pin_fct::lcd_data5       = new pin_fct("lcd_data5");
pin_fct* const pin_fct::lcd_data6       = new pin_fct("lcd_data6");
pin_fct* const pin_fct::lcd_data7       = new pin_fct("lcd_data7");
pin_fct* const pin_fct::lcd_data8       = new pin_fct("lcd_data8");
pin_fct* const pin_fct::lcd_data9       = new pin_fct("lcd_data9");
pin_fct* const pin_fct::lcd_hsync       = new pin_fct("lcd_hsync");
pin_fct* const pin_fct::lcd_memory_clk_mux = new pin_fct("lcd_memory_clk_mux");
pin_fct* const pin_fct::lcd_pclk        = new pin_fct("lcd_pclk");
pin_fct* const pin_fct::lcd_vsync       = new pin_fct("lcd_vsync");
pin_fct* const pin_fct::mcasp0_aclkr    = new pin_fct("mcasp0_aclkr");
pin_fct* const pin_fct::mcasp0_aclkx    = new pin_fct("mcasp0_aclkx");
pin_fct* const pin_fct::mcasp0_ahclkr   = new pin_fct("mcasp0_ahclkr");
pin_fct* const pin_fct::mcasp0_ahclkx   = new pin_fct("mcasp0_ahclkx");
pin_fct* const pin_fct::mcasp0_axr0     = new pin_fct("mcasp0_axr0");
pin_fct* const pin_fct::mcasp0_axr1     = new pin_fct("mcasp0_axr1");
pin_fct* const pin_fct::mcasp0_axr2     = new pin_fct("mcasp0_axr2");
pin_fct* const pin_fct::mcasp0_axr3     = new pin_fct("mcasp0_axr3");
pin_fct* const pin_fct::mcasp0_fsr      = new pin_fct("mcasp0_fsr");
pin_fct* const pin_fct::mcasp0_fsx      = new pin_fct("mcasp0_fsx");
pin_fct* const pin_fct::mcasp1_axr1     = new pin_fct("mcasp1_axr1");
pin_fct* const pin_fct::mcasp1_fsx      = new pin_fct("mcasp1_fsx");
pin_fct* const pin_fct::mii2_col        = new pin_fct("mii2_col");
pin_fct* const pin_fct::mii2_crs        = new pin_fct("mii2_crs");
pin_fct* const pin_fct::mii2_rxerr      = new pin_fct("mii2_rxerr");
pin_fct* const pin_fct::mmc0_sdcd       = new pin_fct("mmc0_sdcd");
pin_fct* const pin_fct::mmc0_sdwp       = new pin_fct("mmc0_sdwp");
pin_fct* const pin_fct::mmc1_clk        = new pin_fct("mmc1_clk");
pin_fct* const pin_fct::mmc1_cmd        = new pin_fct("mmc1_cmd");
pin_fct* const pin_fct::mmc1_dat0       = new pin_fct("mmc1_dat0");
pin_fct* const pin_fct::mmc1_dat1       = new pin_fct("mmc1_dat1");
pin_fct* const pin_fct::mmc1_dat2       = new pin_fct("mmc1_dat2");
pin_fct* const pin_fct::mmc1_dat3       = new pin_fct("mmc1_dat3");
pin_fct* const pin_fct::mmc1_dat4       = new pin_fct("mmc1_dat4");
pin_fct* const pin_fct::mmc1_dat5       = new pin_fct("mmc1_dat5");
pin_fct* const pin_fct::mmc1_dat6       = new pin_fct("mmc1_dat6");
pin_fct* const pin_fct::mmc1_dat7       = new pin_fct("mmc1_dat7");
pin_fct* const pin_fct::mmc1_sdcd       = new pin_fct("mmc1_sdcd");
pin_fct* const pin_fct::mmc1_sdwp       = new pin_fct("mmc1_sdwp");
pin_fct* const pin_fct::mmc2_clk        = new pin_fct("mmc2_clk");
pin_fct* const pin_fct::mmc2_dat0       = new pin_fct("mmc2_dat0");
pin_fct* const pin_fct::mmc2_dat1       = new pin_fct("mmc2_dat1");
pin_fct* const pin_fct::mmc2_dat2       = new pin_fct("mmc2_dat2");
pin_fct* const pin_fct::mmc2_dat3       = new pin_fct("mmc2_dat3");
pin_fct* const pin_fct::mmc2_dat4       = new pin_fct("mmc2_dat4");
pin_fct* const pin_fct::mmc2_dat5       = new pin_fct("mmc2_dat5");
pin_fct* const pin_fct::mmc2_dat6       = new pin_fct("mmc2_dat6");
pin_fct* const pin_fct::mmc2_dat7       = new pin_fct("mmc2_dat7");
pin_fct* const pin_fct::mmc2_sdcd       = new pin_fct("mmc2_sdcd");
pin_fct* const pin_fct::mmc2_sdwp       = new pin_fct("mmc2_sdwp");
pin_fct* const pin_fct::rgmii2_rctl     = new pin_fct("rgmii2_rctl");
pin_fct* const pin_fct::rgmii2_tctl     = new pin_fct("rgmii2_tctl");
pin_fct* const pin_fct::rgmii2_td2      = new pin_fct("rgmii2_td2");
pin_fct* const pin_fct::rgmii2_td3      = new pin_fct("rgmii2_td3");
pin_fct* const pin_fct::rmii2_crs_dv    = new pin_fct("rmii2_crs_dv");
pin_fct* const pin_fct::rmii2_rxerr     = new pin_fct("rmii2_rxerr");
pin_fct* const pin_fct::rmii2_txen      = new pin_fct("rmii2_txen");
pin_fct* const pin_fct::spi0_cs0        = new pin_fct("spi0_cs0");
pin_fct* const pin_fct::spi0_d0         = new pin_fct("spi0_d0");
pin_fct* const pin_fct::spi0_d1         = new pin_fct("spi0_d1");
pin_fct* const pin_fct::spi0_sclk       = new pin_fct("spi0_sclk");
pin_fct* const pin_fct::spi1_cs0        = new pin_fct("spi1_cs0");
pin_fct* const pin_fct::spi1_cs1        = new pin_fct("spi1_cs1");
pin_fct* const pin_fct::spi1_d0         = new pin_fct("spi1_d0");
pin_fct* const pin_fct::spi1_d1         = new pin_fct("spi1_d1");
pin_fct* const pin_fct::spi1_sclk       = new pin_fct("spi1_sclk");
pin_fct* const pin_fct::uart1_ctsn      = new pin_fct("uart1_ctsn");
pin_fct* const pin_fct::uart1_rtsn      = new pin_fct("uart1_rtsn");
pin_fct* const pin_fct::uart1_rxd       = new pin_fct("uart1_rxd");
pin_fct* const pin_fct::uart1_txd       = new pin_fct("uart1_txd");
pin_fct* const pin_fct::uart2_ctsn      = new pin_fct("uart2_ctsn");
pin_fct* const pin_fct::uart2_rtsn      = new pin_fct("uart2_rtsn");
pin_fct* const pin_fct::uart2_rxd       = new pin_fct("uart2_rxd");
pin_fct* const pin_fct::uart2_txd       = new pin_fct("uart2_txd");
pin_fct* const pin_fct::uart3_ctsn      = new pin_fct("uart3_ctsn");
pin_fct* const pin_fct::uart3_txd       = new pin_fct("uart3_txd");
pin_fct* const pin_fct::xdma_event_intr1 = new pin_fct("xdma_event_intr1");
pin_fct* const pin_fct::xdma_event_intr2 = new pin_fct("xdma_event_intr2");


pin* pin::m_P8[46] = {new unmuxed_pin("P8_1", &GND, pin::OUT, pin::NONE),
		      new unmuxed_pin("P8_2", &GND, pin::OUT, pin::NONE),
		      new gpio("P8_3", "gpmc_ad6"  ,  1, 6, pin_fct::gpmc_ad6       , pin_fct::mmc1_dat6      , NULL                    , NULL                    , NULL                    , NULL                    , NULL                    , pin_fct::gpio1_6        ,7, pin::IN, pin::NONE),
		      new gpio("P8_4", "gpmc_ad7"  ,  1, 7, pin_fct::gpmc_ad7       , pin_fct::mmc1_dat7      , NULL                    , NULL                    , NULL                    , NULL                    , NULL                    , pin_fct::gpio1_7        ,0, pin::IN, pin::NONE),
		      new gpio("P8_5", "gpmc_ad2"  ,  1, 2, pin_fct::gpmc_ad2       , pin_fct::mmc1_dat2      , NULL                    , NULL                    , NULL                    , NULL                    , NULL                    , pin_fct::gpio1_2        ,0, pin::IN, pin::NONE),
		      new gpio("P8_6", "gpmc_ad3"  ,  1, 3, pin_fct::gpmc_ad3       , pin_fct::mmc1_dat3      , NULL                    , NULL                    , NULL                    , NULL                    , NULL                    , pin_fct::gpio1_3        ,7, pin::IN, pin::NONE),
 /* ? */	      new pin("P8_7", "gpmc_advn_ale",  pin_fct::gpmc_advn_ale  , NULL                    , NULL                    , NULL                    , NULL                    , NULL                    , NULL                    , NULL                    ,0, pin::OUT, pin::NONE),
                      new gpio("P8_8", "gpmc_oen_ren",  2, 3, pin_fct::gpmc_oen_ren   , NULL                    , NULL                    , NULL                    , NULL                    , NULL                    , NULL                    , pin_fct::gpio2_3        ,0, pin::OUT, pin::NONE),
		      new gpio("P8_9", "gpmc_ben0_cle",  2, 5, pin_fct::gpmc_ben0_cle  , NULL                    , NULL                    , NULL                    , NULL                    , NULL                    , NULL                    , pin_fct::gpio2_5        ,0, pin::OUT, pin::NONE),
		      new gpio("P8_10", "gpmc_wen"  ,  2, 4, pin_fct::gpmc_wen       , NULL                    , NULL                    , NULL                    , NULL                    , NULL                    , NULL                    , pin_fct::gpio2_4        ,0, pin::OUT, pin::NONE),
		      new gpio("P8_11", "gpmc_ad13" ,  1, 13, pin_fct::gpmc_ad13      , pin_fct::lcd_data18     , pin_fct::mmc1_dat5      , pin_fct::mmc2_dat1      , pin_fct::eqep2B_in      , NULL                    , NULL                    , pin_fct::gpio1_13       ,7, pin::IN, pin::NONE),
		      new gpio("P8_12", "gpmc_ad12" ,  1, 12, pin_fct::gpmc_ad12      , pin_fct::lcd_data19     , pin_fct::mmc1_dat4      , pin_fct::mmc2_dat0      , pin_fct::eqep2a_in      , NULL                    , NULL                    , pin_fct::gpio1_12       ,7, pin::IN, pin::NONE),
		      new gpio("P8_13", "gpmc_ad9"  ,  0, 23, pin_fct::gpmc_ad9       , pin_fct::lcd_data22     , pin_fct::mmc1_dat1      , pin_fct::mmc2_dat5      , pin_fct::ehrpwm2B       , NULL                    , NULL                    , pin_fct::gpio0_23       ,7, pin::IN, pin::NONE),
		      new gpio("P8_14", "gpmc_ad10" ,  0, 26, pin_fct::gpmc_ad10      , pin_fct::lcd_data21     , pin_fct::mmc1_dat2      , pin_fct::mmc2_dat6      , pin_fct::ehrpwm2_tripzone_input , NULL                    , NULL                    , pin_fct::gpio0_26       ,7, pin::IN, pin::NONE),
		      new gpio("P8_15", "gpmc_ad15" ,  1, 15, pin_fct::gpmc_ad15      , pin_fct::lcd_data16     , pin_fct::mmc1_dat7      , pin_fct::mmc2_dat3      , pin_fct::eqep2_strobe   , NULL                    , NULL                    , pin_fct::gpio1_15       ,7, pin::IN, pin::NONE),
		      new gpio("P8_16", "gpmc_ad14" ,  1, 14, pin_fct::gpmc_ad14      , pin_fct::lcd_data17     , pin_fct::mmc1_dat6      , pin_fct::mmc2_dat2      , pin_fct::eqep2_index    , NULL                    , NULL                    , pin_fct::gpio1_14       ,7, pin::IN, pin::NONE),
		      new gpio("P8_17", "gpmc_ad11" ,  0, 27, pin_fct::gpmc_ad11      , pin_fct::lcd_data20     , pin_fct::mmc1_dat3      , pin_fct::mmc2_dat7      , pin_fct::ehrpwm0_synco  , NULL                    , NULL                    , pin_fct::gpio0_27       ,7, pin::IN, pin::NONE),
		      new gpio("P8_18", "gpmc_clk"  ,  2, 1,  pin_fct::gpmc_clk       , pin_fct::lcd_memory_clk_mux , NULL                    , pin_fct::mmc2_clk       , NULL                    , NULL                    , pin_fct::mcasp0_fsr     , pin_fct::gpio2_1        ,7, pin::IN, pin::NONE),
		      new gpio("P8_19", "gpmc_ad8"  ,  0, 22, pin_fct::gpmc_ad8       , pin_fct::lcd_data23     , pin_fct::mmc1_dat0      , pin_fct::mmc2_dat4      , pin_fct::ehrpwm2A       , NULL                    , NULL                    , pin_fct::gpio0_22       ,7, pin::IN, pin::NONE),
		      new gpio("P8_20", "gpmc_csn2" ,  1, 31, pin_fct::gpmc_csn2      , pin_fct::gpmc_be1n      , pin_fct::mmc1_cmd       , NULL                    , NULL                    , NULL                    , NULL                    , pin_fct::gpio1_31       ,7, pin::IN, pin::NONE),
		      new gpio("P8_21", "gpmc_csn1" ,  1, 30, pin_fct::gpmc_csn1      , pin_fct::gpmc_clk       , pin_fct::mmc1_clk       , NULL                    , NULL                    , NULL                    , NULL                    , pin_fct::gpio1_30       ,7, pin::IN, pin::NONE),
		      new gpio("P8_22", "gpmc_ad5"  ,  1, 5 , pin_fct::gpmc_ad5       , pin_fct::mmc1_dat5      , NULL                    , NULL                    , NULL                    , NULL                    , NULL                    , pin_fct::gpio1_5        ,0, pin::IN, pin::NONE),
		      new gpio("P8_23", "gpmc_ad4"  ,  1, 4 , pin_fct::gpmc_ad4       , pin_fct::mmc1_dat4      , NULL                    , NULL                    , NULL                    , NULL                    , NULL                    , pin_fct::gpio1_4        ,0, pin::IN, pin::NONE),
		      new gpio("P8_24", "gpmc_ad1"  ,  1, 1 , pin_fct::gpmc_ad1       , pin_fct::mmc1_dat1      , NULL                    , NULL                    , NULL                    , NULL                    , NULL                    , pin_fct::gpio1_1        ,0, pin::IN, pin::NONE),
		      new gpio("P8_25", "gpmc_ad0"  ,  1, 0 , pin_fct::gpmc_ad0       , pin_fct::mmc1_dat0      , NULL                    , NULL                    , NULL                    , NULL                    , NULL                    , pin_fct::gpio1_0        ,0, pin::IN, pin::NONE),
		      new gpio("P8_26", "gpmc_csn0" ,  1, 29, pin_fct::gpmc_csn0      , NULL                    , NULL                    , NULL                    , NULL                    , NULL                    , NULL                    , pin_fct::gpio1_29       ,0, pin::OUT, pin::NONE),
		      new gpio("P8_27", "lcd_vsync" ,  2, 22, pin_fct::lcd_vsync      , pin_fct::gpmc_a8        , NULL                    , NULL                    , NULL                    , NULL                    , NULL                    , pin_fct::gpio2_22       ,7, pin::IN, pin::NONE),
		      new gpio("P8_28", "lcd_pclk"  ,  2, 24, pin_fct::lcd_pclk       , pin_fct::gpmc_a10       , NULL                    , NULL                    , NULL                    , NULL                    , NULL                    , pin_fct::gpio2_24       ,7, pin::IN, pin::NONE),
		      new gpio("P8_29", "lcd_hsync" ,  2, 23, pin_fct::lcd_hsync      , pin_fct::gpmc_a9        , NULL                    , NULL                    , NULL                    , NULL                    , NULL                    , pin_fct::gpio2_23       ,7, pin::IN, pin::NONE),
		      new gpio("P8_30", "lcd_ac_bias_en",  2, 25, pin_fct::lcd_ac_bias_en , pin_fct::gpmc_a11       , NULL                    , NULL                    , NULL                    , NULL                    , NULL                    , pin_fct::gpio2_25       ,7, pin::IN, pin::NONE),
		      new gpio("P8_31", "lcd_data14",  0, 10, pin_fct::lcd_data14     , pin_fct::gpmc_a18       , NULL                    , pin_fct::mcasp0_axr1    , NULL                    , NULL                    , NULL                    , pin_fct::gpio0_10       ,0, pin::OUT, pin::NONE),
		      new gpio("P8_32", "lcd_data15",  0, 11, pin_fct::lcd_data15     , pin_fct::gpmc_a19       , NULL                    , pin_fct::mcasp0_ahclkx  , pin_fct::mcasp0_axr3    , NULL                    , NULL                    , pin_fct::gpio0_11       ,0, pin::OUT, pin::NONE),
		      new gpio("P8_33", "lcd_data13",  0, 9 , pin_fct::lcd_data13     , pin_fct::gpmc_a17       , NULL                    , pin_fct::mcasp0_fsr     , pin_fct::mcasp0_axr3    , NULL                    , NULL                    , pin_fct::gpio0_9        ,0, pin::OUT, pin::NONE),
		      new gpio("P8_34", "lcd_data11",  2, 17, pin_fct::lcd_data11     , pin_fct::gpmc_a15       , NULL                    , pin_fct::mcasp0_ahclkr  , pin_fct::mcasp0_axr2    , NULL                    , NULL                    , pin_fct::gpio2_17       ,0, pin::OUT, pin::NONE),
		      new gpio("P8_35", "lcd_data12",  0, 8 , pin_fct::lcd_data12     , pin_fct::gpmc_a16       , NULL                    , pin_fct::mcasp0_aclkr   , pin_fct::mcasp0_axr2    , NULL                    , NULL                    , pin_fct::gpio0_8        ,0, pin::OUT, pin::NONE),
		      new gpio("P8_36", "lcd_data10",  2, 16, pin_fct::lcd_data10     , pin_fct::gpmc_a14       , pin_fct::ehrpwm1A       , pin_fct::mcasp0_axr0    , pin_fct::mcasp0_axr0    , NULL                    , pin_fct::uart3_ctsn     , pin_fct::gpio2_16       ,0, pin::OUT, pin::NONE),
		      new gpio("P8_37", "lcd_data8" ,  2, 14, pin_fct::lcd_data8      , pin_fct::gpmc_a12       , NULL                    , pin_fct::mcasp0_aclkx   , NULL                    , NULL                    , pin_fct::uart2_ctsn     , pin_fct::gpio2_14       ,0, pin::OUT, pin::NONE),
		      new gpio("P8_38", "lcd_data9" ,  2, 15, pin_fct::lcd_data9      , pin_fct::gpmc_a13       , NULL                    , pin_fct::mcasp0_fsx     , NULL                    , NULL                    , pin_fct::uart2_rtsn     , pin_fct::gpio2_15       ,0, pin::OUT, pin::NONE),
		      new gpio("P8_39", "lcd_data6" ,  2, 12, pin_fct::lcd_data6      , pin_fct::gpmc_a6        , NULL                    , pin_fct::eqep2_index    , NULL                    , NULL                    , NULL                    , pin_fct::gpio2_12       ,0, pin::OUT, pin::NONE),
		      new gpio("P8_40", "lcd_data7" ,  2, 13, pin_fct::lcd_data7      , pin_fct::gpmc_a7        , NULL                    , pin_fct::eqep2_strobe   , NULL                    , NULL                    , NULL                    , pin_fct::gpio2_13       ,0, pin::OUT, pin::NONE),
		      new gpio("P8_41", "lcd_data4" ,  2, 10, pin_fct::lcd_data4      , pin_fct::gpmc_a4        , NULL                    , pin_fct::eQEP2A_in      , NULL                    , NULL                    , NULL                    , pin_fct::gpio2_10       ,0, pin::OUT, pin::NONE),
		      new gpio("P8_42", "lcd_data5" ,  2, 11, pin_fct::lcd_data5      , pin_fct::gpmc_a5        , NULL                    , pin_fct::eqep2b_in      , NULL                    , NULL                    , NULL                    , pin_fct::gpio2_11       ,0, pin::OUT, pin::NONE),
		      new gpio("P8_43", "lcd_data2" ,  2, 8 , pin_fct::lcd_data2      , pin_fct::gpmc_a2        , NULL                    , pin_fct::ehrpwm2_tripzone_input , NULL                    , NULL                    , NULL                    , pin_fct::gpio2_8        ,0, pin::OUT, pin::NONE),
		      new gpio("P8_44", "lcd_data3" ,  2, 9 , pin_fct::lcd_data3      , pin_fct::gpmc_a3        , NULL                    , pin_fct::ehrpwm0_synco  , NULL                    , NULL                    , NULL                    , pin_fct::gpio2_9        ,0, pin::OUT, pin::NONE),
		      new gpio("P8_45", "lcd_data0" ,  2, 6 , pin_fct::lcd_data0      , pin_fct::gpmc_a0        , NULL                    , pin_fct::ehrpwm2A       , NULL                    , NULL                    , NULL                    , pin_fct::gpio2_6        ,0, pin::OUT, pin::NONE),
		      new gpio("P8_46", "lcd_data1" ,  2, 7 , pin_fct::lcd_data1      , pin_fct::gpmc_a1        , NULL                    , pin_fct::ehrpwm2B       , NULL                    , NULL                    , NULL                    , pin_fct::gpio2_7        ,0, pin::OUT, pin::NONE)};

pin* pin::m_P9[46] = {new unmuxed_pin("P9_1", &GND, pin::OUT, pin::NONE),
		      new unmuxed_pin("P9_2", &GND, pin::OUT, pin::NONE),
		      new unmuxed_pin("P9_3", &VDD_3V3EXP, pin::OUT, pin::NONE),
		      new unmuxed_pin("P9_4", &VDD_3V3EXP, pin::OUT, pin::NONE),
		      new unmuxed_pin("P9_5", &VDD_5V, pin::OUT, pin::NONE),
		      new unmuxed_pin("P9_6", &VDD_5V, pin::OUT, pin::NONE),
		      new unmuxed_pin("P9_7", &SYS_5V, pin::OUT, pin::NONE),
		      new unmuxed_pin("P9_8", &SYS_5V, pin::OUT, pin::NONE),
		      new unmuxed_pin("P9_9", &PWR_BUT, pin::OUT, pin::NONE),
		      new unmuxed_pin("P9_10", &SYS_RESETn, pin::OUT, pin::NONE),
		      new gpio("P9_11", "gpmc_wait0",  0, 30, pin_fct::gpmc_wait0     , pin_fct::mii2_crs       , NULL                    , pin_fct::rmii2_crs_dv   , pin_fct::mmc1_sdcd      , NULL                    , NULL                    , pin_fct::gpio0_30       ,0, pin::IN, pin::NONE),
		      new gpio("P9_12", "gpmc_ben1" ,  1, 28, pin_fct::gpmc_ben1      , pin_fct::mii2_col       , NULL                    , pin_fct::mmc2_dat3      , NULL                    , NULL                    , pin_fct::mcasp0_aclkr   , pin_fct::gpio1_28       ,7, pin::IN, pin::NONE),
		      new gpio("P9_13", "gpmc_wpn"  ,  0, 31, pin_fct::gpmc_wpn       , pin_fct::mii2_rxerr     , NULL                    , pin_fct::rmii2_rxerr    , pin_fct::mmc2_sdcd      , NULL                    , NULL                    , pin_fct::gpio0_31       ,7, pin::IN, pin::NONE),
		      new gpio("P9_14", "gpmc_a2"   ,  1, 18, pin_fct::gpmc_a2        , pin_fct::gmii2_txd3     , pin_fct::rgmii2_td3     , pin_fct::mmc2_dat1      , pin_fct::gpmc_a18       , NULL                    , pin_fct::ehrpwm1A       , pin_fct::gpio1_18       ,7, pin::IN, pin::NONE),
		      new gpio("P9_15", "gpmc_a0"   ,  1, 16, pin_fct::gpmc_a0        , pin_fct::gmii2_txen     , pin_fct::rgmii2_tctl    , pin_fct::rmii2_txen     , pin_fct::gpmc_a16       , NULL                    , pin_fct::ehrpwm1_tripzone_input , pin_fct::gpio1_16       ,7, pin::IN, pin::NONE),
		      new gpio("P9_16", "gpmc_a3"   ,  1, 19, pin_fct::gpmc_a3        , pin_fct::gmii2_txd2     , pin_fct::rgmii2_td2     , pin_fct::mmc2_dat2      , pin_fct::gpmc_a19       , NULL                    , pin_fct::ehrpwm1B       , pin_fct::gpio1_19       ,7, pin::IN, pin::NONE),
 /* ? */              new gpio("P9_17", "spi0_cs0"  ,  0, 5 , pin_fct::spi0_cs0       , pin_fct::mmc2_sdwp      , pin_fct::i2c1_scl       , NULL                    , NULL                    , NULL                    , NULL                    , pin_fct::gpio0_5        ,2, pin::IN, pin::NONE),
		      new gpio("P9_18", "spi0_d1"   ,  0, 4 , pin_fct::spi0_d1        , pin_fct::mmc1_sdwp      , pin_fct::i2c1_sda       , NULL                    , NULL                    , NULL                    , NULL                    , pin_fct::gpio0_4        ,2, pin::IN, pin::NONE),
		      new gpio("P9_19", "uart1_rtsn",  0, 13, pin_fct::uart1_rtsn     , NULL                    , pin_fct::d_can0_rx      , pin_fct::i2c2_scl       , pin_fct::spi1_cs1       , NULL                    , NULL                    , pin_fct::gpio0_13       ,3, pin::IN, pin::NONE),
		      new gpio("P9_20", "uart1_ctsn",  0, 12, pin_fct::uart1_ctsn     , NULL                    , pin_fct::d_can0_tx      , pin_fct::i2c2_sda       , pin_fct::spi1_cs0       , NULL                    , NULL                    , pin_fct::gpio0_12       ,3, pin::IN, pin::NONE),
		      new gpio("P9_21", "spi0_d0"   ,  0, 3 , pin_fct::spi0_d0        , pin_fct::uart2_txd      , pin_fct::i2c2_scl       , NULL                    , NULL                    , NULL                    , NULL                    , pin_fct::gpio0_3        ,7, pin::IN, pin::NONE),
		      new gpio("P9_22", "spi0_sclk" ,  0, 2 , pin_fct::spi0_sclk      , pin_fct::uart2_rxd      , pin_fct::i2c2_sda       , NULL                    , NULL                    , NULL                    , NULL                    , pin_fct::gpio0_2        ,7, pin::IN, pin::NONE),
		      new gpio("P9_23", "gpmc_a1"   ,  1, 17, pin_fct::gpmc_a1        , pin_fct::gmii2_rxdv     , pin_fct::rgmii2_rctl    , pin_fct::mmc2_dat0      , pin_fct::gpmc_a17       , NULL                    , pin_fct::ehrpwm0_synco  , pin_fct::gpio1_17       ,7, pin::IN, pin::NONE),
		      new gpio("P9_24", "uart1_txd" ,  0, 15, pin_fct::uart1_txd      , pin_fct::mmc2_sdwp      , pin_fct::d_can1_rx      , pin_fct::i2c1_scl       , NULL                    , NULL                    , NULL                    , pin_fct::gpio0_15       ,7, pin::IN, pin::NONE),
		      new gpio("P9_25", "mcasp0_ahclkx",  3, 21, pin_fct::mcasp0_ahclkx  , NULL                    , pin_fct::mcasp0_axr3    , pin_fct::mcasp1_axr1    , NULL                    , NULL                    , NULL                    , pin_fct::gpio3_21       ,7, pin::IN, pin::NONE),
		      new gpio("P9_26", "uart1_rxd" ,  0, 14, pin_fct::uart1_rxd      , pin_fct::mmc1_sdwp      , pin_fct::d_can1_tx      , pin_fct::i2c1_sda       , NULL                    , NULL                    , NULL                    , pin_fct::gpio0_14       ,7, pin::IN, pin::NONE),
		      new gpio("P9_27", "mcasp0_fsr",  3, 19, pin_fct::mcasp0_fsr     , NULL                    , pin_fct::mcasp0_axr3    , pin_fct::mcasp1_fsx     , NULL                    , NULL                    , NULL                    , pin_fct::gpio3_19       ,7, pin::IN, pin::NONE),
		      new gpio("P9_28", "mcasp0_ahclkr",  3, 17, pin_fct::mcasp0_ahclkr  , NULL                    , pin_fct::mcasp0_axr2    , pin_fct::spi1_cs0       , pin_fct::ecap2_in_pwm2_out , NULL                    , NULL                    , pin_fct::gpio3_17       ,3, pin::IN, pin::NONE),
		      new gpio("P9_29", "mcasp0_fsx",  3, 15, pin_fct::mcasp0_fsx     , pin_fct::ehrpwm0B       , NULL                    , pin_fct::spi1_d0        , pin_fct::mmc1_sdcd      , NULL                    , NULL                    , pin_fct::gpio3_15       ,3, pin::IN, pin::NONE),
		      new gpio("P9_30", "mcasp0_axr0",  3, 16, pin_fct::mcasp0_axr0    , NULL                    , NULL                    , pin_fct::spi1_d1        , pin_fct::mmc2_sdcd      , NULL                    , NULL                    , pin_fct::gpio3_16       ,3, pin::IN, pin::NONE),
		      new gpio("P9_31", "mcasp0_aclkx",  3, 14, pin_fct::mcasp0_aclkx   , pin_fct::ehrpwm0A       , NULL                    , pin_fct::spi1_sclk      , pin_fct::mmc0_sdcd      , NULL                    , NULL                    , pin_fct::gpio3_14       ,3, pin::IN, pin::NONE),
		      new unmuxed_pin("P9_32", &VADC, pin::OUT, pin::NONE),
		      new unmuxed_pin("P9_33", &AIN4, pin::OUT, pin::NONE),
		      new unmuxed_pin("P9_34", &AGND, pin::OUT, pin::NONE),
		      new unmuxed_pin("P9_35", &AIN6, pin::OUT, pin::NONE),
		      new unmuxed_pin("P9_36", &AIN5, pin::OUT, pin::NONE),
		      new unmuxed_pin("P9_37", &AIN2, pin::OUT, pin::NONE),
		      new unmuxed_pin("P9_38", &AIN3, pin::OUT, pin::NONE),
		      new unmuxed_pin("P9_39", &AIN0, pin::OUT, pin::NONE),
		      new unmuxed_pin("P9_40", &AIN1, pin::OUT, pin::NONE),
		      new gpio("P9_41", "xdma_event_intr1",  0, 20, pin_fct::xdma_event_intr1 , NULL                    , NULL                    , pin_fct::clkout2        , NULL                    , NULL                    , NULL                    , pin_fct::gpio0_20       ,3, pin::OUT, pin::NONE),
		      new gpio("P9_42", "ecap0_in_pwm0_out",  0, 7 , pin_fct::ecap0_in_pwm0_out , pin_fct::uart3_txd      , pin_fct::spi1_cs1       , NULL                    , pin_fct::spi1_sclk      , pin_fct::mmc0_sdwp      , pin_fct::xdma_event_intr2 , pin_fct::gpio0_7        ,7, pin::IN, pin::NONE),
		      new unmuxed_pin("P9_43", &GND, pin::OUT, pin::NONE),
		      new unmuxed_pin("P9_44", &GND, pin::OUT, pin::NONE),
		      new unmuxed_pin("P9_45", &GND, pin::OUT, pin::NONE),
		      new unmuxed_pin("P9_46", &GND, pin::OUT, pin::NONE)};

  pin::pin(const char*    name,
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
	   direction_t    dir,
	   pull_t         pulls)
    : m_name(name), m_fct(NULL), m_gpio(mode7), m_locker(NULL), m_key(0)
{
  m_dev = (char*) malloc(strlen(devdir)+32);
  sprintf(m_dev, "%s/%s", devdir, dev);

  // ToDo: Detect actual current mux setting
  switch(init) {
  case 0: m_fct = mode0; break;
  case 1: m_fct = mode1; break;
  case 2: m_fct = mode2; break;
  case 3: m_fct = mode3; break;
  case 4: m_fct = mode4; break;
  case 5: m_fct = mode5; break;
  case 6: m_fct = mode6; break;
  case 7: m_fct = mode7; break;
  }

  if (m_fct == NULL) {
    fprintf(stderr, "ERROR: Pin %s is initialized to NULL functionality.\n", get_name());
    return;
  }

  m_fct->m_pin = this;

  m_pin_can_do(mode0, 0);
  m_pin_can_do(mode1, 1);
  m_pin_can_do(mode2, 2);
  m_pin_can_do(mode3, 3);
  m_pin_can_do(mode4, 4);
  m_pin_can_do(mode5, 5);
  m_pin_can_do(mode6, 6);
  m_pin_can_do(mode7, 7);
}

void
pin::m_pin_can_do(pin_fct* const fct, unsigned char mode)
{
  int i = 0;
  if (fct == NULL) return;

  pin** p = fct->m_pins;
  while (*p) {
    p++;
    i++;
  }
  fct->m_pins[i] = this;
  fct->m_mode[i] = mode;
}

pin*
pin::P8(unsigned char n)
{
  if (n < 1 || n > 46) {
    fprintf(stderr, "ERROR: invalid pin number P8[%d]. Must be in 1..46.\n", n);
    return NULL;
  }

  return m_P8[n-1];
}

pin*
pin::P9(unsigned char n)
{
  if (n < 1 || n > 46) {
    fprintf(stderr, "ERROR: invalid pin number P9[%d]. Must be in 1..46.\n", n);
    return NULL;
  }

  return m_P9[n-1];
}

const char*
pin::get_name()
{
  return m_name;
}

pin_fct*
pin::get_fct()
{
  return m_fct;
}

pin_fct*
pin::get_gpio()
{
  return m_gpio;
}

int
pin::xport(pin_fct* fct, direction_t dir, pull_t pulls)
{
  // Even if already exported here, go ahead as we may be changing direction or pulls
  // if (fct->m_pin == this) return 1;

  // This pin locked?
  if (is_locked()) {
    fprintf(stderr, "ERROR: Pin %s is locked exporting %s function.\n",
	    get_name(), fct->get_name());
    return 0;
  }

  // Can we even export this function here?
  int i = 0;
  unsigned char mode;
  pin** p = fct->m_pins;
  while (*p) {
    if (*p == this) break;
    p++;
    i++;
  }
  if (!*p) {
    fprintf(stderr, "ERROR: Pin %s cannot export %s function.\n",
	    get_name(), fct->get_name());
    return 0;
  }
  mode = fct->m_mode[i];

  // Is it already exported somewhere else?
  if (fct->m_pin != NULL && fct->m_pin != this) {
    if (fct->m_pin->is_locked()) {
      fprintf(stderr, "ERROR: %s function is currently exported by locked pin %s.\n",
	      fct->get_name(), fct->m_pin->get_name());
      return 0;
    }

    // ToDo: Automatically remux previous exporting pin
    fprintf(stderr, "ERROR: %s function is currently exported by pin %s.\n",
	    fct->get_name(), fct->m_pin->get_name());
    return 0;
  }

  // Good to go!
  m_fct->m_pin = NULL;
  m_fct = fct;
  m_fct->m_pin = this;

  // Perform the muxing
  FILE *fp = fopen(m_dev, "w");
  if (fp == NULL) {
    fprintf(stderr, "ERROR: Cannot open %s for writing: ", m_dev);
    perror(0);
    return 0;
  }

  //
  // From: http://www.nathandumont.com/node/250
  //
  // Encoding:        +-- 5 ---+--- 4 ---+---- 3 ---+- 2:0 --+
  //           Bit==1 | Input  | Pull Up | Pull Dis |        |
  //                  +--------+---------+----------+  Mode  +  
  //           Bit==0 | Output | Pull Dn | Pull En  |        |
  //                  +--------+---------+----------+--------+  
  //
  int code = mode & 0x7;
  switch (pulls) {
  case NONE: code |= 0x08;
  case PU  : code |= 0x10;
  case PD  : code |= 0x00;
  }
  if (dir == IN) code |= 0x20;
  
  fprintf(fp, "%x\n", code);
  fclose(fp);

  return 1;
}

int
pin::lock(const char* whoami)
{
  if (m_key) {
    fprintf(stderr, "ERROR: Cannot lock pin %s: Already locked by %s\n", get_name(), m_locker);
    return 0;
  }
  if (whoami == NULL || *whoami == '\0') whoami = "(unknown)";
  m_locker = whoami;
  while (!m_key) m_key = random();
  return m_key;
}

int
pin::is_locked()
{
  return (m_key != 0);
}

void
pin::unlock(int key)
{
  if (key != m_key) {
    fprintf(stderr, "ERROR: Wrong credentials for unlocking pin %s.\n", m_name);
    return;
  }
  m_key = 0;
}



pin_fct::pin_fct(const char* name)
  : m_name(name), m_pin(NULL)
{
  for(int i = 0; i < 4; i++) m_pins[i] = NULL;
}

const char*
pin_fct::get_name()
{
  return m_name;
}

pin*
pin_fct::get_pin()
{
  return m_pin;
}

pin*
pin_fct::xport(pin::direction_t dir, pin::pull_t pulls)
{
  // Already exported?
  if (m_pin != NULL) return m_pin;

  // Export it on the first unlocked pin that can
  pin** p = m_pins;
  while (*p) {
    if (!(*p)->is_locked()) {
      (*p)->xport(this, dir, pulls);
      return *p;
    }
    p++;
  }

  fprintf(stderr, "ERROR: Cannot export %s functionality: all possible pins (", get_name());
  p = m_pins;
  while (*p) {
    if (p != m_pins) fprintf(stderr, ", ");
    fprintf(stderr, "%s", (*p)->get_name());
    p++;
  }
  fprintf(stderr, ") are locked.\n");

  return NULL;
}

}


#ifdef TEST

void
switch_pin(BeagleBone::pin* p, BeagleBone::pin_fct* f)
{
  printf("\nSwitching pin %s to %s function...\n", p->get_name(), f->get_name());
  p->xport(f);
  system("cat /sys/kernel/debug/omap_mux/ecap0_in_pwm0_out");
}


int
main(int argc, char *argv[])
{
  BeagleBone::pin *P9_42 = BeagleBone::pin::P9(42);
  printf("Pin %s is %s...\n", P9_42->get_name(), P9_42->get_fct()->get_name());
  system("cat /sys/kernel/debug/omap_mux/ecap0_in_pwm0_out");
  switch_pin(P9_42, BeagleBone::pin_fct::ecap0_in_pwm0_out);
  switch_pin(P9_42, BeagleBone::pin_fct::uart3_txd);
  switch_pin(P9_42, BeagleBone::pin_fct::spi1_cs1);
  switch_pin(P9_42, BeagleBone::pin_fct::spi1_sclk);
  switch_pin(P9_42, BeagleBone::pin_fct::mmc0_sdwp);
  switch_pin(P9_42, BeagleBone::pin_fct::xdma_event_intr2);
  switch_pin(P9_42, BeagleBone::pin_fct::gpio0_7);
  printf("\nSwitching pin %s to OUT GPIO...\n", P9_42->get_name());
  P9_42->xport(BeagleBone::pin_fct::gpio0_7, BeagleBone::pin::OUT);
  system("cat /sys/kernel/debug/omap_mux/ecap0_in_pwm0_out");
  printf("\nSwitching pin %s to OUT PU GPIO...\n", P9_42->get_name());
  P9_42->xport(BeagleBone::pin_fct::gpio0_7, BeagleBone::pin::OUT, BeagleBone::pin::PU);
  system("cat /sys/kernel/debug/omap_mux/ecap0_in_pwm0_out");
  printf("\nSwitching pin %s to OUT PD GPIO...\n", P9_42->get_name());
  P9_42->xport(BeagleBone::pin_fct::gpio0_7, BeagleBone::pin::OUT, BeagleBone::pin::PD);
  system("cat /sys/kernel/debug/omap_mux/ecap0_in_pwm0_out");
  printf("\nSwitching pin %s to IN PD GPIO...\n", P9_42->get_name());
  P9_42->xport(BeagleBone::pin_fct::gpio0_7, BeagleBone::pin::IN, BeagleBone::pin::PD);
  system("cat /sys/kernel/debug/omap_mux/ecap0_in_pwm0_out");
  printf("\nSwitching pin %s to IN PU GPIO...\n", P9_42->get_name());
  P9_42->xport(BeagleBone::pin_fct::gpio0_7, BeagleBone::pin::IN, BeagleBone::pin::PU);
  system("cat /sys/kernel/debug/omap_mux/ecap0_in_pwm0_out");
  printf("\nSwitching pin %s to IN GPIO...\n", P9_42->get_name());
  P9_42->xport(BeagleBone::pin_fct::gpio0_7, BeagleBone::pin::IN);
  system("cat /sys/kernel/debug/omap_mux/ecap0_in_pwm0_out");

  printf("\nNOTE: Expect no errors from muxed pin...\n");
  
  BeagleBone::pin *p1 = BeagleBone::pin::P9(20);
  BeagleBone::pin *p2 = BeagleBone::pin::P9(28);

  printf("NOTE: Expect *ONE* errors below...\n");
  p2->xport(BeagleBone::pin_fct::i2c2_sda, BeagleBone::pin::OUT);

  printf("NOTE: Expect *ONE* errors below -- but it should be possible to make it go away...\n");
  p1->xport(BeagleBone::pin_fct::spi1_cs0, BeagleBone::pin::OUT);

  printf("NOTE: No more errors from this point on...\n");
  p1->xport(BeagleBone::pin_fct::i2c2_sda, BeagleBone::pin::OUT);
  p2->xport(BeagleBone::pin_fct::gpio3_17, BeagleBone::pin::OUT);
  p1->xport(BeagleBone::pin_fct::spi1_cs0, BeagleBone::pin::OUT);

  printf("NOTE: Expect *ONE* error from locked pin...\n");
  int key;
  key = p1->lock("p1");
  p1->xport(BeagleBone::pin_fct::i2c2_sda, BeagleBone::pin::OUT);
  printf("NOTE: Expect *ONE* error from bad credentials...\n");
  p1->unlock(77);
  printf("NOTE: Expect *ONE* error from already-locked pin...\n");
  p1->lock("Again");
  printf("NOTE: Expect no more errors from locked pin...\n");
  p1->unlock(key);
  p1->xport(BeagleBone::pin_fct::i2c2_sda, BeagleBone::pin::OUT);
  p1->xport(BeagleBone::pin_fct::spi1_cs0, BeagleBone::pin::OUT);
  BeagleBone::pin_fct::i2c2_sda->xport(BeagleBone::pin::OUT);
  key = p1->lock("p1");
  printf("NOTE: Expect *ONE* error from locked pin...\n");
  BeagleBone::pin_fct::gpio0_12->xport(BeagleBone::pin::OUT);
  printf("NOTE: Expect no more errors from locked pin...\n");
  BeagleBone::pin_fct::spi1_cs0->xport(BeagleBone::pin::OUT);
  if (BeagleBone::pin_fct::spi1_cs0->get_pin() != p2) {
    fprintf(stderr, "ERROR: Functionality spi1_cso is on pin %s instead of %s.\n",
	    BeagleBone::pin_fct::spi1_cs0->get_pin()->get_name(), p2->get_name());
  }

  printf("NOTE: Expect *ONE* error from unmuxed pin...\n");
  BeagleBone::pin::P8(1)->lock("GND");

  printf("Done!\n");

  return 0;
}

#endif
