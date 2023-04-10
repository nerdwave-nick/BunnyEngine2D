#include <gtest/gtest.h>
int main() {
  auto argc    = 2;
  char* argv[] = {"BunnyTest.exe", "--gtest_color=no", "--gtest_output_on_failure=yes"};

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}