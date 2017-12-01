#include <pigpio.h>
#include <iostream>
#include <stdio.h>

using namespace std;


static const int GPIO_VCC = 26; // GREEN
static const int GPIO_DAT = 19; // RED
static const int GPIO_LAT = 13; // WHITE
static const int GPIO_CLK = 20; // YELLOW

extern int clock_count = 0;
extern uint32_t dat_button = 1 << GPIO_DAT;

void controll();

void clocking(int gpio, int level, uint32_t tick) {
  if (level == 1) {
    clock_count++;
  }
  controll();
}

void latching(int gpio, int level, uint32_t tick) {
  if (level == 1) {
    clock_count = 0;
  }
  controll();
}

void controll() {
  if (clock_count < 13) {
    gpioWrite(GPIO_DAT, 0);
    // gpioWrite_Bits_0_31_Clear(0);
  } else {
    gpioWrite(GPIO_DAT, 1);
    // gpioWrite_Bits_0_31_Set(dat_button);
  }
}

int main() {
  gpioCfgClock(1, 1, 1);
  if (gpioInitialise() < 0) return 1;
  gpioSetMode(GPIO_VCC, PI_INPUT);
  gpioSetMode(GPIO_DAT, PI_OUTPUT);
  gpioSetMode(GPIO_CLK, PI_INPUT);
  gpioSetMode(GPIO_LAT, PI_INPUT);

  gpioSetPullUpDown(GPIO_CLK, PI_PUD_UP);
  gpioSetPullUpDown(GPIO_LAT, PI_PUD_UP);

  gpioSetAlertFunc(GPIO_CLK, clocking);
  gpioSetAlertFunc(GPIO_LAT, latching);


  while (1) {
  }

  gpioTerminate();
  return 0;
}
