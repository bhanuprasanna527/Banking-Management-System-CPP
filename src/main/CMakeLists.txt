project(BMS)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME}
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/../../include
            /opt/homebrew/Cellar/libpqxx/7.8.1/include
)

target_link_libraries(${PROJECT_NAME}
        PUBLIC
            /opt/homebrew/Cellar/libpqxx/7.8.1/lib/libpqxx-7.8.dylib
)