## StringProject

## Description
- Реализация класса динамических строк **String** на **C++11** без использования **STL**.

- Программа пример принимающая на ввод список строк до конца ввода (**^Z** или **^D**).

- Модульные тесты (**GoogleTest**).

## Project structure

```
                        StringProject/├── src/                
               Исходный код библиотеки│   ├── nstring/        
Пример с использованием STL-контейнера│   └── example/        
                    Тесты(GoogleTests)├── └── tests/              
            Генерируемая папка сборки ├── build/                           
                                      └── CMakeLists.txt
```

## Requrements

**CMake 3.16+**

**GCC** / **Clang** / **MSVC**

## Quick start
```
cmake -S . -B build 
cmake --build build
./build/src/example/StrExample # Пример 
./build/src/tests/StrTests # Тесты
```
