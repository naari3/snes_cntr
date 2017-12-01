#include <pigpio.h>
#include <iostream>

using namespace std;


static const int GPIO_VCC = 26; // GREEN
static const int GPIO_DAT = 19; // RED
static const int GPIO_P_S = 13; // WHITE
static const int GPIO_CLK = 6; // YELLOW

void init() {
}

int main() {
  if (gpioInitialise() < 0) return 1;
  gpioSetMode(GPIO_VCC, PI_INPUT);
  gpioSetMode(GPIO_DAT, PI_INPUT);
  gpioSetMode(GPIO_CLK, PI_INPUT);
  gpioSetMode(GPIO_P_S, PI_INPUT);

  cout << "POWER " << gpioRead(GPIO_VCC) << endl;
  cout << "DAT   " << gpioRead(GPIO_DAT) << endl;
  cout << "CLK   " << gpioRead(GPIO_CLK) << endl;
  cout << "P/S   " << gpioRead(GPIO_P_S) << endl;

  gpioTerminate();
  return 0;
}
