#include "gtest/gtest.h"
#include "../main/Budget.h"


using namespace date;
using namespace std;

namespace {

    TEST(BudgetTest, OneMonthBudget) {

        // GIVE, 2023.11, 30
        auto pRepo = new BudgetRepo();
        auto pService = new BudgetService(pRepo);
        
        Budget budget;
        budget.yearmonth = 2023_y / 11;
        budget.amout = 30;
        pRepo->addBudget(budget);

        // WHEN, 2023.11.1 - 2023.11.31
        auto from = 2023_y / 11 / 1;
        auto to = 2023_y / 11 / last;
        auto result = pService->query(from, to);

        // THEN, 30
        ASSERT_EQ(result, 30);
    }

    TEST(BudgetTest, HalfMonthBudget) {

        // GIVE, 2023.11, 30
        auto pRepo = new BudgetRepo();
        auto pService = new BudgetService(pRepo);
        auto budget = Budget();
        budget.amout = 30;
        budget.yearmonth = 2023_y / 11;
        pRepo->addBudget(budget);
        
        // WHEN, 2023.11.1 - 2023.11.15
        auto from = 2023_y / 11 / 1;
        auto to = 2023_y / 11 / 15;
        auto result = pService->query(from, to);

        // THEN, 15
        ASSERT_EQ(result, 15);
    }

    TEST(BudgetTest, NextMonthBudget) {

        // GIVE
        // 2023.10, 30
        // 2023.11, 30
        auto pRepo = new BudgetRepo();
        auto pService = new BudgetService(pRepo);

        Budget budget;
        budget.amout = 31;
        budget.yearmonth = 2023_y / 10;
        pRepo->addBudget(budget);

        budget.amout = 30;
        budget.yearmonth = 2023_y / 11;
        pRepo->addBudget(budget);
        
        // WHEN, 2023.10.1 - 2023.11.15
        auto from = 2023_y / 10 / 1;
        auto to = 2023_y / 11 / 15;
        auto days = (to.day() - from.day()).count() + 1;
        auto result = pService->query(from, to);

        // THEN, 46
        ASSERT_EQ(result, 46);
    }

    TEST(BudgetTest, PrevMonthBudget) {

        // GIVE
        // 2023.10, 30
        // 2023.11, 30
        auto pRepo = new BudgetRepo();
        auto pService = new BudgetService(pRepo);

        Budget budget;
        budget.yearmonth = 2023_y / 11;
        budget.amout = 30;
        pRepo->addBudget(budget);

        budget.amout = 31;
        budget.yearmonth = 2023_y / 10;
        pRepo->addBudget(budget);

        // WHEN, 2023.10.15 - 2023.11.30
        auto from = 2023_y / 10 / 15;
        auto to = 2023_y / 11 / 30;
        auto days = (to.day() - from.day()).count() + 1;
        auto result = pService->query(from, to);

        // THEN, 47
        ASSERT_EQ(result, 47);
    }

    TEST(BudgetTest, HalfHalfMonthBudget) {

        // GIVE
        // 2023.10, 30
        // 2023.11, 30
        auto pRepo = new BudgetRepo();
        auto pService = new BudgetService(pRepo);

        Budget budget;
        budget.yearmonth = 2023_y / 11;
        budget.amout = 30;
        pRepo->addBudget(budget);

        budget.amout = 31;
        budget.yearmonth = 2023_y / 10;
        pRepo->addBudget(budget);

        // WHEN, 2023.10.15 - 2023.11.30
        auto from = 2023_y / 10 / 15;
        auto to = 2023_y / 11 / 15;
        auto days = (to.day() - from.day()).count() + 1;
        auto result = pService->query(from, to);

        // THEN, 32
        ASSERT_EQ(result, 32);
    }

    TEST(BudgetTest, NoBudget) {

        // GIVE, no budget
        auto pRepo = new BudgetRepo();
        auto pService = new BudgetService(pRepo);
        
        // WHEN, 2023.11.1 - 2023.11.31
        auto from = 2023_y / 9 / 15;
        auto to = 2023_y / 11 / 20;
        auto result = pService->query(from, to);

        // THEN, 0
        ASSERT_EQ(result, 0);
    }
}