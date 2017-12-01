#include <pigpio.h>
#include <iostream>
#include <stdio.h>

using namespace std;


static const int GPIO_VCC = 26; // GREEN
static const int GPIO_DAT = 19; // RED
static const int GPIO_LAT = 13; // WHITE
static const int GPIO_CLK = 20; // YELLOW

extern int clock_count = 0;

void clocking(int gpio, int level, uint32_t tick) {
  if (level == 1) {
    clock_count++;
    printf("clocked at %d\n", clock_count);
  }
}

void latching(int gpio, int level, uint32_t tick) {
  if (level == 1) {
    clock_count = 0;
    printf("latched at %d\n", clock_count);
  }
}

int main() {
  if (gpioInitialise() < 0) return 1;
  gpioSetMode(GPIO_VCC, PI_INPUT);
  gpioSetMode(GPIO_DAT, PI_INPUT);
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
