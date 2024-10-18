cmake_minimum_required(VERSION 3.10)  # Минимальная версия CMake
project(MyProject)                      # Название вашего проекта

set(CMAKE_CXX_STANDARD 11)              # Установка стандарта C++

# Установка типа сборки по умолчанию
set(CMAKE_BUILD_TYPE Release)            # Установка типа сборки на Release

# Добавление исполняемого файла
add_executable(MyExecutable main.cpp)   # Создание исполняемого файла из main.cpp

# Включение поддержки тестирования
enable_testing()

# Если у вас есть тесты, добавьте их здесь
# Например:
# add_executable(MyTest test.cpp)
# target_link_libraries(MyTest PRIVATE MyExecutable)
# add_test(NAME MyTest COMMAND MyTest)  # Регистрация теста
