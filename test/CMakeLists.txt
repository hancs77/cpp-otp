# set(Test_SRCS TeniseTest.cc)
set(Test_SRCS BudgetTest.cc)
# set(Test_SRCS AuthenticationServiceTest.cc)
# set(Test_SRCS BirthdayTest.cc)

add_executable(cpp_otp_test ${Test_SRCS})
target_link_libraries(cpp_otp_test gtest gmock gtest_main core)
