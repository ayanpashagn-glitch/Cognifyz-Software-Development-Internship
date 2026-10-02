#include <iostream>
#include <iomanip>

int main() {
    std::cout << "=== Temperature Converter ===\n";
    std::cout << "1. Celsius to Fahrenheit\n";
    std::cout << "2. Fahrenheit to Celsius\n";
    std::cout << "Choose: ";

    int choice;
    std::cin >> choice;

    double temperature;
    std::cout << "Temperature: ";
    if (!(std::cin >> temperature)) {
        std::cout << "Invalid temperature.\n";
        return 0;
    }

    std::cout << std::fixed << std::setprecision(2);

    if (choice == 1) {
        double fahrenheit = temperature * 9.0 / 5.0 + 32.0;
        std::cout << temperature << " C = " << fahrenheit << " F\n";
    } else if (choice == 2) {
        double celsius = (temperature - 32.0) * 5.0 / 9.0;
        std::cout << temperature << " F = " << celsius << " C\n";
    } else {
        std::cout << "Invalid option.\n";
    }
    return 0;
}
