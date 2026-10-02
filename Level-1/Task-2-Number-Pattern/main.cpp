#include <iostream>

int main() {
    std::cout << "=== Number Pattern Generator ===\n";
    std::cout << "Enter number of rows (1-20): ";

    int rows;
    if (!(std::cin >> rows) || rows < 1 || rows > 20) {
        std::cout << "Rows must be between 1 and 20.\n";
        return 0;
    }

    for (int i = 1; i <= rows; ++i) {
        for (int space = 0; space < rows - i; ++space) {
            std::cout << " ";
        }
        for (int number = 1; number <= i; ++number) {
            std::cout << number;
            if (number < i) std::cout << " ";
        }
        std::cout << "\n";
    }
    return 0;
}
