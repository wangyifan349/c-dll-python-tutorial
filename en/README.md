# Compile C into a DLL and Call It from Python

This tutorial covers one simple idea: **the same ordinary C source file can be compiled into a DLL or directly into an EXE; Python uses `ctypes` to call the functions in the DLL.**

```text
calculator.c --gcc--> calculator.dll --ctypes--> use_dll.py
calculator.c --gcc--> calculator.exe
```

## Files

```text
en/
├── calculator.c       C source code
├── use_dll.py         Python DLL caller
└── README.md          this tutorial
```

The repository intentionally does not include DLL, EXE, or other binary files. This keeps the published content transparent and avoids false antivirus reports. Build them locally with the commands below.

## 1. Compile directly into an EXE

Open PowerShell in this folder:

```powershell
gcc calculator.c -o calculator.exe
.\calculator.exe
```

GCC compiles and runs the `main()` function. The program performs the four calculator operations directly.

## 2. Compile the same source into a DLL

Use the same `calculator.c` file:

```powershell
gcc -shared -O2 calculator.c -o calculator.dll
```

`-shared` means “create a dynamic library.” A DLL does not run like an EXE; it provides functions for another program to load and call.

## 3. Call the DLL from Python

```powershell
python use_dll.py
```

Expected output:

```text
2 + 3 = 5.0
8 - 3 = 5.0
4 * 5 = 20.0
10 / 2 = 5.0
10 / 0 = Error: division by zero
```

## 4. Important parts of the C source

```c
#define DLL_API __declspec(dllexport)

DLL_API double add(double a, double b)
{
    return a + b;
}
```

`__declspec(dllexport)` exports `add`, so another program can find it in the DLL.

```c
int main(void)
{
    printf("%.2f\n", add(2, 3));
    return 0;
}
```

`main()` lets this file build as an EXE too. When building the DLL, `main()` is compiled into it but Python does not call it. Python calls only the exported `add`, `subtract`, `multiply`, and `divide` functions.

## 5. C and Python types

`use_dll.py` must tell `ctypes` the C function types:

| C type | ctypes type |
|---|---|
| `double` | `ctypes.c_double` |
| `int` | `ctypes.c_int` |
| `double *` | `ctypes.POINTER(ctypes.c_double)` |

For example, this C function:

```c
double add(double a, double b);
```

uses this Python declaration:

```python
calculator.add.argtypes = [ctypes.c_double, ctypes.c_double]
calculator.add.restype = ctypes.c_double
```

## 6. DLL and EXE

- **EXE**: has `main()` and can run directly.
- **DLL**: normally provides functions and waits for another program to load it.
- **Python**: uses `ctypes.CDLL()` to load the DLL and call its exported functions.

## 7. Cross-language and cross-device notes

This is a regular DLL and does not depend on the Python C API. Therefore Python 3.10, 3.11, 3.12, and other versions can call it with `ctypes`, as long as the operating system and architecture match.

Remember:

1. A Windows DLL normally cannot be used directly on Linux or macOS.
2. 32-bit callers need a 32-bit DLL; 64-bit callers need a 64-bit DLL.
3. The DLL and its caller must agree on function argument types and calling conventions.
4. The target machine also needs the C runtime libraries required by the DLL.

## 8. Suggested exercise

Run `calculator.exe` first, then run `python use_dll.py`. Both use the same C source file. The first calls the functions from a C program; the second calls the functions from Python through the DLL.

## MIT License

This tutorial is released under the MIT License. See the full text in the project root: [LICENSE](../LICENSE).
