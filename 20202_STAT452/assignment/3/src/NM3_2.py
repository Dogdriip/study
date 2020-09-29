from math import *


def f(x):
    return -0.9 * x**2 + 1.7 * x + 2.5


def df(x):
    return -1.8 * x + 1.7


actual_root = 2.8601


if __name__ == "__main__":
    x = [5.0]
    approx_rel_error = []
    true_rel_error = []

    for i in range(0, 4):
        approx_err = 0 if i == 0 else abs(x[-1] - x[-2]) / x[-1] * 100
        true_err = abs(actual_root - x[-1]) / actual_root * 100

        print(f"i: {i}, x_i: {x[-1]:.6f}, f(x_i): {f(x[-1]):.6f}, approx_err: {approx_err:.6f}, true_err: {true_err:.6f}")

        x.append(x[-1] - f(x[-1]) / df(x[-1]))
        approx_rel_error.append(approx_err)
        true_rel_error.append(true_err)

