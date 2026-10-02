def main():
    print("=== Temperature Converter ===")
    print("1. Celsius to Fahrenheit")
    print("2. Fahrenheit to Celsius")
    choice = input("Choose: ").strip()

    try:
        temp = float(input("Temperature: "))
    except ValueError:
        print("Invalid temperature.")
        return

    if choice == "1":
        print(f"{temp:.2f} C = {(temp * 9 / 5 + 32):.2f} F")
    elif choice == "2":
        print(f"{temp:.2f} F = {((temp - 32) * 5 / 9):.2f} C")
    else:
        print("Invalid option.")

if __name__ == "__main__":
    main()
