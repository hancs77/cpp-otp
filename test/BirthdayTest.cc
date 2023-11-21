#include "gtest/gtest.h"
#include "../main/Birthday.h"

namespace {

    TEST(Birthday, IsBirthday) {
        Birthday birthday;

        bool actual = birthday.IsBirthday(11, 21);

        ASSERT_TRUE(actual);
    }

}