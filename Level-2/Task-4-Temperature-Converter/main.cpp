#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    cout << "=== Temperature Converter ===\n";
    cout << "1. Celsius to Fahrenheit\n";
    cout << "2. Fahrenheit to Celsius\n";
    cout << "Choose: ";

    int choice;
    cin >> choice;

    double temperature;
    cout << "Temperature: ";
    if (!(cin >> temperature)) {
        cout << "Invalid temperature.\n";
        return 0;
    }

    cout << fixed << setprecision(2);

    if (choice == 1) {
        double fahrenheit = temperature * 9.0 / 5.0 + 32.0;
        cout << temperature << " C = " << fahrenheit << " F\n";
    } else if (choice == 2) {
        double celsius = (temperature - 32.0) * 5.0 / 9.0;
        cout << temperature << " F = " << celsius << " C\n";
    } else {
        cout << "Invalid option.\n";
    }

    return 0;
}
