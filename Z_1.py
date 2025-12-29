import math

def func1(x, dx):
    y_values = []
    while x <= -2:
        y = x + 3
        y_values.append(y)
        x += dx
    return y_values

def func2(x, dx):
    y_values = []
    while x <= 4:
        y = x * (-0.5)
        y_values.append(y)
        x += dx
    return y_values

def func3(x, dx):
    y_values = []
    while x <= 6:
        y = -2
        y_values.append(y)
        x += dx
    return y_values

def func4(x, dx):
    y_values = []
    while x <= 10:
        a, b, r = 8, -2, 2
        y = math.sqrt(pow(r, 2) - pow(x, 2) + (2 * a * x) - pow(a, 2)) + b
        y_values.append(y)
        x += dx
    return y_values

def main_func(x, dx):
    all_y_values = []

    all_y_values.append(func1(x, dx))
    x = -1.5
    all_y_values.append(func2(x, dx))
    x = 4.5
    all_y_values.append(func3(x, dx))
    x = 6.5
    all_y_values.append(func4(x, dx))

    print("-4< x <-2\t|\t-2< x <4\t|\t4< x <6\t|\t6< x <10")
    print("______________________________________________________________________________")

    max_size = max(len(y_values) for y_values in all_y_values)

    for i in range(max_size):
        for y_values in all_y_values:
            if i < len(y_values):
                print(f" {y_values[i]:.2f}\t|\t", end="")
            else:
                print(" \t|\t", end="")
        print()

x = -4
dx = 0.5

main_func(x, dx)