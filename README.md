# C DLL 教学 / C DLL Tutorial

本目录专门演示：普通 C 源码如何编译成 DLL，并被其他语言调用。

This directory demonstrates how ordinary C code can be compiled into a DLL and called from another language.

- 中文教程：[zh/README.md](zh/README.md)
- English tutorial：[en/README.md](en/README.md)

两个目录使用相同的简单计算器例子：

```text
calculator.c --gcc--> calculator.dll --ctypes--> use_dll.py
calculator.c --gcc--> calculator.exe
```

The same simple calculator example is available in both folders.

## License

This project is released under the MIT License. See [LICENSE](LICENSE).

本项目采用 MIT 许可证，详见 [LICENSE](LICENSE)。
