#pragma once
#include <iostream>
#include <QString>
#include <QDebug>
#include <vector>
using std::vector;

enum week
{
    Mon, Tue, Wed, Thu, Fri, Sat, Sun
};

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
    week day;
    double credit;
    int beg;
    int last;
    int beg_week;
    int last_week;
    vector<QString> prereq;
public:
    ClassInfo() = delete;
    ClassInfo(const QString& cid, const QString& cspid, const QString& cname, const QString& t,
              const QString& dept, const QString& seme, const QString& cate, const week& w,
              double c, int b, int l, int bw, int lw, const vector<QString>& p)
        : course_basic_ID(cid), course_sp_ID(cspid), course_name(cname)
        , teacher(t), department(dept), semester(seme), category(cate)
        , day(w), credit(c), beg(b), last(l), beg_week(bw), last_week(lw), prereq(p) {}
    ClassInfo(const ClassInfo& cp)
        : course_basic_ID(cp.course_basic_ID), course_sp_ID(cp.course_sp_ID), course_name(cp.course_name)
        , teacher(cp.teacher), department(cp.department), semester(cp.semester), category(cp.category), day(cp.day)
        , credit(cp.credit), beg(cp.beg), last(cp.last), beg_week(cp.beg_week), last_week(cp.last_week), prereq(cp.prereq) {}
    ~ClassInfo() = default;

    friend std::ostream& operator<<(std::ostream& out, const ClassInfo& cp)
    {
        out << "CourseID: " << cp.course_basic_ID.toStdString() 
            << "." << cp.course_sp_ID.toStdString()
            << "\nCourseName: " << cp.course_name.toStdString()
            << "\nTeacher: " << cp.teacher.toStdString()
            << "\nDepartment: " << cp.department.toStdString()
            << "\nSemester: " << cp.semester.toStdString()
            << "\nCategory: " << cp.category.toStdString()
            << "\nCredits: " << cp.credit
            << "\nDay: " << weeks[cp.day]
            << "\nPeriod:[";
        for (int i = 0; i < cp.last; i++)
        {
            out << "," + !i << cp.beg + i;
        }
        out << "]\nWeeks:[";
        for (int i = 0; i < cp.last_week; i++)
        {
            out << "," + !i << cp.beg_week + i;
        }
        out << "]\nPrereq:[";
        for (int i = 0; i < cp.prereq.size(); i++) {
            out << "," + !i << cp.prereq[i].toStdString();
        }
        out << "]\n";
        return out;
    }
};
