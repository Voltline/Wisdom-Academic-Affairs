#pragma once
#ifndef COURSESYSTEM_MULTICOURSETIME_H
#define COURSESYSTEM_MULTICOURSETIME_H
#include "fenwick_tree.h"
#include "coursetime.h"
#include <vector>
using std::vector;
namespace CourseSystem {
class CourseTime; // 前向声明
class multiCourseTime
{
public:
    multiCourseTime()=default;
    void push_back(const CourseTime &course_time);
    friend bool judge_conflict(const multiCourseTime &course_time_1, const multiCourseTime &course_time_2);
private:
    vector<CourseSystem::CourseTime> course_times;
};
bool judge_conflict(const multiCourseTime &course_time_1, const multiCourseTime &course_time_2);
} // namespace CourseSystem

#endif // COURSESYSTEM_MULTICOURSETIME_H
