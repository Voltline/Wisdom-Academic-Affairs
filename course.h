#pragma once
#ifndef COURSE_H
#define COURSE_H
#include "CourseSystem.h"
#include "classinfo.h"
#include "stdAddition.h"
#include <vector>
#include <QString>
#include <QDebug>
#include <unordered_map>
using std::vector;
namespace CourseSystem
{
    class TeacherCourse;
    class Course
    {
    public:
        Course() = default;
        Course(ClassInfo cInfo);
        Course(const Course &Course);
        Course &operator=(const Course &Course);
        // 插入一个教师上课信息
        Course &push_teacherCourse(const TeacherCourse &teacherCourse);
        Course &push_teacherCourse(ClassInfo cInfo);
        const QString &get_course_basic_ID() const { return course_basic_ID; }
        const QString &get_course_name() const { return course_name; }
        const QString &get_department() const { return department; }
        const QString &get_semester() const { return semester; }
        const QString &get_category() const { return category; }
        double get_credit() const { return credit; }
        const vector<TeacherCourse> &get_teacherCourse() const { return teacherCourses; }
        const vector<QString> get_prerequisites() const { return prereq; }
        const vector<QString> get_nxtrequisites() const { return nxtreq; }
        bool get_must() { return must_map[category]; }
        void debug();
        friend bool operator<(const Course &c1, const Course &c2);
        friend bool operator>(const Course &c1, const Course &c2);
        int priority;

    private:
        void init(ClassInfo cInfo);
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
        // 后继课程
        vector<QString> nxtreq;
        // 开课教师课程
        vector<TeacherCourse> teacherCourses;
        //必修目录
        std::unordered_map<QString, bool> must_map;
    };
}
#endif // COURSE_H
