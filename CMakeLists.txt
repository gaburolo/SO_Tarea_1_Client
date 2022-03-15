cmake_minimum_required(VERSION 3.0.0)
project(Client VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Client 
    src/main.c
    src/services/add_service.h
    src/services/add_service.c
    src/services/encode_b64.h
    src/services/encode_b64.c
    
    
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(OUTPUT_NAME index)
include(CPack)

target_link_libraries(${PROJECT_NAME} b64)
target_link_libraries(${PROJECT_NAME} curl)
