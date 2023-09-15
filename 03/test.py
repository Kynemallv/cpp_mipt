import random
import subprocess
import sys
import pathlib


def generate_random_data(n: int) -> str:
    name = ''

    with open(f"input{n}.txt", "w") as file:
        name = file.name
        for _ in range(n):
            file.write(f"{random.randint(1, 1000)} {random.randint(1, 1000)}\n")

    return name




def main(iterates: int) -> None:
    tmp = set([random.randint(100, 1000) for _ in range(iterates)])

    for t in tmp:
        filename = generate_random_data(t)
        subprocess.call([
            "/home/matvey/Projects/MIPT/seminars_cpp/03/least_squares.exe",
            pathlib.Path(filename).absolute()
            ])


if __name__ == "__main__":
    if len(sys.argv) > 1:
        main(int(sys.argv[1]))
    else:
        print(f"Usage: {__name__} <quantity>")

