#ifndef CPP_OTP_BUDGET_H
#define CPP_OTP_BUDGET_H
#include <iostream>
#include <vector>
#include <map>
#include "date.h"

using namespace date;
using namespace std;

struct Budget {
    year_month yearmonth;
    int amout;
};

class BudgetRepo {
public:
    BudgetRepo() {
        _budget.clear();
    }
    virtual std::vector<Budget> findAll() {
        return _budget;
    };
    virtual void addBudget(Budget budget) {
        _budget.push_back(budget);
    }
    std::vector<Budget> _budget;
};

class BudgetService {
public:
    BudgetService(BudgetRepo* budgetRepo) {
        _pBudgetRepo = budgetRepo;
    }

    void calcByMonthly() {
        auto budgetList = _pBudgetRepo -> findAll();
        for (auto it = budgetList.begin(); it < budgetList.end(); it++) {
            // day avg
            auto start = it->yearmonth / 1;
            auto end = it->yearmonth / last;
            auto days = (end.day() - start.day()).count() + 1;
            int budgetByDay = it->amout / days;
            // cout << "month budget: " << it->yearmonth << ", " << budgetByDay << endl;
            dayBudget.insert({it->yearmonth, budgetByDay});
        }
    }

    long query(date::year_month_day from, date::year_month_day to) {

        calcByMonthly();

        int total = 0;

        // cout << "From: " << from << ", To: " << to << endl;

        // for all loop
        // for (auto i = from; i <= to; i = sys_days{i} + days{1} ) {
        //     auto it = dayBudget.find(i.year()/i.month());
        //     // cout << it->second << endl;
        //     if (it != dayBudget.end()) total += it->second;
        // }

        auto fromYearMonth = from.year()/from.month();
        auto toYearMonth = to.year()/to.month();

        // loop pef month from to
        for (auto it = from; it <= to; it = it + months{1}) {

            int days = 0;

            auto currentYearMonth = it.year()/it.month();

            auto nextYearMonth = currentYearMonth + months{1};
            auto hasNextMonth = nextYearMonth <= toYearMonth ? true : false;

            auto prevYearMonth = currentYearMonth - months{1};
            auto hasPrevMonth = prevYearMonth >= fromYearMonth ? true : false;

            // cout << "======" << endl;
            // cout << "cur: " << currentYearMonth << " prev: " << prevYearMonth << " hasPrev: " << hasPrevMonth << endl;
            // cout << "cur: " << currentYearMonth << " next: " << nextYearMonth << " hasNext: " << hasNextMonth << endl;
            
            if (!hasNextMonth && !hasPrevMonth) {
                days = (to.day() - from.day()).count() + 1;
            }
            else if (hasNextMonth) {
                auto startDays = currentYearMonth/from.day();
                auto endDays = currentYearMonth/last;

                if (hasPrevMonth) {
                    startDays = currentYearMonth/1;
                }
                // cout << "start: " << startDays << " , end: " << endDays << endl;
                days = (endDays.day() - startDays.day()).count() + 1;
            }
            else if (hasPrevMonth) {
                auto startDays = currentYearMonth/1;
                auto endDays = currentYearMonth/to.day();

                if (hasNextMonth) {
                    endDays = currentYearMonth/last;
                }
                // cout << "start: " << startDays << " , end: " << endDays << endl;
                days = (endDays.day() - startDays.day()).count() + 1;
            }
            else {
                cout << "ERROR!!!! " << it << endl;
            }
            
            auto itt = dayBudget.find(it.year()/it.month());

            if (itt != dayBudget.end()) total += itt->second * days;

            // cout << it.year()/it.month() << ", days: " << days << ", budget:" << total << endl;
        }
        
        return total;
    }
private:
    BudgetRepo* _pBudgetRepo;
    std::map<year_month, int> dayBudget;
};

#endif //CPP_OTP_BUDGET_H
