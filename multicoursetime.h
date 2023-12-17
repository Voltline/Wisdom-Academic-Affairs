#pragma once
#ifndef COURSESYSTEM_MULTICOURSETIME_H
#define COURSESYSTEM_MULTICOURSETIME_H
#include "CourseSystem.h"
#include "segmenttree.h"
#include "coursetime.h"
#include "classinfo.h"
#include <vector>
using std::vector;
using DataStructureAlgorithm::SegmentTree;
namespace CourseSystem
{
    class CourseTime; // 前向声明
    // 课程时间类 处理某个课的多个课程时间
    class multiCourseTime
    {
    public:
        multiCourseTime() = default;
        multiCourseTime(const vector<ClassPeriod>&);
        void push_back(const CourseTime &course_time);
        friend bool judge_conflict(const multiCourseTime &course_time_1, const multiCourseTime &course_time_2);

    private:
        vector<CourseSystem::CourseTime> course_times; // 课时组
    };
    // 判断两个课的课时是否冲突
    bool judge_conflict(const multiCourseTime &course_time_1, const multiCourseTime &course_time_2);
    bool operator^(const multiCourseTime &course_time_1, const multiCourseTime &course_time_2);
} // namespace CourseSystem

#endif // COURSESYSTEM_MULTICOURSETIME_H
