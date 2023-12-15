#include "multicoursetime.h"
namespace CourseSystem
{
    void multiCourseTime::push_back(const CourseTime &course_time)
    {
        course_times.push_back(course_time);
    }
    bool judge_conflict(const multiCourseTime &course_time_1, const multiCourseTime &course_time_2)
    {
        Fenwick_Tree fenwick_tree;
        for (const auto &time : course_time_1.course_times)
        {
            fenwick_tree.add(time.get_start_class_id(), time.get_end_class_id(), 1);
        }
        for (const auto &time : course_time_2.course_times)
        {
            if (fenwick_tree.query(time.get_start_class_id(), time.get_end_class_id()) != 0)
                return false;
        }
        return true;
    }
} // namespace CourseSystem
