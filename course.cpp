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
        nxtreq = vector<QString>();
        if (!cInfo.succeed.isEmpty())
            nxtreq.push_back(cInfo.succeed);
        priority = 0;
        push_teacherCourse(TeacherCourse(cInfo.course_sp_ID, cInfo.teacher, cInfo.limits, multiCourseTime(cInfo.times)));
    }

    Course::Course(const Course &Course)
    {
        course_basic_ID = Course.course_basic_ID;
        course_name = Course.course_name;
        department = Course.department;
        semester = Course.semester;
        credit = Course.credit;
        category = Course.category;
        prereq = Course.prereq;
        nxtreq = vector<QString>();
        if (!Course.nxtreq.empty())
            nxtreq.push_back(Course.nxtreq[0]);
        priority = Course.priority;
        for (auto teacherCourse : Course.teacherCourses)
        {
            push_teacherCourse(teacherCourse);
        }
    }

    Course &Course::operator=(const Course &Course)
    {
        course_basic_ID = Course.course_basic_ID;
        course_name = Course.course_name;
        department = Course.department;
        semester = Course.semester;
        credit = Course.credit;
        category = Course.category;
        prereq = Course.prereq;
        nxtreq = Course.nxtreq;
        priority = Course.priority;
        // 老师课程
        for (auto teacherCourse : Course.teacherCourses)
        {
            push_teacherCourse(teacherCourse);
        }
        return *this;
    }

    Course &Course::push_teacherCourse(const TeacherCourse &teacherCourse)
    {
        teacherCourses.push_back(teacherCourse);
        return *this;
    }

    void Course::debug()
    {
        qDebug() << course_basic_ID << "\n"
                 << course_name << "\n"
                 << department << "\n"
                 << semester << "\n"
                 << category << "\n"
                 << credit;
        for (auto x : prereq)
            qDebug() << x << " ";
        for (auto x : teacherCourses)
            x.debug();
    }
    Course &Course::push_teacherCourse(ClassInfo cInfo)
    {
        if (course_basic_ID.isEmpty())
            init(cInfo);
        else if (course_basic_ID != cInfo.course_basic_ID)
            throw QString("insert wrong basic Class");
        TeacherCourse teacherCourse(cInfo.course_sp_ID, cInfo.teacher, cInfo.limits, multiCourseTime(cInfo.times));
        teacherCourses.push_back(teacherCourse);
        return *this;
    }
    void Course::init(ClassInfo cInfo)
    {
        course_basic_ID = cInfo.course_basic_ID;
        course_name = cInfo.course_name;
        department = cInfo.department;
        semester = cInfo.semester;
        credit = cInfo.credit;
        category = cInfo.category;
        prereq = cInfo.prereq;
        nxtreq = vector<QString>();
        if (!cInfo.succeed.isEmpty())
            nxtreq.push_back(cInfo.succeed);
    }
    bool operator<(const Course &c1, const Course &c2)
    {

        return c1.priority == c2.priority ? c1.semester < c2.semester : c1.priority > c2.priority;
    }
    bool operator>(const Course &c1, const Course &c2)
    {
        return c1.priority == c2.priority ? c1.semester > c2.semester : c1.priority > c2.priority;
    }
}
