#include <pigpio.h>
#include <iostream>
#include <stdio.h>

using namespace std;


static const int GPIO_VCC = 26; // GREEN
static const int GPIO_DAT = 19; // RED
static const int GPIO_LAT = 13; // WHITE
static const int GPIO_CLK = 20; // YELLOW

extern int clock_count = 0;
extern int latch_count = 0;

extern int current_input = 0;
extern int next_input = 1;

extern int dat_path = 1<<GPIO_DAT;


void controll();

void clocking(int gpio, int level, uint32_t tick) {
  if (level == 1) {
    clock_count++;
    if ((current_input & 1) || clock_count > 15) {
      gpioWrite_Bits_0_31_Clear(dat_path);
    } else {
      gpioWrite_Bits_0_31_Set(dat_path);
    }
    current_input >>= 1;
  }
}

void latching(int gpio, int level, uint32_t tick) {
  if (level == 1) {
    current_input = next_input;
    clock_count = 0;
    if ((current_input & 1) || clock_count > 15) {
      gpioWrite_Bits_0_31_Clear(dat_path);
    } else {
      gpioWrite_Bits_0_31_Set(dat_path);
    }
    current_input >>= 1;
  }
}

void controll() {
  if ((current_input & 1) || clock_count > 15) {
    gpioWrite_Bits_0_31_Clear(1<<GPIO_DAT);
  } else {
    gpioWrite_Bits_0_31_Set(1<<GPIO_DAT);
  }
}

void setup() {

}

void loop() {
  printf("%d\n", latch_count);
  time_sleep(1);
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
    loop();
  }

  gpioTerminate();
  return 0;
}
