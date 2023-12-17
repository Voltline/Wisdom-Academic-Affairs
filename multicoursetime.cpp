#include "multicoursetime.h"
namespace CourseSystem
{
    multiCourseTime::multiCourseTime(const vector<ClassPeriod> &cps)
    {
        for (auto cp : cps)
        {
            push_back(CourseTime(cp));
        }
    }

    void multiCourseTime::push_back(const CourseTime &course_time)
    {
        course_times.push_back(course_time);
    }
    bool judge_conflict(const multiCourseTime &course_time_1, const multiCourseTime &course_time_2)
    {
        SegmentTree tree(MAX_CLASS_ID);
        for (const auto &time : course_time_1.course_times)
        {
            tree.change(1, 1, MAX_CLASS_ID, time.get_start_class_id(), time.get_end_class_id(), 1);
        }
        for (const auto &time : course_time_2.course_times)
        {
            if (tree.query(1, 1, MAX_CLASS_ID, time.get_start_class_id(), time.get_end_class_id()) != 0)
                return false;
        }
        return true;
    }
    bool operator^(const multiCourseTime &course_time_1, const multiCourseTime &course_time_2)
    {
        return judge_conflict(course_time_1, course_time_2);
    }
} // namespace CourseSystem
