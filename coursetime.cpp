#include "coursetime.h"

namespace CourseSystem
{
    CourseTime::CourseTime(ClassPeriod cp)
    {
        this->day = cp.day;
        this->start_class = cp.beg;
        this->end_class = cp.beg + cp.last - 1;
        // qDebug() << cp.beg << " " << cp.last << endl;
        this->start_class_id = (day - 1) * MAX_CLASS_IN_DAY + start_class;
        this->end_class_id = (day - 1) * MAX_CLASS_IN_DAY + end_class;
    }

    CourseTime::CourseTime(int day, int start_class, int end_class)
    {
        this->day = day;
        this->start_class = start_class;
        this->end_class = end_class;
        this->start_class_id = (day - 1) * MAX_CLASS_IN_DAY + start_class;
        this->end_class_id = (day - 1) * MAX_CLASS_IN_DAY + end_class;
    }
    CourseTime::CourseTime(int time_id_1, int time_id_2)
    {
        day = time_id_1 / MAX_CLASS_IN_DAY + 1;
        start_class = time_id_1 % MAX_CLASS_IN_DAY;
        end_class = time_id_2 % MAX_CLASS_IN_DAY;
        start_class_id = time_id_1;
        end_class_id = time_id_2;
    }
    CourseTime::CourseTime(const CourseTime &course_time)
    {
        this->day = course_time.day;
        this->start_class = course_time.start_class;
        this->end_class = course_time.end_class;
        this->start_class_id = course_time.start_class_id;
        this->end_class_id = course_time.end_class_id;
    }
    CourseTime& CourseTime::operator=(const CourseTime &course_time)
    {
        this->day = course_time.day;
        this->start_class = course_time.start_class;
        this->end_class = course_time.end_class;
        this->start_class_id = course_time.start_class_id;
        this->end_class_id = course_time.end_class_id;
        return *this;
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
