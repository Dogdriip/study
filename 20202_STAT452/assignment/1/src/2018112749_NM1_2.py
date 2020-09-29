# 2018112749_NM1_2.py
# Python 3.8.1 64-bit

from math import *

x = 0.5
result = []


def true_value(_x):
    return 1 / (1 - _x)


def approx(_x, terms):
    res = 0
    for i in range(0, terms):
        res += _x**i
    return res


print("%-7s %-14s %-14s %-14s" % ("terms", "result", "true_error(%)", "approx_error(%)"))
for t in range(1, 11):
    true_val = true_value(x)
    result.append(approx(x, t))
    true_error = (true_val - result[-1]) / true_val * 100
    approx_error = 0 if t == 1 else (result[-1] - result[-2]) / result[-1] * 100

    print("%-7s %-14.9f %-14.9f %-14.9f" % (t, result[-1], true_error, approx_error))
