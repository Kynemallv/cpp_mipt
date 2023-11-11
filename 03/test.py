import os
import random
import subprocess
import sys
import pathlib
import matplotlib as mpl
import matplotlib.pyplot as plt


def generate_random_data(n: int) -> str:
    name = ''

    with open(f"input{n}.txt", "w") as file:
        name = file.name
        for i in range(n):
            file.write(f"{i + random.random()*random.randint(1, 5)} {i + random.random()*random.randint(1, 5)}\n")

    return name


def create_plot(filename: str, a: float, b: float) -> None:
    _, ax = plt.subplots()
    data = [[], []]
    with open(filename, 'r') as file:
        for line in file.readlines():
            x, y = map(float, line.split())
            data[0].append(x)
            data[1].append(y)

    x = [min(data[0]), max(data[0])]
    y = [min(data[0])*a + b, max(data[0])*a + b]
    ax.plot(*data, 'ro')
    ax.plot(x, y)
    plt.show()


def close() -> None:
    curr_dir = os.getcwd()
    for file in os.listdir(curr_dir):
        if file.endswith(".txt"):
            os.remove(os.path.join(curr_dir, file))

    sys.exit(0)


def parse_output(output: bytes) -> tuple[str, float, float]:
    output_str = output.decode().strip()
    tmp = output_str.split()
    filename = tmp[0]
    a, b = float(tmp[1]), float(tmp[2])

    return filename, a, b


def pretty_print(filename: str, a: float, b: float, count: int) -> None:
    print(
            f"\n{count})\n"
            f"C++ programm output: {filename} {a} {b}\n"
            + "="*3
    )


def main(iterates: int) -> None:
    tmp = set([random.randint(10, 100) for _ in range(iterates)])
    count = 1

    for t in tmp:
        filename = generate_random_data(t)
        proc = subprocess.Popen([
            "/home/matvey/Projects/MIPT/seminars_cpp/03/least_squares.exe",
            pathlib.Path(filename).absolute()
            ], stdout=subprocess.PIPE)
        output = proc.stdout.read()

        filename, a, b = parse_output(output)
        pretty_print(filename, a, b, count)
        create_plot(filename, b, a)

        count += 1
        input("Press <Enter> to continue")



if __name__ == "__main__":
    if len(sys.argv) > 1:
        mpl.use('Qt5Agg')
        main(int(sys.argv[1]))
        close()
    else:
        print(f"Usage: {__name__} <quantity>")

