#include <iostream>
#include <map>
#include <functional>
using namespace std;

enum CheckType { TEMPERATURE, SOC, CHARGE_RATE };

bool checkRange(float value, float min, float max, const string& errorMsg) {
    if (value < min || value > max) {
        cout << errorMsg << "\n";
        return false;
    }
    return true;
}

bool checkParameter(CheckType check, float value) {
    static const map<CheckType, function<bool(float)>> checkers = {
        {TEMPERATURE, [](float v) { return checkRange(v, 0, 45, "Temperature out of range!"); }},
        {SOC, [](float v) { return checkRange(v, 20, 80, "State of Charge out of range!"); }},
        {CHARGE_RATE, [](float v) { return checkRange(v, 0, 0.8, "Charge Rate out of range!"); }}
    };

    auto it = checkers.find(check);
    if (it != checkers.end()) {
        return it->second(value);
    }
    // Unknown check type
    return false;
}

bool batteryIsOk(float temperature, float soc, float chargeRate) {
    return checkParameter(TEMPERATURE, temperature) &&
           checkParameter(SOC, soc) &&
           checkParameter(CHARGE_RATE, chargeRate);
}

int main() {
    assert(batteryIsOk(25, 70, 0.7) == true);
    assert(batteryIsOk(50, 85, 0) == false);
}
