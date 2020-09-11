# Проект по "Пользовательским интерфейсам"

## Необходимые инструменты

MinGW 5.1.0 (32-bit) [ссылка](https://drive.google.com/file/d/1iB3V-27KJWSrZfLoH8MLVn23hInXVi_U/view?usp=sharing)  
IDE (Code::Blocks, CLion, etc.)  
Стандарт C++11

См. также [гайд по сборке](#guide)  
**Важно:** если будете писать тесты, не привязывайте их к своей реализации, особенно это касается проверки кода ошибки (он же `ReturnCode`), если ожидаете ошибку в тесте 
пишите `... != ReturnCode::RC_SUCCESS`, этого вполне достаточно

## Описание интерфейсов
### ILogger
*Логгер, записывает сообщения об ошибках в файл, должен быть реализован как синглтон*  
**Важно:** не забывайте проверять что `logger != nullptr` прежде чем с ним работать в методах других классов

### IVector
*Вектор, компьютерное представление некоторого элемента R^n*  
**Важно:** в случае если в методе который не возвращает ReturnCode произошла собственно ошибка, то в зависимости от возвращаемого типа данных метода кидаем
1. double: std::nan
2. IVector*: nullptr 
3. bool: false

иначе неясно произошла ошибка или нет и программа продолжит свою работу как ни в чем не бывало, 3 пункт особенно важен в сравнении векторов методом `IVector::equals`: допустим этот метод получил 2 вектора разной размерности, хотя это и считается ошибкой - логично что они не равны, а пользователь может ожидать что равны и обломается.

### ISet
*Дискретное множество векторов, компьютерное представление конечного подмножества в R^n*  
**Важно:** в методе `ISet::find` если элемент не найден возвращается `ReturnCode::RC_ELEM_NOT_FOUND`. Если будете писать тесты, исходите из того что мы не знаем в каком порядке векторы занесены в множество, проверяйте методами `ISet::find` и `ISet::get`

### ICompact
*Компьютерное представление параллеллепипеда в R^n, задается началом и концом*  
**Важно:** запрещается вырожденный компакт т.е. при создании координаты начала должны быть строго меньше координат конца, а в результате операций должен получаться компакт начало и конец которого отличаются на некоторую ε (указана как `double tolerance` в методах). При получении итератора для компакта, необходимо задать шаг `IVector* step`, координаты которого неотрицательные.

<a name="guide"><h2>Гайд по сборке</h2></a>
### CLion
1. Устанавливаем CLion https://www.jetbrains.com/ru-ru/clion/
2. Скачиваем MinGW по [ссылке](https://drive.google.com/file/d/1iB3V-27KJWSrZfLoH8MLVn23hInXVi_U/view?usp=sharing)
3. Запускаем CLion и устанавливаем MinGW в качестве тулчейна
4. Используем CMake чтобы структурировать проект (см. [возможная структура проекта](#structure))
5. Собираем, получаем .dll-ки и .exe-шник с тестами
6. Возможно со стороны системы поступит жалоба об отсутствии libstdc++-6.dll, для решения проблемы пропишите путь до MINGW5.1.0\bin в системную переменную PATH

### Code::Blocks
1. Для начала в кодблохе выбрать Setting->Compiler->Global compiler settings:
-тут в selected compiler выбрать GNU GCC Compiler
-открываем вкладку toolchain executables, в Compiler's installation directory прописываем путь к MinGW 5.1.0 и можно нажать auto-detect. Если при этом во поле Program Files не выберутся нужные .exe-шники, то нужно их прописать вручную: (C compiler - gcc.exe, C++ compiler - g++.exe, linker for dynamic libs - g++.exe, linker for static libs - ar.exe, make program - mingw32-make.exe)
2. Как создать .dll-ку:
   1. File->New->Project->Empty Project->при выборе компилятора выбрать GNU GCC Compiler.
   2. Можно нажать правой кнопкой мыши на созданный проект->Add files recursively, далее выбрать директорию со всеми исходниками (где внутри будут src и include), чтобы добавить их.
   3. Снова правой кнопкой мыши по проекту->build properties->project's build options->слева выбрать название проекта(НЕ отдельно debug и release)->compiler settings->compiler flags, тут выбрать флаги:  
static libgcc [-static-libgcc]  
static libstdc++ [-static-libstdc++]  
target x86 (32bit) [-m32]  
первые два на самом деле нужны только для .exe-шника с тестами прописывать, чтобы он не запрашивал пару дополнительных библиотек (libstdc++-6.dll и libgcc_s_<что-то>.dll) при запуске не из IDE. но можно и в PATH к ним путь прописать (они есть в MinGW5.1.0\bin)
   4. Назад в build options->build targets:
      1. Тут для каждой конфигурации (debug/release) нужно указать type->dynamic library
      2. Галочку с create .DEF exports file можно убрать
      3. Import library filename можно прописать вручную, куда вы хотите, чтобы сохранялись библиотеки импорта (gcc породит .a файлы, они нужны для последующей линковки ваших длл между собой и их же с .exe-шником с тестами)
3. Как собрать проект (.dll или .ехе), который должен тянуть какую-то .dll (например vector.dll хочет тянуть logger.dll):
Снова правой кнопкой мыши->build options->project's build options->linker settings. Может быть важным что .a файлы собираются для разных конфигураций разные и здесь в Link libraries->add следует выбирать .a файлы нужных библиотек в соответствии с конфигурацией, их все нужно указать для успешной сборки.

<a name="structure"><h2>Возможная структура проекта</h2></a>
```
+--Root  
   |  
   --CMakeLists.txt  
   |  
   +--src                         исходный код
   |  |
   |  |
   |  +--Vector                   здесь вот Вектор, например
   |  |  |
   |  |  --CMakeLists.txt
   |  |  |
   |  |  +--include
   |  |  |  |
   |  |  |  --IVector.h
   |  |  |
   |  |  --VectorImpl.cpp
   |  |  |
   |  |  --IVector.cpp
   |  |
   |  +--Logger                   а тут вот Логгер, например
   |  |  |
   |  |  ...
   |  |
   |  +--Utils                    а тут вот вспомогательные .h файлы, без них ничего работать не будет!!!
   |  |  |
   |  |  --Export.h
   |  |  |
   |  |  --ReturnCode.h
   |  |
   |  ...
   |
   +--test                        здесь свои тесты напишете
   |  |
   |  --CMakeLists.txt
   |  |
   |  --main.cpp
   |
   +--bin                         здесь после сборки материализуются исполняемые файлы
```

**Root\CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 3.17)
project(%вставьте ваше название проекта%)

# это важно
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_SHARED_LIBRARY_PREFIX "")

# тесты тут
add_subdirectory(test)

# исходный код тут
add_subdirectory(src)
```
**Root\src\CMakeLists.txt**
```cmake
add_subdirectory(Logger)
add_subdirectory(Vector)
...
```
**Root\src\Vector\CMakeLists.txt**
```cmake
# сообщаем о динамической библиотеке и из каких файлов она будет собрана
add_library(vector SHARED
        include/IVector.h
        IVector.cpp
        VectorImpl.cpp)

# сообщаем какие includ'ы будут видны извне
target_include_directories(vector PUBLIC include)

# исполняемые файлы должны перекидываться в bin
set_target_properties(vector PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ..\\..\\..\\bin
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ..\\..\\..\\bin
        )

# зависимости этой библиотеки (logger вряд ли нуждается в такой строчке если вы не реализуете его с использованием чужих библиотек)
target_link_libraries(vector PUBLIC logger)
```
**Root\test\CMakeLists.txt**
```cmake
# сообщаем об .exe-шнике и из каких файлов он будет собран
add_executable(test main.cpp)

# подключаем все библиотеки которые тестируем
target_link_libraries(test PUBLIC logger vector)

# .exe-шник должен перекинуться в bin
set_target_properties(test PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ..\\..\\bin
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ..\\..\\bin
        )
```


## Credits
* [Петрунин Григорий](https://github.com/via8) - создал все интерфейсы и вообще хороший человек
* [Самутичев Евгений](https://github.com/zhenyatos) - мимокрокодил расписал как тут чего работает
