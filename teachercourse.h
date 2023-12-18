#pragma once
#ifndef TEACHERCOURSE_H
#define TEACHERCOURSE_H
#include "CourseSystem.h"
#include <QString>
#include <QDebug>
namespace CourseSystem
{
    class multiCourseTime;
    // 某一个老师的某一个课程类，处理该课程的上课时间等信息
    class TeacherCourse
    {
    public:
        TeacherCourse() = default;
        TeacherCourse(QString spid, QString teacher, int limits, multiCourseTime times);
        ~TeacherCourse() = default;
        multiCourseTime &get_times();
        void debug();
    private:
        // 开课序号
        QString spid;
        // 教师
        QString teacher;
        // 选课上限
        int limits;
        // 上课时间
        multiCourseTime *times;
    };

}

#endif // TEACHERCOURSE_H
