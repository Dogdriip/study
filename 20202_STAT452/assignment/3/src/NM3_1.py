from math import *


def f(x):
    return sin(sqrt(x))
    # return exp(-x)


actual_root = 0.7686
# actual_root = 0.5671


if __name__ == "__main__":
    x = [0.5]
    approx_rel_error = []
    true_rel_error = []

    for i in range(0, 4):
        approx_err = 0 if i == 0 else abs(x[-1] - x[-2]) / x[-1] * 100
        true_err = abs(actual_root - x[-1]) / actual_root * 100

        print(f"i: {i}, x_i: {x[-1]:.6f}, f(x_i): {f(x[-1]):.6f}, approx_err: {approx_err:.6f}, true_err: {true_err:.6f}")

        x.append(f(x[-1]))
        approx_rel_error.append(approx_err)
        true_rel_error.append(true_err)

