def display(tasks):
    if not tasks:
        print("No tasks.")
        return
    for i, task in enumerate(tasks, 1):
        status = "Done" if task["completed"] else "Pending"
        print(f"{i}. [{status}] {task['title']}")

def main():
    tasks = []
    while True:
        print("\n=== CRUD Task Manager ===")
        print("1.Create  2.Read  3.Update  4.Delete  0.Exit")
        choice = input("Choose: ").strip()

        if choice == "1":
            title = input("Title: ").strip()
            if title:
                tasks.append({"title": title, "completed": False})
                print("Created.")
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
                print("Updated.")
            except (ValueError, IndexError):
                print("Invalid task.")
        elif choice == "4":
            display(tasks)
            try:
                idx = int(input("Task number: ")) - 1
                if idx < 0 or idx >= len(tasks):
                    raise IndexError
                print("Deleted:", tasks.pop(idx)["title"])
            except (ValueError, IndexError):
                print("Invalid task.")
        elif choice == "0":
            break
        else:
            print("Invalid option.")

if __name__ == "__main__":
    main()
