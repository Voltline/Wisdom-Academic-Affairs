#include "course.h"
namespace CourseSystem
{
    Course::Course(ClassInfo cInfo)
    {
        course_basic_ID = cInfo.course_basic_ID;
        course_name = cInfo.course_name;
        department = cInfo.department;
        semester = cInfo.semester;
        credit = cInfo.credit;
        category = cInfo.category;
        prereq = cInfo.prereq;
        push_teacherCourse(TeacherCourse(cInfo.course_sp_ID, cInfo.teacher, cInfo.limits, multiCourseTime(cInfo.times)));
    }

    Course &Course::push_teacherCourse(const TeacherCourse &teacherCourse)
    {
        teacherCourses.push_back(teacherCourse);
        return *this;
    }
}
