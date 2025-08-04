#include <assert.h>
#include <iostream>
using namespace std;

enum CheckType {
  TEMPERATURE,
  SOC,
  CHARGE_RATE
};

bool checkParameter(CheckType check, float value) {
  switch (check) {
    case TEMPERATURE:
      if (value < 0 || value > 45) {
        cout << "Temperature out of range!\n";
        return false;
      }
      break;
    case SOC:
      if (value < 20 || value > 80) {
        cout << "State of Charge out of range!\n";
        return false;
      }
      break;
    case CHARGE_RATE:
      if (value > 0.8) {
        cout << "Charge Rate out of range!\n";
        return false;
      }
      break;
    default:
      // Unknown check type
      return false;
  }
  return true;
}

bool batteryIsOk(float temperature, float soc, float chargeRate) {
  if (!checkParameter(TEMPERATURE, temperature)) return false;
  if (!checkParameter(SOC, soc)) return false;
  if (!checkParameter(CHARGE_RATE, chargeRate)) return false;
  return true;
}

int main() {
  assert(batteryIsOk(25, 70, 0.7) == true);
  assert(batteryIsOk(50, 85, 0) == false);
}
