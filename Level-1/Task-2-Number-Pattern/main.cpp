#include<bits/stdc++.h>
using namespace std;

int main() {
    cout << "=== Number Pattern Generator ===\n";
    cout << "Enter number of rows (1-20): ";

    int rows;
    if (!(cin >> rows) || rows < 1 || rows > 20) {
        cout << "Rows must be between 1 and 20.\n";
        return 0;
    }

    for (int i = 1; i <= rows; ++i) {
        for (int space = 0; space < rows - i; ++space) {
            cout << " ";
        }

        for (int number = 1; number <= i; ++number) {
            cout << number;
            if (number < i) cout << " ";
        }

        cout << "\n";
    }

    return 0;
}
