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

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "gpio.hpp"

namespace BeagleBone {

//
// Where are the GPIO control devices?
//
static const char* const devdir       = "/sys/class/gpio";
static const char* const export_dev   = "/sys/class/gpio/export";
static const char* const unexport_dev = "/sys/class/gpio/unexport";


gpio::gpio(const char*    name,
	   const char*    pin_dev,
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
	   direction_t    dir,
	   pull_t         pulls)
  : pin(name, pin_dev, mode0, mode1, mode2, mode3, mode4, mode5, mode6, mode7, init, dir, pulls),
    m_number(port_no * 32 + pin_no)
{
  m_dev = (char*) malloc(strlen(devdir)+64);
  sprintf(m_dev, "%s/gpio%d", devdir, m_number);
  m_dev_append = m_dev + strlen(m_dev);
}


gpio*
gpio::P8(unsigned char n)
{
  pin* p = pin::P8(n);
  gpio* gp;

  if (p == NULL) return NULL;

  gp = dynamic_cast<gpio*>(p);
  if (gp == NULL) {
    fprintf(stderr, "ERROR: Pin P8(%d) is not a GPIO pin.\n", n);
    return NULL;
  }
  
  if (!gp->pin_xport()) return NULL;

  return gp;
}


gpio*
gpio::P9(unsigned char n)
{
  pin* p = pin::P9(n);
  gpio* gp;

  if (p == NULL) return NULL;

  gp = dynamic_cast<gpio*>(p);
  if (gp == NULL) {
    fprintf(stderr, "ERROR: Pin P9(%d) is not a GPIO pin.\n", n);
    return NULL;
  }
  
  if (!gp->pin_xport()) return NULL;

  return gp;
}


int
gpio::pin_xport()
{
  // Already on GPIO function?
  if (get_fct() != get_gpio()) {
    // Mux pin to GPIO
    if (!xport(get_gpio())) return 0;
  }

  // Has the GPIO pin already been exported?
  *m_dev_append = '\0';
  DIR *dirp = opendir(m_dev);
  if (dirp != NULL) {
    closedir(dirp);
    return 1;
  }

  FILE *fp = fopen(export_dev, "w");
  if (fp == NULL) {
    fprintf(stderr, "ERROR: Cannot export GPIO %s on pin %s: ", get_fct()->get_name(), get_name());
    perror(0);
    return 0;
  }

  fprintf(fp, "%d", m_number);

  fclose(fp);

  return 1;
}


int
gpio::configure(pin::direction_t dir, pin::pull_t pulls)
{
  // Mux the pin in the right direction (redundent?)
  pin::xport(get_gpio(), dir, pulls);

  // Next, configure the GPIO driver accordingly
  strcpy(m_dev_append, "/direction");
  FILE* fp = fopen(m_dev, "w");
  if (fp == NULL) {
    fprintf(stderr, "ERROR: Cannot configure GPIO %s on pin %s: ", get_fct()->get_name(), get_name());
    perror(0);
    return 0;
  }

  if (dir == pin::IN) fprintf(fp, "in");
  else fprintf(fp, "out");
  
  fclose(fp);
  return 1;
}


pin::direction_t
gpio::get_direction()
{
  fprintf(stderr, "ERROR: gpio::get_direction() not yet implemented.\n");
  return IN;
}


pin::pull_t
gpio::get_pulls()
{
  fprintf(stderr, "ERROR: gpio::get_pulls() not yet implemented.\n");
  return NONE;
}


int
gpio::set(unsigned char val)
{
  strcpy(m_dev_append, "/value");
  FILE* fp = fopen(m_dev, "w");
  if (fp == NULL) {
    fprintf(stderr, "ERROR: Cannot set GPIO %s on pin %s: ", get_fct()->get_name(), get_name());
    perror(0);
    return 0;
  }

  fprintf(fp, "%d", val % 2);
  
  fclose(fp);
  return 1;
}


unsigned char
gpio::get()
{
  strcpy(m_dev_append, "/value");
  FILE* fp = fopen(m_dev, "r");
  if (fp == NULL) {
    fprintf(stderr, "ERROR: Cannot get GPIO %s on pin %s: ", get_fct()->get_name(), get_name());
    perror(0);
    return 0;
  }

  char c = fgetc(fp);
  fclose(fp);

  return c == '1';
}

}

#ifdef TEST

