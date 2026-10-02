# Cognifyz Software Development Internship

Software Development internship task repository containing all six assigned tasks, organized by level.

## Project Structure

### Level 1 — Beginner
- **Task 1: Text-Based Game** — Number guessing game using conditional statements.
- **Task 2: Number Pattern** — Number pyramid generator using loops.

### Level 2 — Intermediate
- **Task 3: CRUD Task Manager** — Console-based Create, Read, Update, and Delete operations using a Python list.
- **Task 4: Temperature Converter** — Celsius ↔ Fahrenheit conversion.

### Level 3 — Advanced
- **Task 5: Persistent CRUD** — Task manager with file persistence and file-operation error handling.
- **Task 6: Interactive Web Scraper** — Fetches and displays a public webpage's title, headings, and links.

## Technologies

- Python 3
- Python standard library
- Requests
- Beautiful Soup 4
- JSON/file I/O

## How to Run

Each task is independent. Open a terminal in the task folder and run:

```bash
python main.py
```

For Task 6, install its dependencies first:

```bash
pip install -r requirements.txt
python main.py
```

## Repository Layout

```text
Cognifyz-Software-Development-Internship/
├── Level-1/
│   ├── Task-1-Text-Based-Game/
│   └── Task-2-Number-Pattern/
├── Level-2/
│   ├── Task-3-CRUD-Task-Manager/
│   └── Task-4-Temperature-Converter/
├── Level-3/
│   ├── Task-5-Persistent-CRUD/
│   └── Task-6-Web-Scraper/
├── .gitignore
└── README.md
```

## Notes

- Task 5 creates `tasks.txt` when task data is saved.
- Task 6 should only be used on websites where automated access is permitted.
- Each task folder contains its own README with task-specific instructions.

## Internship

**Domain:** Software Development  
**Organization:** Cognifyz Technologies
