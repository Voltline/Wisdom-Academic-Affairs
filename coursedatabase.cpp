#include "coursedatabase.h"
#include <QDebug>

int weekday_map(const QString& w)
{
    if (w == "Mon") return 1;
    if (w == "Tue") return 2;
    if (w == "Wed") return 3;
    if (w == "Thu") return 4;
    if (w == "Fri") return 5;
    if (w == "Sat") return 6;
    if (w == "Sun") return 7;
    return 0;
}

QString toWeekdayString(int wd)
{
    switch (wd)
    {
    case 1: return "星期一";
    case 2: return "星期二";
    case 3: return "星期三";
    case 4: return "星期四";
    case 5: return "星期五";
    case 6: return "星期六";
    case 7: return "星期日";
    default: return "NULL";
    }
}

CourseDatabase::CourseDatabase()
    :db(DatabaseHandler()) {}

CourseDatabase::CourseDatabase(const CourseDatabase& cdb)
    :db(cdb.db) {}

CourseDatabase::CourseDatabase(CourseDatabase&& cdb) noexcept
    :db(std::move(cdb.db)) {}

vector<ClassInfo> CourseDatabase::get_all_class_info()
{
    vector<ClassInfo> ans_set;
    QString sql{ "call get_all_courses_ID()" };
    db.exec(sql);
    auto all_courses_ID{ db.get_select_results() };
    for (const auto& cs : all_courses_ID)
    {
        QString basic_ID = cs[0].toString(), sp_ID = cs[1].toString();
        sql = "call get_info_from_course(?, ?);";
        db.prepare(sql);
        db.add_bind_value(basic_ID);
        db.add_bind_value(sp_ID);
        db.exec();
        auto course_info{ db.get_select_results() };
        QString name{course_info[0][0].toString()},
            teacher{course_info[0][1].toString()},
            dept{course_info[0][2].toString()},
            seme{course_info[0][3].toString()},
            cate{course_info[0][4].toString()};
        double credit{course_info[0][5].toDouble()};
        int beg_w{course_info[0][6].toInt()}, last_w{course_info[0][7].toInt()}, lm{course_info[0][8].toInt()};
        vector<ClassPeriod> cp;
        sql = "call get_period_from_course(?, ?);";
        db.prepare(sql);
        db.add_bind_value(basic_ID);
        db.add_bind_value(sp_ID);
        db.exec();
        auto courses_period_info{ db.get_select_results() };
        for (const auto& ci : courses_period_info)
        {
            cp.push_back(ClassPeriod{
                          weekday_map(ci[0].toString()),
                          ci[1].toInt(), ci[2].toInt()});
        }

        vector<QString> prereq;
        db.prepare("call get_course_prereq(?);");
        db.bind_value(0, basic_ID);
        db.exec();
        auto pre{ db.get_select_results() };
        for (const auto& rec : pre) {
            prereq.push_back(rec[2].toString());
        }
        QString succeed{course_info[0][9].toString()};

        ans_set.push_back(ClassInfo{basic_ID, sp_ID, name, teacher,
                                    dept, seme, cate, cp, credit,
                                     beg_w, last_w, lm, prereq, succeed});
    }
    return ans_set;
}

