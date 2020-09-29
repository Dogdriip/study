# 2018112749_NM1_1.py
# Python 3.8.1 64-bit

from math import *

g = 9.81
c_d = 0.25
m = 80
numeric = []


def analytic_func(_t):
    return sqrt(g * m / c_d) * tanh(sqrt(g * c_d / m) * _t)


def numeric_func(prev, _t):
    return prev + (g - (c_d * prev ** 2) / m) * 2


print("%-2s %-8s %-7s %-10s %-14s %-14s" % ("t", "analytic", "numeric", "difference", "true_error(%)", "approx_error(%)"))
for t in range(0, 14, 2):
    analytic = analytic_func(t)
    numeric.append(0 if t == 0 else numeric_func(numeric[-1], t))

    true_error = 0 if t == 0 else (analytic - numeric[-1]) / analytic * 100
    approx_error = 0 if t == 0 else (numeric[-1] - numeric[-2]) / numeric[-1] * 100

    print("%-2d %-8.3f %-7.3f %-10.3f %-14.9f %-14.9f" % (t, analytic, numeric[-1], analytic - numeric[-1], true_error, approx_error))
