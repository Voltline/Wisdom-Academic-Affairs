#include "coursetime.h"

namespace CourseSystem
{

    CourseTime::CourseTime(int day, int start_class, int end_class)
    {
        this->day = day;
        this->start_class = start_class;
        this->end_class = end_class;
        this->start_class_id = (day - 1) * MAX_CLASS_IN_DAY + start_class;
        this->end_class_id = (day - 1) * MAX_CLASS_IN_DAY + end_class;
    }
    const int &CourseTime::get_day() const
    {
        return day;
    }
    const int &CourseTime::get_start_class() const
    {
        return start_class;
    }
    const int &CourseTime::get_end_class() const
    {
        return end_class;
    }
    const int &CourseTime::get_start_class_id() const
    {
        return start_class_id;
    }
    const int &CourseTime::get_end_class_id() const
    {
        return end_class_id;
    }
    bool judge_conflict(CourseTime &c1, CourseTime &c2)
    {
        if (c1.day != c2.day)
            return false;
        if (c1.start_class > c2.end_class)
            return false;
        if (c2.start_class > c1.end_class)
            return false;
        return true;
    }
} // namespace CourseSystem
