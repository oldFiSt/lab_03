cmake_minimum_required(VERSION 3.10)  # Минимальная версия CMake
project(MyProject)                      # Название вашего проекта

set(CMAKE_CXX_STANDARD 11)              # Установка стандарта C++

# Добавление исполняемого файла
add_executable(MyExecutable main.cpp)   # Создание исполняемого файла из main.cpp

# Установка целевого каталога для установки
set(CMAKE_INSTALL_PREFIX "/usr/local")  # Установка по умолчанию

# Установка исполняемого файла
install(TARGETS MyExecutable DESTINATION bin)  # Установка исполняемого файла в /usr/local/bin

# Установка конфигурации для пакета
set(CPACK_GENERATOR "DEB")              # Укажите тип пакета (например, DEB для Debian)
set(CPACK_PACKAGE_NAME "MyExecutable")  # Имя пакета
set(CPACK_PACKAGE_VERSION "0.1.0")      # Версия пакета
set(CPACK_PACKAGE_DESCRIPTION "MyExecutable package description")  # Описание пакета
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Your Name <your.email@example.com>")  # Имя и email поддерживающего
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.3.1-6)")  # Зависимости, если есть

# Дополнительные параметры
set(CPACK_PACKAGE_CONTACT "Your Name <your.email@example.com>")  # Контактная информация
set(CPACK_PACKAGE_HOMEPAGE "https://example.com")                # Домашняя страница проекта
set(CPACK_PACKAGE_LICENSE "MIT")                                  # Лицензия проекта

include(CPack)                           # Включение CPack
