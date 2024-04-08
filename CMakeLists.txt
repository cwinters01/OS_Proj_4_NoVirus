cmake_minimum_required (VERSION 3.14)
project(hw4)

#set(CMAKE_C_FLAGS "-std=c11 -Wall -Wextra -Wshadow -Werror -D_XOPEN_SOURCE=500")
#set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wshadow -Werror -Wno-sign-compare -D_XOPEN_SOURCE=500")

set(CMAKE_C_FLAGS "-std=c11 -Wall -Wextra -Wshadow -Werror")
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wshadow -Werror")

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif ()

include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(proj4_pthread 3way-pthread/proj4_pthread.c)

#add_executable(proj4_pthread_test 3way-pthread/proj4_pthread.c)

# link the proj4_pthread library we compiled against our proj4_pthread_test executable.
#target_link_libraries(proj4_pthread_test proj4_pthread)

# make an executable
add_executable(${PROJECT_NAME}_test 3way-pthread/proj4_pthread.c)
target_compile_definitions(${PROJECT_NAME}_test PRIVATE)
target_link_libraries(${PROJECT_NAME}_test gtest pthread proj4_pthread)
