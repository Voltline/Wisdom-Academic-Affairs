#include "coursetime.h"

namespace CourseSystem {

CourseTime::CourseTime(int day, int start_class, int end_class)
{
    this->day = day;
    this->start_class = start_class;
    this->end_class = end_class;
}
bool judge_conflict(CourseTime &c1, CourseTime &c2);
} // namespace CourseSystem
