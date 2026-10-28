# C 编译 DLL 并被 Python 调用

本教程只讲一件事：**同一个普通 C 源文件，可以编译成 DLL，也可以直接编译成 EXE；Python 使用 `ctypes` 调用 DLL 中的函数。**

```text
calculator.c --gcc--> calculator.dll --ctypes--> use_dll.py
calculator.c --gcc--> calculator.exe
```

## 文件

```text
zh/
├── calculator.c       C 源码
├── use_dll.py         Python 调用 DLL
└── README.md          本教程
```

本仓库不包含 DLL、EXE 等二进制文件，避免误报并保持发布内容安全透明。请在本机按照下面的命令编译。

## 1. 直接编译成 EXE

在这个文件夹打开 PowerShell：

```powershell
gcc calculator.c -o calculator.exe
./calculator.exe
```

如果终端不支持上面的中文路径写法，也可以直接双击 `calculator.exe`。

这时 GCC 会编译 `main()`，程序直接执行四则运算。

## 2. 编译成 DLL

使用同一个 `calculator.c`：

```powershell
gcc -shared -O2 calculator.c -o calculator.dll
```

`-shared` 表示生成动态库。DLL 不会像 EXE 那样直接运行，它提供函数，等待其他程序加载和调用。

## 3. Python 调用 DLL

```powershell
python use_dll.py
```

Python 输出：

```text
2 + 3 = 5.0
8 - 3 = 5.0
4 * 5 = 20.0
10 / 2 = 5.0
10 / 0 = 错误：不能除以 0
```

## 4. C 源码的重点

```c
#define DLL_API __declspec(dllexport)

DLL_API double add(double a, double b)
{
    return a + b;
}
```

`__declspec(dllexport)` 把 `add` 导出，其他程序才能从 DLL 中找到它。

```c
int main(void)
{
    printf("%.2f\n", add(2, 3));
    return 0;
}
```

`main()` 让这份代码也可以直接编译成 EXE。编译 DLL 时，`main()` 会被编译进去，但 Python 不会调用它；Python 只调用导出的 `add`、`subtract`、`multiply`、`divide`。

## 5. Python 类型对应

`use_dll.py` 中必须告诉 `ctypes` C 函数的类型：

| C 类型 | ctypes 类型 |
|---|---|
| `double` | `ctypes.c_double` |
| `int` | `ctypes.c_int` |
| `double *` | `ctypes.POINTER(ctypes.c_double)` |

例如 C 函数：

```c
double add(double a, double b);
```

对应 Python 设置：

```python
calculator.add.argtypes = [ctypes.c_double, ctypes.c_double]
calculator.add.restype = ctypes.c_double
```

## 6. DLL 和 EXE 的区别

- **EXE**：有 `main()`，编译后可以直接运行。
- **DLL**：通常提供函数，没有自己的运行流程，等待其他程序加载。
- **Python**：通过 `ctypes.CDLL()` 加载 DLL，再调用导出的函数。

## 7. 跨语言和跨设备

这个 DLL 是普通 DLL，不依赖 Python C API，所以 Python 3.10、3.11、3.12 等版本都可以通过 `ctypes` 调用，只要系统和架构匹配。

注意：

1. Windows DLL 通常不能直接拿到 Linux 或 macOS 使用。
2. 32 位程序需要 32 位 DLL，64 位程序需要 64 位 DLL。
3. DLL 和调用方必须使用一致的函数参数类型和调用约定。
4. 目标设备还需要 DLL 所依赖的 C 运行库。

## 8. 学习建议

先运行 `calculator.exe`，再运行 `python use_dll.py`。两次运行使用的是同一个 C 文件，但第一次是 C 程序直接调用函数，第二次是 Python 调用了 DLL 中的函数。

## MIT 许可证

本教程采用 MIT License，完整文本见项目根目录的 [LICENSE](../LICENSE)。
