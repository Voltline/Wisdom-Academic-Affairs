#ifndef COURSE_H
#define COURSE_H
#include "CourseSystem.h"
#include "classinfo.h"
#include <vector>
#include <QString>
using std::vector;
namespace CourseSystem
{
    class TeacherCourse;
    class Course
    {
    public:
        Course() = default;
        Course(ClassInfo cInfo);
        // 插入一个教师上课信息
        Course &push_teacherCourse(const TeacherCourse &teacherCourse);

    private:
        // 课程信息 eg COMS0031121009
        QString course_basic_ID;
        // 课程名
        QString course_name;
        // 部门
        QString department;
        // 学期
        QString semester;
        // 类别
        QString category;
        // 学分
        double credit;

        // 前序课程
        vector<QString> prereq;

        // 开课教师课程
        vector<TeacherCourse> teacherCourses;
    };
}
#endif // COURSE_H
