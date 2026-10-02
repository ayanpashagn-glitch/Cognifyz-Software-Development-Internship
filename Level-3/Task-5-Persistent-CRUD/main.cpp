#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>

class Task {
public:
    std::string title;
    bool completed;

    Task(const std::string& taskTitle, bool isCompleted = false)
        : title(taskTitle), completed(isCompleted) {}
};

const std::string FILE_NAME = "tasks.txt";

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::vector<Task> loadTasks() {
    std::vector<Task> tasks;
    std::ifstream file(FILE_NAME);
    if (!file.is_open()) return tasks;

    std::string line;
    while (std::getline(file, line)) {
        std::size_t separator = line.find('|');
        if (separator == std::string::npos) continue;
        bool completed = line.substr(0, separator) == "1";
        std::string title = line.substr(separator + 1);
        tasks.emplace_back(title, completed);
    }

    if (file.bad()) {
        std::cout << "Warning: An error occurred while reading the task file.\n";
    }
    return tasks;
}

bool saveTasks(const std::vector<Task>& tasks) {
    std::ofstream file(FILE_NAME);
    if (!file.is_open()) {
        std::cout << "Could not save task data.\n";
        return false;
    }

    for (const Task& task : tasks) {
        file << (task.completed ? 1 : 0) << "|" << task.title << "\n";
    }

    if (!file) {
        std::cout << "An error occurred while writing task data.\n";
        return false;
    }
    return true;
}

void displayTasks(const std::vector<Task>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks.\n";
        return;
    }

    for (std::size_t i = 0; i < tasks.size(); ++i) {
        std::cout << (i + 1) << ". ["
                  << (tasks[i].completed ? "Done" : "Pending")
                  << "] " << tasks[i].title << "\n";
    }
}

int main() {
    std::vector<Task> tasks = loadTasks();

    while (true) {
        std::cout << "\n=== Persistent CRUD Task Manager ===\n";
        std::cout << "1. Create\n2. Read\n3. Update\n4. Delete\n0. Exit\n";
        std::cout << "Choose: ";

        int choice;
        if (!(std::cin >> choice)) {
            clearInput();
            std::cout << "Invalid option.\n";
            continue;
        }
        clearInput();

        if (choice == 1) {
            std::string title;
            std::cout << "Title: ";
            std::getline(std::cin, title);
            if (!title.empty()) {
                tasks.emplace_back(title);
                if (saveTasks(tasks)) std::cout << "Created and saved.\n";
            }
        } else if (choice == 2) {
            displayTasks(tasks);
        } else if (choice == 3) {
            displayTasks(tasks);
            if (tasks.empty()) continue;

            std::cout << "Task number: ";
            std::size_t number;
            if (!(std::cin >> number)) {
                clearInput();
                std::cout << "Invalid task.\n";
                continue;
            }
            clearInput();

            if (number < 1 || number > tasks.size()) {
                std::cout << "Invalid task.\n";
                continue;
            }

            Task& task = tasks[number - 1];
            std::string newTitle;
            std::cout << "New title (Enter to keep): ";
            std::getline(std::cin, newTitle);
            if (!newTitle.empty()) task.title = newTitle;

            char done;
            std::cout << "Completed? (y/n): ";
            std::cin >> done;
            clearInput();

            if (done == 'y' || done == 'Y') task.completed = true;
            else if (done == 'n' || done == 'N') task.completed = false;

            if (saveTasks(tasks)) std::cout << "Updated and saved.\n";
        } else if (choice == 4) {
            displayTasks(tasks);
            if (tasks.empty()) continue;

            std::cout << "Task number: ";
            std::size_t number;
            if (!(std::cin >> number)) {
                clearInput();
                std::cout << "Invalid task.\n";
                continue;
            }
            clearInput();

            if (number < 1 || number > tasks.size()) {
                std::cout << "Invalid task.\n";
                continue;
            }

            std::string removedTitle = tasks[number - 1].title;
            tasks.erase(tasks.begin() + static_cast<long long>(number - 1));
            if (saveTasks(tasks)) std::cout << "Deleted: " << removedTitle << "\n";
        } else if (choice == 0) {
            break;
        } else {
            std::cout << "Invalid option.\n";
        }
    }

    return 0;
}
