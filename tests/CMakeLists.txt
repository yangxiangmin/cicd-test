# tests/CMakeLists.txt
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)  # 添加这一行
include_directories(${GTEST_INCLUDE_DIRS} ../include)

add_executable(run_tests 
    test_math.cpp 
    ../src/math.cpp
)
target_link_libraries(run_tests ${GTEST_LIBRARIES} pthread)

#mkdir build && cd build
#cmake .. && make
#./run_tests