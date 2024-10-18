cmake_minimum_required(VERSION 3.10)

project(IFilterProject VERSION 0.1.0)

# Найти Boost
find_package(Boost REQUIRED COMPONENTS unit_test_framework)

# Создание библиотеки и исполняемого файла
add_executable(22 main.cpp)


# Установка директорий для заголовочных файлов


# Копирование ресурсов (если необходимо)
set(RESOURCE_FILES 
    resources/ic.icns 
    
)

foreach(RESOURCE ${RESOURCE_FILES})
    configure_file(${RESOURCE} ${CMAKE_BINARY_DIR}/${RESOURCE} COPYONLY)
endforeach()

# Включение CPack для создания пакетов
include(CPack)

# Настройки для CPack
set(CPACK_PACKAGE_NAME "ip_filter")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION "A description of your package.")
set(CPACK_PACKAGE_LICENSE "MIT")
set(CPACK_GENERATOR "DEB")


# Установка ресурсов в пакет (если необходимо)
install(FILES ${RESOURCE_FILES} DESTINATION resources)

message("Configured PROJECT_VERSION: ${PROJECT_VERSION}")