int
main(int argc, char *argv[])
{
  BeagleBone::gpio* gpio;
  BeagleBone::pin*  pin;

  printf("Checking basic get of GPIO pin...\n");
  gpio = BeagleBone::gpio::P8(15);
  printf("Got GPIO %s.\n", gpio->get_name());
  if (gpio->get_fct() != gpio->get_gpio()) {
    printf("ERROR: GPIO %s did not mux to GPIO function.\n", gpio->get_name());
  }
  printf("NOTE: Expect *ONE* error...\n");
  gpio = BeagleBone::gpio::P8(1);

  pin = gpio;
  pin = BeagleBone::pin::P8(15);
  
  printf("\nChecking switching to GPIO function...\n");
  pin->xport(BeagleBone::pin_fct::gpmc_ad15);
  gpio = BeagleBone::gpio::P8(15);
  printf("NOTE: Expect *ONE* error...\n");
  pin->xport(BeagleBone::pin_fct::gpmc_ad15);
  int key = pin->lock("GPIO");
  gpio = BeagleBone::gpio::P8(15);
  printf("NOTE: Expect NO error...\n");
  pin->unlock(key);
  gpio = BeagleBone::gpio::P8(15);

  printf("\nChecking Basic GPIO I/O operations...\n");
  printf("\n*** WARNING: For this portion of the test to pass,\n");
  printf("*** WARNING: P8/42 must be connected to P9/41\n");
  printf("*** WARNING: (3rd outside pins from the bottom)\n\n");
  BeagleBone::gpio* outp = BeagleBone::gpio::P8(42);
  BeagleBone::gpio* inp = BeagleBone::gpio::P9(41);
  unsigned char v;
  if (!outp->configure(BeagleBone::pin::OUT, BeagleBone::pin::NONE)) {
    printf("ERROR: Could not configure GPIO OUT pin...\n");
  }
  if (!inp->configure(BeagleBone::pin::IN, BeagleBone::pin::NONE)) {
    printf("ERROR: Could not configure GPIO IN pin...\n");
  }
  printf("...Setting to 0...\n");
  if (!outp->set(0)) {
    printf("ERROR: Could not drive pin to 0...\n");
  }
  v = inp->get();
  printf("NOTE: GPIO input = %d\n", v);
  if (v != 0) {
    printf("ERROR: GPIO input value was %d instead of 0.\n", v);
  }
  printf("...Setting to 1...\n");
  if (!outp->set(1)) {
    printf("ERROR: Could not drive pin to 1...\n");
  }
  v = inp->get();
  printf("NOTE: GPIO input = %d\n", v);
  if (v != 1) {
    printf("ERROR: GPIO input value was %d instead of 1.\n", v);
  }
  printf("...Setting to 0...\n");
  if (!outp->set(0)) {
    printf("ERROR: Could not drive pin to 0...\n");
  }
  v = inp->get();
  printf("NOTE: GPIO input = %d\n", v);
  if (v != 0) {
    printf("ERROR: GPIO input value was %d instead of 0.\n", v);
  }
  printf("...Setting to 1...\n");
  if (!outp->set(1)) {
    printf("ERROR: Could not drive pin to 1...\n");
  }
  v = inp->get();
  printf("NOTE: GPIO input = %d\n", v);
  if (v != 1) {
    printf("ERROR: GPIO input value was %d instead of 1.\n", v);
  }

  printf("\nChecking GPIO pull-up settings...\n");
  printf("\n*** WARNING: For this portion of the test to pass,\n");
  printf("*** WARNING: P8(3) must NOT be connected\n");
  inp = BeagleBone::gpio::P8(3);
  if (!inp->configure(BeagleBone::pin::IN, BeagleBone::pin::PD)) {
    printf("ERROR: Could not configure GPIO IN pin to pull-up...\n");
  }
  v = inp->get();
  printf("NOTE: GPIO input = %d\n", v);
  if (v != 0) {
    printf("ERROR: GPIO input value was %d instead of 0.\n", v);
  }
  if (!inp->configure(BeagleBone::pin::IN, BeagleBone::pin::PU)) {
    printf("ERROR: Could not configure GPIO IN pin to pull-up...\n");
  }
  v = inp->get();
  printf("NOTE: GPIO input = %d\n", v);
  if (v != 1) {
    printf("ERROR: GPIO input value was %d instead of 1.\n", v);
  }

  printf("Done!\n");

  return 0;
}

#endif


