#pragma once
#ifndef COURSESYSTEM_COURSETIME_H
#define COURSESYSTEM_COURSETIME_H
#include "CourseSystem.h"
namespace CourseSystem {

class CourseTime
{
public:
    CourseTime()=default;
    CourseTime(int day, int start_class, int end_class);
    CourseTime(int time_id_1, int time_id_2);
    CourseTime(const CourseTime &time);
    CourseTime &operator=(const CourseTime &time);
    const int &get_day() const;
    const int &get_start_class() const;
    const int &get_end_class() const;
    const int &get_start_class_id() const;
    const int &get_end_class_id() const;
    friend bool judge_conflict(CourseTime &c1, CourseTime &c2);
private:
    int day;
    int start_class, end_class;
    int start_class_id, end_class_id;
};
bool judge_conflict(CourseTime &c1, CourseTime &c2);
} // namespace CourseSystem

#endif // COURSESYSTEM_COURSETIME_H
