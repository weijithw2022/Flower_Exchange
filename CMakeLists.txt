cmake_minimum_required(VERSION 3.16)
project(flower-exchange LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(ExchangeAppMain
    src/main.cpp
    src/domain/InputOrder.cpp
    src/domain/OrderBook.cpp
    src/services/OrderIDGenerator.cpp
    src/app/OrderProcessor.cpp
    src/app/FileCleanupService.cpp
    src/validation/OrderValidator.cpp
    src/io/ReadInputOrderCSV.cpp
    src/io/GenerateCSV.cpp
)

target_include_directories(ExchangeAppMain PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/app
    ${CMAKE_CURRENT_SOURCE_DIR}/src/domain
    ${CMAKE_CURRENT_SOURCE_DIR}/src/validation
    ${CMAKE_CURRENT_SOURCE_DIR}/src/interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/src/io
    ${CMAKE_CURRENT_SOURCE_DIR}/src/services
)
