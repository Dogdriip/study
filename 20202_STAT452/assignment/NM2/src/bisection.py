from math import *


def f(x):
    return exp(-x) * (3.2*sin(x) - 0.3*cos(x))


x_l = 3
x_u = 4

if __name__ == "__main__":
    for i in range(6):
        x_r = (x_l + x_u) / 2
        print(f"iteration {i}: ")
        print(f"x_l: {x_l:.6f}, x_u: {x_u:.6f}, x_r: {x_r:.6f}, f(x_l): {f(x_l):.6f}, f(x_u): {f(x_u):.6f}, f(x_r): {f(x_r):.6f}")

        if f(x_r) > 0:
            x_u = x_r
        else:
            x_l = x_r
