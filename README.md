# Проект по "Пользовательским интерфейсам"

## Необходимые инструменты

MinGW 5.1.0 (32-bit) [ссылка](https://drive.google.com/file/d/1iB3V-27KJWSrZfLoH8MLVn23hInXVi_U/view?usp=sharing)  
IDE (Code::Blocks, CLion, etc.)  

См. также Гайд по сборке  
**Важно:** если будете писать тесты, не привязывайте их к своей реализации, особенно это касается проверки кода ошибки (он же `ReturnCode`), если ожидаете ошибку в тесте 
пишите `... != ReturnCode::RC_SUCCESS`, этого вполне достаточно

## Описание интерфейсов
### ILogger
*Логгер, записывает сообщения об ошибках в файл, должен быть реализован как синглтон*  
**Важно:** не забывайте проверять что `logger != nullptr` прежде чем с ним работать в методах других классов

### IVector
*Вектор, компьютерное представление некоторого элемента R^n*  
**Важно:** в случае если в методе который не возвращает ReturnCode произошла собственно ошибка, то в зависимости от возвращаемого типа данных метода кидаем
1. double -> std::nan
2. IVector* -> nullptr  

иначе неясно произошла ошибка или нет и программа продолжит свою работу как ни в чем не бывало

### ISet
*Дискретное множество векторов, компьютерное представление конечного подмножества в R^n*  
**Важно:** если будете писать тесты, исходите из того что мы не знаем в каком порядке векторы занесены в множество, проверяйте методами `ISet::find` и `ISet::get`

## Гайд по сборке
### CLion (Windows)
1. Устанавливаем CLion https://www.jetbrains.com/ru-ru/clion/
2. Скачиваем MinGW по [ссылке](https://drive.google.com/file/d/1iB3V-27KJWSrZfLoH8MLVn23hInXVi_U/view?usp=sharing)
3. Запускаем CLion и устанавливаем MinGW в качестве тулчейна
4. Используем CMake чтобы структурировать проект (см. Возможная структура проекта)
5. Собираем, получаем .dll-ки

## Возможная структура проекта
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