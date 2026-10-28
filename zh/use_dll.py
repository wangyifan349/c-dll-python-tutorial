"""使用 Python ctypes 调用 calculator.dll。"""

import ctypes
from pathlib import Path


dll_path = Path(__file__).with_name("calculator.dll")
calculator = ctypes.CDLL(str(dll_path))

calculator.add.argtypes = [ctypes.c_double, ctypes.c_double]
calculator.add.restype = ctypes.c_double

calculator.subtract.argtypes = [ctypes.c_double, ctypes.c_double]
calculator.subtract.restype = ctypes.c_double

calculator.multiply.argtypes = [ctypes.c_double, ctypes.c_double]
calculator.multiply.restype = ctypes.c_double

calculator.divide.argtypes = [
    ctypes.c_double,
    ctypes.c_double,
    ctypes.POINTER(ctypes.c_double),
]
calculator.divide.restype = ctypes.c_int


print("2 + 3 =", calculator.add(2, 3))
print("8 - 3 =", calculator.subtract(8, 3))
print("4 * 5 =", calculator.multiply(4, 5))

result = ctypes.c_double()
if calculator.divide(10, 2, ctypes.byref(result)):
    print("10 / 2 =", result.value)

if not calculator.divide(10, 0, ctypes.byref(result)):
    print("10 / 0 = 错误：不能除以 0")
