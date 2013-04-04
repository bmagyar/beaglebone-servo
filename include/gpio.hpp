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

#ifndef __BONELIB_GPIO__
#define __BONELIB_GPIO__

#include "pinmux.hpp"

namespace BeagleBone {

/** Class representing a GPIO pin */
class gpio: public pin
{
  friend class pin;

public:
  /** Get the GPIO pin corresponding to a connector pin.
   *  Returns NULL if it does not support GPIO or it cannot be muxed to its GPIO function.
   */
  static gpio* P8(unsigned char n);
  static gpio* P9(unsigned char n);

  /** Configure the direction (and pull resistors) of the GPIO pin */
  int configure(pin::direction_t dir, pin::pull_t pulls = pin::NONE);

  /** Get the current direction of the GPIO pin */
  pin::direction_t get_direction();

  /** Get the pull resistors of the GPIO pin */
  pin::pull_t get_pulls();

  /** Set the value of the GPIO pin. Return TRUE if successful. */
  int set(unsigned char val);

  /** Get the value of the GPIO pin */
  unsigned char get();

private:
  unsigned char m_number;
  char*         m_dev;
  char*         m_dev_append;

  gpio(const char* name,
       const char* pin_dev,
       unsigned char  port_no,
       unsigned char  pin_no,
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

  /** Export the GPIO function of the pin. Returns TRUE on success. */
  int pin_xport();
};

}

#endif
