#include "gtest/gtest.h"

class TeniseScore {
public:
    TeniseScore() {}
    std::string getScore() {
        if (_p1 == 1) {
            return "Fifteen Love";
        }
        if (_p1 == 2) {
            return "Thirty Love";
        }
        if (_p1 == 3) {
            return "Fourty Love";
        }
        return "Love All";
    }

    void p1Win() {
        _p1++;
    }
private:
    int _p1 = 0;
    int _p2 = 0;
};

namespace {

    TEST(TeniseTest, testScore_0_0) {
        // GIVEN
        TeniseScore tenise = TeniseScore();

        // WHEN
        std::string score = tenise.getScore();
        
        // THEN
        ASSERT_EQ(score, "Love All");
    }

    TEST(TeniseTest, testScore_1_0) {
        // GIVEN
        TeniseScore tenise = TeniseScore();
        tenise.p1Win();

        // WHEN
        std::string score = tenise.getScore();
        
        // THEN
        ASSERT_EQ(score, "Fifteen Love");
    }

    TEST(TeniseTest, testScore_2_0) {
        // GIVEN
        TeniseScore tenise = TeniseScore();
        tenise.p1Win();
        tenise.p1Win();

        // WHEN
        std::string score = tenise.getScore();
        
        // THEN
        ASSERT_EQ(score, "Thirty Love");
    }

    TEST(TeniseTest, testScore_3_0) {
        // GIVEN
        TeniseScore tenise = TeniseScore();
        tenise.p1Win();
        tenise.p1Win();
        tenise.p1Win();

        // WHEN
        std::string score = tenise.getScore();
        
        // THEN
        ASSERT_EQ(score, "Fourty Love");
    }
}
