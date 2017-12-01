#include <pigpio.h>
#include <iostream>

using namespace std;


static const int GPIO_VCC = 7; // GREEN
static const int GPIO_DAT = 3; // RED
static const int GPIO_CLK = 0; // YELLOW
static const int GPIO_P_S = 2; // WHITE

void init() {
  gpioSetMode(GPIO_VCC, PI_INPUT);
}

int main() {
  init();

  cout << "POWER " << gpioRead(GPIO_VCC) << endl;
  return 0;
}
