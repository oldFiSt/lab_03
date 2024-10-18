cmake_minimum_required(VERSION 3.10)  # Минимальная версия CMake
project(MyProject)                      # Название вашего проекта

set(CMAKE_CXX_STANDARD 11)              # Установка стандарта C++

# Укажите директорию для поиска заголовочных файлов
include_directories(${CMAKE_SOURCE_DIR}/resources)

# Добавление исполняемого файла
add_executable(MyExecutable main.cpp)

# Например, если у вас есть файлы в папке resources:
file(GLOB_RECURSE RESOURCE_FILES resources/*.cpp resources/*.h)
target_sources(MyExecutable PRIVATE ${RESOURCE_FILES})

