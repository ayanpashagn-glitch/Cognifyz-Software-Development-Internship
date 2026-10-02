#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
using namespace std;

class Task {
public:
    string title;
    bool completed;

    Task(const string& taskTitle, bool isCompleted = false)
        : title(taskTitle), completed(isCompleted) {}
};

const string FILE_NAME = "tasks.txt";

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

vector<Task> loadTasks() {
    vector<Task> tasks;
    ifstream file(FILE_NAME);

    if (!file.is_open()) {
        return tasks;
    }

    string line;
    while (getline(file, line)) {
        size_t separator = line.find('|');
        if (separator == string::npos) continue;

        string completedText = line.substr(0, separator);
        string title = line.substr(separator + 1);

        bool completed = (completedText == "1");
        tasks.emplace_back(title, completed);
    }

    if (file.bad()) {
        cout << "Warning: An error occurred while reading the task file.\n";
    }

    return tasks;
}

bool saveTasks(const vector<Task>& tasks) {
    ofstream file(FILE_NAME);

    if (!file.is_open()) {
        cout << "Could not save task data.\n";
        return false;
    }

    for (const Task& task : tasks) {
        file << (task.completed ? 1 : 0) << "|" << task.title << "\n";
    }

    if (!file) {
        cout << "An error occurred while writing task data.\n";
        return false;
    }

    return true;
}

void displayTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks.\n";
        return;
    }

    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << (i + 1) << ". ["
              << (tasks[i].completed ? "Done" : "Pending")
              << "] " << tasks[i].title << "\n";
    }
}

int main() {
    vector<Task> tasks = loadTasks();

    while (true) {
        cout << "\n=== Persistent CRUD Task Manager ===\n";
        cout << "1. Create\n2. Read\n3. Update\n4. Delete\n0. Exit\n";
        cout << "Choose: ";

        int choice;
        if (!(cin >> choice)) {
            clearInput();
            cout << "Invalid option.\n";
            continue;
        }
        clearInput();

        if (choice == 1) {
            string title;
            cout << "Title: ";
            getline(cin, title);

            if (!title.empty()) {
                tasks.emplace_back(title);
                if (saveTasks(tasks)) cout << "Created and saved.\n";
            }
        } else if (choice == 2) {
            displayTasks(tasks);
        } else if (choice == 3) {
            displayTasks(tasks);
            if (tasks.empty()) continue;

            cout << "Task number: ";
            size_t number;
            if (!(cin >> number)) {
                clearInput();
                cout << "Invalid task.\n";
                continue;
            }
            clearInput();

            if (number < 1 || number > tasks.size()) {
                cout << "Invalid task.\n";
                continue;
            }

            Task& task = tasks[number - 1];

            string newTitle;
            cout << "New title (Enter to keep): ";
            getline(cin, newTitle);
            if (!newTitle.empty()) task.title = newTitle;

            char done;
            cout << "Completed? (y/n): ";
            cin >> done;
            clearInput();

            if (done == 'y' || done == 'Y') task.completed = true;
            else if (done == 'n' || done == 'N') task.completed = false;

            if (saveTasks(tasks)) cout << "Updated and saved.\n";
        } else if (choice == 4) {
            displayTasks(tasks);
            if (tasks.empty()) continue;

            cout << "Task number: ";
            size_t number;
            if (!(cin >> number)) {
                clearInput();
                cout << "Invalid task.\n";
                continue;
            }
            clearInput();

            if (number < 1 || number > tasks.size()) {
                cout << "Invalid task.\n";
                continue;
            }

            string removedTitle = tasks[number - 1].title;
            tasks.erase(tasks.begin() + static_cast<long long>(number - 1));

            if (saveTasks(tasks)) {
                cout << "Deleted: " << removedTitle << "\n";
            }
        } else if (choice == 0) {
            break;
        } else {
            cout << "Invalid option.\n";
        }
    }

    return 0;
}
