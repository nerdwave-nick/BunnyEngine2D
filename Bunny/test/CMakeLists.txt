file(GLOB bunnyTest_SRC
"*.h"
"*.cpp"
)
file(GLOB_RECURSE bunnyTest_SRC CONFIGURE_DEPENDS "*.h" "*.cpp")
add_executable(BunnyTest
  ${bunnyTest_SRC}
)
target_link_libraries(BunnyTest PRIVATE Bunny GTest::gtest)
target_include_directories(BunnyTest PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)

include(GoogleTest)
gtest_discover_tests(BunnyTest)
