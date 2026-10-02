#include <iostream>
#include <random>
#include <limits>

int main() {
    std::cout << "=== Number Guessing Game ===\n";
    std::cout << "Guess a number between 1 and 100. You have 7 valid attempts.\n";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);
    int secret = dist(gen);

    int attempts = 0;

    while (attempts < 7) {
        int guess;
        std::cout << "Attempt " << (attempts + 1) << "/7: ";

        if (!(std::cin >> guess)) {
            std::cout << "Enter a valid whole number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (guess < 1 || guess > 100) {
            std::cout << "Enter a number from 1 to 100.\n";
            continue;
        }

        attempts++;

        if (guess == secret) {
            std::cout << "Correct! You won in " << attempts << " attempt(s).\n";
            return 0;
        } else if (guess < secret) {
            std::cout << "Too low.\n";
        } else {
            std::cout << "Too high.\n";
        }
    }

    std::cout << "Game over. The number was " << secret << ".\n";
    return 0;
}
