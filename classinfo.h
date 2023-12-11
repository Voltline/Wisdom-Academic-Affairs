#pragma once
#include <iostream>
#include <QString>
#include <vector>
#include <QDebug>
using std::vector;

constexpr const char* weeks[]{"Monday", "Tuesday", "Wednesday","Thursday", "Friday", "Saturday", "Sunday"};

class ClassInfo
{
private:
    QString course_basic_ID;
    QString course_sp_ID;
    QString course_name;
    QString teacher;
    QString department;
    QString semester;
    QString category;
    QString day;
    double credit;
    int beg;
    int last;
    int beg_week;
    int last_week;
    vector<QString> prereq;
public:
    ClassInfo() = delete;
    ClassInfo(const QString& cid, const QString& cspid, const QString& cname, const QString& t,
              const QString& dept, const QString& seme, const QString& cate, const QString& w,
              double c, int b, int l, int bw, int lw, const vector<QString>& p)
        : course_basic_ID(cid), course_sp_ID(cspid), course_name(cname)
        , teacher(t), department(dept), semester(seme), category(cate)
        , day(w), credit(c), beg(b), last(l), beg_week(bw), last_week(lw), prereq(p) {}
    ClassInfo(const ClassInfo& cp)
        : course_basic_ID(cp.course_basic_ID), course_sp_ID(cp.course_sp_ID), course_name(cp.course_name)
        , teacher(cp.teacher), department(cp.department), semester(cp.semester), category(cp.category), day(cp.day)
        , credit(cp.credit), beg(cp.beg), last(cp.last), beg_week(cp.beg_week), last_week(cp.last_week), prereq(cp.prereq) {}
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
            << "\nDay: " << day
            << "\nPeriod: " << beg << "~" << beg + last - 1
            << "\nWeeks: " << beg_week << "~" << beg_week + last_week - 1
            << "\nPrereq:\n[";

        for (int i = 0; i < prereq.size(); i++) {
            qDebug() <<  prereq[i];
        }
        qDebug() << "]";
    }
};
