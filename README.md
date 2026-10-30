# NamedPipe-Audit

<div align="center">

![Platform](https://img.shields.io/badge/Platform-Windows-0078D4?style=flat-square&logo=windows)
![Language](https://img.shields.io/badge/Language-C%2B%2B20-00599C?style=flat-square&logo=c%2B%2B)
![License](https://img.shields.io/badge/License-MIT-blue?style=flat-square)
![Build](https://img.shields.io/badge/Build-Passing-brightgreen?style=flat-square)

**Аудитор межпроцессных каналов (IPC Named Pipes) в пространстве Windows NT.**  
*Прямое перечисление пула `\\.\pipe\*` через нативный Win32 Device Namespace API без PowerShell или сторонних утилит.*

</div>

---

## Архитектура

- Использование `FindFirstFileW` / `FindNextFileW` для прямого обхода скрытого пространства имен ядра `\\.\pipe\*`.
- Позволяет мгновенно обнаружить скрытые каналы IPC, используемые бэкдорами, RPC-серверами или вредоносными службами для межпроцессного взаимодействия.

## Сборка и тесты

```powershell
g++ -std=c++20 -O2 tests/test_main.cpp -o namedpipe_tests.exe
.\namedpipe_tests.exe
```

## Лицензия
MIT

<!-- verified: 2026-10-30 -->