#pragma once
#include <iostream>
#include <QString>
#include <vector>
#include <QDebug>
using std::vector;

class ClassPeriod
{
public:
    int day;
    int beg;
    int last;

public:
    bool operator==(const ClassPeriod &cp) const
    {
        return (day == cp.day) && (beg == cp.beg) && (last == cp.last);
    }
};

class ClassInfo
{
public:
    // 课程信息 eg COMS0031121009
    QString course_basic_ID;
    // 开课序号 eg 02
    QString course_sp_ID;
    // 课程名
    QString course_name;
    // 教师
    QString teacher;
    // 部门
    QString department;
    // 学期
    QString semester;
    // 类别
    QString category;
    vector<ClassPeriod> times;
    // 学分
    double credit;
    int beg_week;
    int last_week;
    // 选课上限
    int limits;
    // 前序课程
    vector<QString> prereq;

public:
    ClassInfo() = delete;
    ClassInfo(const QString &cid, const QString &cspid, const QString &cname, const QString &t,
              const QString &dept, const QString &seme, const QString &cate, const vector<ClassPeriod> &tms,
              double c, int bw, int lw, int lm, const vector<QString> &p)
        : course_basic_ID(cid), course_sp_ID(cspid), course_name(cname), teacher(t), department(dept), semester(seme), category(cate), times(tms), credit(c), beg_week(bw), last_week(lw), limits(lm), prereq(p) {}
    ClassInfo(const ClassInfo &cp)
        : course_basic_ID(cp.course_basic_ID), course_sp_ID(cp.course_sp_ID), course_name(cp.course_name), teacher(cp.teacher), department(cp.department), semester(cp.semester), category(cp.category), times(cp.times), credit(cp.credit), beg_week(cp.beg_week), last_week(cp.last_week), limits(cp.limits), prereq(cp.prereq) {}
    ~ClassInfo() = default;

    void display() const
    {
        qDebug() << "CourseID: " << course_basic_ID + "." + course_sp_ID
                 << "\nCourseName: " << course_name
                 << "\nTeacher: " << teacher
                 << "\nDepartment: " << department
                 << "\nSemester: " << semester
                 << "\nCategory: " << category
                 << "\nCredits: " << credit
                 << "\nWeeks: " << beg_week << " " << beg_week + last_week - 1
                 << "\nLimits: " << limits;

        for (const auto &cp : times)
        {
            qDebug() << cp.day << " " << cp.beg << " " << cp.beg + cp.last - 1;
        }
        qDebug() << "Prereq:\n[";

        for (int i = 0; i < prereq.size(); i++)
        {
            qDebug() << " " << prereq[i];
        }
        qDebug() << "]";
    }
};
