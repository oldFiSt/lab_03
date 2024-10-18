cmake_minimum_required(VERSION 3.10)  # Минимальная версия CMake
project(MyProject)                      # Название вашего проекта

set(CMAKE_CXX_STANDARD 11)              # Установка стандарта C++

# Добавление исполняемого файла
add_executable(MyExecutable main.cpp)   # Создание исполняемого файла из main.cpp

# Включение поддержки тестирования (опционально)
enable_testing()

# Установка конфигурации для пакета
set(CPACK_GENERATOR "DEB")              # Укажите тип пакета (например, DEB для Debian)
set(CPACK_PACKAGE_NAME "MyExecutable")  # Имя пакета
set(CPACK_PACKAGE_VERSION "0.1.0")      # Версия пакета
set(CPACK_PACKAGE_DESCRIPTION "MyExecutable package description")  # Описание пакета

include(CPack)                           # Включение CPack
