import random

def main():
    print("=== Number Guessing Game ===")
    print("Guess a number between 1 and 100. You have 7 valid attempts.")
    secret = random.randint(1, 100)
    attempts = 0

    while attempts < 7:
        try:
            guess = int(input(f"Attempt {attempts + 1}/7: "))
        except ValueError:
            print("Enter a valid whole number.")
            continue

        if not 1 <= guess <= 100:
            print("Enter a number from 1 to 100.")
            continue

        attempts += 1
        if guess == secret:
            print(f"Correct! You won in {attempts} attempt(s).")
            return
        elif guess < secret:
            print("Too low.")
        else:
            print("Too high.")

    print(f"Game over. The number was {secret}.")

if __name__ == "__main__":
    main()
