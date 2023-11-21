#include "Birthday.h"

bool Birthday::IsBirthday(const unsigned int mm, const unsigned int dd) {
    return date::year_month_day().month() == date::month{mm} && date::year_month_day().day() == date::day{dd};
}
