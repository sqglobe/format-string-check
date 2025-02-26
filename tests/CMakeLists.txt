find_package(GTest REQUIRED)


add_executable(format-test format-test.cpp)
target_link_libraries(format-test format-string-check GTest::gtest GTest::gtest_main)

add_test(format-test format-test)
