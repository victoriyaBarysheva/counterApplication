cmake_minimum_required(VERSION 3.16)

project(CounterApp
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

message(STATUS "Build ${PROJECT_NAME}")

find_package(Qt6 COMPONENTS Core Widgets Sql REQUIRED)

set(HEADERS
    src/presentation/mainwindow.h
    src/presentation/counter.h
    src/data/database.h
    src/data/counter_data.h
    src/data/counter_query.h
    src/usecase/entity/counter_entity.h
    src/usecase/counter_usecase.h
    src/usecase/bases/counter_data_interface.h
    src/usecase/bases/database_interface.h
    src/usecase/bases/counter_query_interface.h
    src/usecase/frequency_usecase.h
)


set(SOURCES
    src/main.cpp
    src/presentation/mainwindow.cpp
    src/data/database.cpp
    src/data/counter_data.cpp
    src/data/counter_query.cpp
    src/usecase/entity/counter_entity.cpp
    src/usecase/counter_usecase.cpp
    src/usecase/frequency_usecase.cpp
)

add_executable(${PROJECT_NAME}
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Sql
)

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION share/${PROJECT_NAME}/lib
    ARCHIVE DESTINATION share/${PROJECT_NAME}/lib
)


