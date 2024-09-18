cmake_minimum_required(VERSION 3.30.3)
project(vocabLearning C)

add_executable(${PROJECT_NAME} src/main.c src/dbManager.c src/dbManagerGTK.c)

find_package(libmongoc-1.0 REQUIRED)
find_package(PkgConfig REQUIRED) 

pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)

target_include_directories(${PROJECT_NAME} PRIVATE "${MONGOC_INCLUDE_DIRS}")
target_link_libraries(${PROJECT_NAME} PRIVATE "${MONGOC_LIBRARIES}")
target_compile_definitions(${PROJECT_NAME} PRIVATE "${MONGOC_DEFINITIONS}")

target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::GTK4)