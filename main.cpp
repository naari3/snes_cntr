#include <pigpio.h>
#include <iostream>

using namespace std;


static const int GPIO_VCC = 18; // GREEN
static const int GPIO_DAT = 22; // RED
static const int GPIO_CLK = 17; // YELLOW
static const int GPIO_P_S = 27; // WHITE

void init() {
}

int main() {
  if (gpioInitialise() < 0) return 1;
  gpioSetMode(GPIO_VCC, PI_INPUT);
  gpioSetMode(GPIO_DAT, PI_INPUT);
  gpioSetMode(GPIO_P_S, PI_INPUT);

  cout << "POWER " << gpioRead(GPIO_VCC) << endl;
  cout << "DAT   " << gpioRead(GPIO_DAT) << endl;
  cout << "P/S   " << gpioRead(GPIO_P_S) << endl;
  return 0;
}
