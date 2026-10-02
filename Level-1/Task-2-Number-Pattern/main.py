def main():
    print("=== Number Pattern Generator ===")
    try:
        rows = int(input("Enter number of rows (1-20): "))
    except ValueError:
        print("Invalid input.")
        return

    if not 1 <= rows <= 20:
        print("Rows must be between 1 and 20.")
        return

    for i in range(1, rows + 1):
        print(" " * (rows - i) + " ".join(str(n) for n in range(1, i + 1)))

if __name__ == "__main__":
    main()
