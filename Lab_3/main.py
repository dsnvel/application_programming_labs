import re


class FormatException(Exception):
    pass


def check_format(number: str) -> None:
    # r"(\d{3})\-(\d{3})\-(\d{3})\[:space:]\d{2}"
    number_by_parts: list = number.split(" ")
    first_part: str = "".join(number_by_parts[0].split("-"))
    regular_expressions = r"(\d{3})\-(\d{3})\-(\d{3})(\s{1})(\d{2})$"
    result = re.search(regular_expressions, number)
    # print(first_part)
    # print(result is None, not check_repetitions(first_part))
    if result is None or not check_repetitions(first_part):
        # print(check_repetitions(first_part))
        raise FormatException(f"[ERROR] Incorrect format: {number}")


def get_control_summary(summary: int) -> int:
    if summary > 101:
        summary %= 101
    elif summary == 100 or summary == 101:
        summary = 0
    return summary


def check_control_summary(number: str) -> bool:
    separation_symbol: str = number[3]
    # print(number)
    if separation_symbol == "-":
        parts: list = number.split(" ")
        # print(parts)
        first_part: str = ''.join(parts[0].split("-"))
        second_part: int = int(parts[1])
        # print(first_part, second_part)
    else:
        part1, part2, part3, part4 = number.split(" ")
        first_part: str = part1 + part2 + part3
        second_part: int = int(part4)
    formatted_first_part: str = "".join(first_part.split("-"))
    summary: int = 0
    count_of_digits: int = len(formatted_first_part)
    for i in range(1, count_of_digits+1):
        # print(int(formatted_first_part[i-1]), (count_of_digits-i+1))
        summary += int(formatted_first_part[i-1]) * (count_of_digits-i+1)
    result: int = get_control_summary(summary)
    # print(result, second_part)
    # print(result == second_part)
    return result == second_part


def check_repetitions(first_part: str) -> bool:
    separation_symbol: str = first_part[3]
    formatted_number: str = "".join(first_part.split(separation_symbol))
    counter: int = 1
    for i in range(len(formatted_number) - 1):
        if formatted_number[i] == formatted_number[i + 1]:
            counter += 1
            # print(counter)
            if counter == 3:
                # print("Three symbols in a row!")
                return False
        else:
            counter = 1
    return True


def checking_correctly(number: str) -> None:
    """«ХХХ-ХХХ-ХХХ YY»
    X - random number
    YY - controlling summary"""
    try:
        check_format(number)
        if check_control_summary(number):
            print(f"[+] Correct SNILS number: {number}")
        else:
            print(f"[-] Incorrect SNILS summary: {number}")
    except FormatException as error:
        print(error)


def test_cases():
    print("------------Test start------------")
    checking_correctly("886-535-861 78")  # Correct
    checking_correctly("886-555-861 78")  # Not correct format
    checking_correctly("886-535-861 078")  # Not correct format
    checking_correctly("886-535-8612 078")  # Not correct format
    checking_correctly("886-535-861 80")  # Not correct control summary
    print("------------Test end--------------\n")


def main():
    test_cases()
    user_input = input("Enter SNILS number («ХХХ-ХХХ-ХХХ YY»): ")
    checking_correctly(user_input)


if __name__ == "__main__":
    main()
