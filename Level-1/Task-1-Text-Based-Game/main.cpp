#include <iostream>
#include <random>
#include <limits>
#include <chrono>
using namespace std;

int main() {
    cout << "=== Number Guessing Game ===\n";
    cout << "Guess a number between 1 and 100. You have 7 valid attempts.\n";

    unsigned seed = chrono::high_resolution_clock::now()
                    .time_since_epoch()
                    .count();

    mt19937 gen(seed);
    uniform_int_distribution<int> dist(1, 100);
    int secret = dist(gen);

    int attempts = 0;

    while (attempts < 7) {
        int guess;
        cout << "Attempt " << (attempts + 1) << "/7: ";

        if (!(cin >> guess)) {
            cout << "Enter a valid whole number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (guess < 1 || guess > 100) {
            cout << "Enter a number from 1 to 100.\n";
            continue;
        }

        attempts++;

        if (guess == secret) {
            cout << "Correct! You won in " << attempts << " attempt(s).\n";
            return 0;
        } else if (guess < secret) {
            cout << "Too low.\n";
        } else {
            cout << "Too high.\n";
        }
    }

    cout << "Game over. The number was " << secret << ".\n";
    return 0;
}
