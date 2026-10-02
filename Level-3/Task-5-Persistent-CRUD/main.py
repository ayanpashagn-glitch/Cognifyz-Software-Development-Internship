import json
from pathlib import Path

FILE = Path(__file__).with_name("tasks.txt")

def load_tasks():
    if not FILE.exists():
        return []
    try:
        return json.loads(FILE.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError):
        print("Could not read task data.")
        return []

def save_tasks(tasks):
    try:
        FILE.write_text(json.dumps(tasks, indent=2), encoding="utf-8")
        return True
    except OSError:
        print("Could not save task data.")
        return False

def display(tasks):
    if not tasks:
        print("No tasks.")
    for i, task in enumerate(tasks, 1):
        status = "Done" if task["completed"] else "Pending"
        print(f"{i}. [{status}] {task['title']}")

def main():
    tasks = load_tasks()
    while True:
        print("\n=== Persistent CRUD Task Manager ===")
        print("1.Create  2.Read  3.Update  4.Delete  0.Exit")
        choice = input("Choose: ").strip()

        if choice == "1":
            title = input("Title: ").strip()
            if title:
                tasks.append({"title": title, "completed": False})
                if save_tasks(tasks):
                    print("Created and saved.")
        elif choice == "2":
            display(tasks)
        elif choice == "3":
            display(tasks)
            try:
                idx = int(input("Task number: ")) - 1
                if idx < 0 or idx >= len(tasks):
                    raise IndexError
                title = input("New title (Enter to keep): ").strip()
                if title:
                    tasks[idx]["title"] = title
                done = input("Completed? y/n: ").lower()
                if done in ("y", "n"):
                    tasks[idx]["completed"] = done == "y"
                if save_tasks(tasks):
                    print("Updated and saved.")
            except (ValueError, IndexError):
                print("Invalid task.")
        elif choice == "4":
            display(tasks)
            try:
                idx = int(input("Task number: ")) - 1
                if idx < 0 or idx >= len(tasks):
                    raise IndexError
                removed = tasks.pop(idx)
                if save_tasks(tasks):
                    print("Deleted:", removed["title"])
            except (ValueError, IndexError):
                print("Invalid task.")
        elif choice == "0":
            break
        else:
            print("Invalid option.")

if __name__ == "__main__":
    main()
