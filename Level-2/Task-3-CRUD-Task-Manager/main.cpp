#include <iostream>
#include <vector>
#include <string>
#include <limits>

class Task {
public:
    std::string title;
    bool completed;

    Task(const std::string& taskTitle, bool isCompleted = false)
        : title(taskTitle), completed(isCompleted) {}
};

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
    std::vector<Task> tasks;

    while (true) {
        std::cout << "\n=== CRUD Task Manager ===\n";
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
                std::cout << "Created.\n";
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

            std::cout << "Updated.\n";
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

            std::cout << "Deleted: " << tasks[number - 1].title << "\n";
            tasks.erase(tasks.begin() + static_cast<long long>(number - 1));
        } else if (choice == 0) {
            break;
        } else {
            std::cout << "Invalid option.\n";
        }
    }

    return 0;
}
