import sys

sys.path = ['', '/usr/lib/python2.7', '/usr/lib/python2.7/plat-linux2', '/usr/lib/python2.7/lib-tk', '/usr/lib/python2.7/lib-old', '/usr/lib/python2.7/lib-dynload', '/usr/local/lib/python2.7/dist-packages', '/usr/lib/python2.7/dist-packages']

import ctypes

lib = ctypes.CDLL('bin/call_test.so')


def test_return_int():
    return 5


def test_return_string():
    return "UROP"


def test_pass_integer(n):
    return n + 1


def test_call_c():
    return lib.test_return_int(5) * 5