vector<ClassInfo> CourseDatabase::get_one_class_info(const QString& course_basic_ID)
{
    vector<ClassInfo> ans_set;
    QString sql{ "call get_one_course_ID(?);" };
    db.prepare(sql);
    db.add_bind_value(course_basic_ID);
    db.exec();
    auto all_courses_ID{ db.get_select_results() };
    for (const auto& cs : all_courses_ID)
    {
        QString basic_ID = cs[0].toString(), sp_ID = cs[1].toString();
        sql = "call get_info_from_course(?, ?);";
        db.prepare(sql);
        db.add_bind_value(basic_ID);
        db.add_bind_value(sp_ID);
        db.exec();
        auto course_info{ db.get_select_results() };
        QString name{course_info[0][0].toString()},
            teacher{course_info[0][1].toString()},
            dept{course_info[0][2].toString()},
            seme{course_info[0][3].toString()},
            cate{course_info[0][4].toString()};
        double credit{course_info[0][5].toDouble()};
        int beg_w{course_info[0][6].toInt()}, last_w{course_info[0][7].toInt()}, lm{course_info[0][8].toInt()};
        vector<ClassPeriod> cp;
        sql = "call get_period_from_course(?, ?);";
        db.prepare(sql);
        db.add_bind_value(basic_ID);
        db.add_bind_value(sp_ID);
        db.exec();
        auto courses_period_info{ db.get_select_results() };
        for (const auto& ci : courses_period_info)
        {
            cp.push_back(ClassPeriod{
                          weekday_map(ci[0].toString()),
                          ci[1].toInt(), ci[2].toInt()});
        }

        vector<QString> prereq;
        db.prepare("call get_course_prereq(?);");
        db.bind_value(0, basic_ID);
        db.exec();
        auto pre{ db.get_select_results() };
        for (const auto& rec : pre) {
            prereq.push_back(rec[2].toString());
        }
        QString succeed{course_info[0][9].toString()};

        ans_set.push_back(ClassInfo{basic_ID, sp_ID, name, teacher,
                                    dept, seme, cate, cp, credit,
                                     beg_w, last_w, lm, prereq, succeed});
    }
    return ans_set;
}

vector<ClassInfo> CourseDatabase::get_class_from_dept(const QString& dept)
{
    vector<ClassInfo> ans_set;
    QString sql{ "call get_from_dept(?);" };
    db.prepare(sql);
    db.add_bind_value(dept);
    db.exec();
    auto all_courses_ID{ db.get_select_results() };
    for (const auto& cs : all_courses_ID)
    {
        QString basic_ID = cs[0].toString(), sp_ID = cs[1].toString();
        sql = "call get_info_from_course(?, ?);";
        db.prepare(sql);
        db.add_bind_value(basic_ID);
        db.add_bind_value(sp_ID);
        db.exec();
        auto course_info{ db.get_select_results() };
        QString name{course_info[0][0].toString()},
            teacher{course_info[0][1].toString()},
            dept{course_info[0][2].toString()},
            seme{course_info[0][3].toString()},
            cate{course_info[0][4].toString()};
        double credit{course_info[0][5].toDouble()};
        int beg_w{course_info[0][6].toInt()}, last_w{course_info[0][7].toInt()}, lm{course_info[0][8].toInt()};
        vector<ClassPeriod> cp;
        sql = "call get_period_from_course(?, ?);";
        db.prepare(sql);
        db.add_bind_value(basic_ID);
        db.add_bind_value(sp_ID);
        db.exec();
        auto courses_period_info{ db.get_select_results() };
        for (const auto& ci : courses_period_info)
        {
            cp.push_back(ClassPeriod{
                          weekday_map(ci[0].toString()),
                          ci[1].toInt(), ci[2].toInt()});
        }

        vector<QString> prereq;
        db.prepare("call get_course_prereq(?);");
        db.bind_value(0, basic_ID);
        db.exec();
        auto pre{ db.get_select_results() };
        for (const auto& rec : pre) {
            prereq.push_back(rec[2].toString());
        }

        QString succeed{course_info[0][9].toString()};

        ans_set.push_back(ClassInfo{basic_ID, sp_ID, name, teacher,
                                    dept, seme, cate, cp, credit,
                                     beg_w, last_w, lm, prereq, succeed});
    }
    return ans_set;
}

/*
void CourseDatabase::get_construct_data()
{
    auto ans_set{ get_all_class_info() };
    for (const auto& l : ans_set) {
        std::cout << l.course_basic_ID.toStdString() << "." << l.course_sp_ID.toStdString() << std::endl;
        std::cout << l.credit << std::endl;
        std::cout << weekday_map(l.day) << " " << l.beg << " " << l.beg + l.last - 1 << std::endl;
        bool isPrint{ false };
        for (const auto& ll : l.prereq) {
            std::cout << l.course_basic_ID.toStdString() << " " << ll.toStdString() << std::endl;
            isPrint = true;
        }
        if (!isPrint) std::cout << "--" << std::endl;
    }

}
*/
