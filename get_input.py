#!/usr/bin/env python
import os
import sys
import requests
from dotenv import dotenv_values

def main():
    if (len(sys.argv) != 2 or not sys.argv[1].isnumeric()):
        print(f"usage: {sys.argv[0]} day_number")
        return 1

    day = int(sys.argv[1])
    if (day < 1 or day > 25):
        print("day must be between 1 and 25 inclusive")
        return 1

    session_cookie = dotenv_values().get("SESSION_COOKIE")
    if not session_cookie:
        print("please put your session cookie in the .env file")
        return 1
    
    with requests.get(f"https://adventofcode.com/2021/day/{day}/input", cookies={"session": session_cookie}) as r:
        if r.status_code != 200:
            print("unable to get input data")
            return 2
        os.system(f"mkdir -p {day}")
        with open(f"{day}/input.txt", "w") as f:
            f.write(r.text)

    return 0

if __name__ == "__main__":
    sys.exit(main())
