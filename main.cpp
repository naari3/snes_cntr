#include <pigpio.h>
#include <iostream>

using namespace std;


static const int GPIO_VCC = 4; // GREEN
static const int GPIO_DAT = 22; // RED
static const int GPIO_CLK = 17; // YELLOW
static const int GPIO_P_S = 27; // WHITE

void init() {
  gpioSetMode(GPIO_VCC, PI_INPUT);
}

int main() {
  if (gpioInitialise() < 0) return 1;
  init();

  cout << "POWER " << gpioRead(GPIO_VCC) << endl;
  return 0;
}
