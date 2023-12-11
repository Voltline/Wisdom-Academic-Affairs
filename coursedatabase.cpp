#include "coursedatabase.h"
#include <QDebug>

CourseDatabase::CourseDatabase()
    :db(DatabaseHandler()) {}

CourseDatabase::CourseDatabase(const CourseDatabase& cdb)
    :db(cdb.db) {}

CourseDatabase::CourseDatabase(CourseDatabase&& cdb) noexcept
    :db(std::move(cdb.db)) {}

vector<ClassInfo> CourseDatabase::get_all_class_info()
{
    vector<ClassInfo> ans_set;
    QString sql{ "select * from courses;" };
    db.exec(sql);
    QString basic_ID, sp_ID, name, teacher, dept, seme, cate, day;
    double credit;
    int beg_c, last_c, beg_w, last_w;
    auto ans{ db.get_select_results() };
    for (const auto& l : ans)
    {
        basic_ID = l[0].toString();
        sp_ID = l[1].toString();
        name = l[2].toString();
        teacher = l[3].toString();
        dept = l[4].toString();
        seme = l[5].toString();
        cate = l[6].toString();
        day = l[7].toString();
        credit = l[8].toDouble();
        beg_c = l[9].toInt();
        last_c = l[10].toInt();
        beg_w = l[11].toInt();
        last_w = l[12].toInt();
        vector<QString> prereq;
        db.prepare("call get_course_prereq(?);");
        db.bind_value(0, basic_ID);
        db.exec();
        auto pre{ db.get_select_results() };
        for (const auto& rec : pre) {
            prereq.push_back(rec[2].toString());
        }
        ans_set.push_back(ClassInfo{basic_ID, sp_ID, name, teacher,
                          dept, seme, cate, day, credit, beg_c,
                          last_c, beg_w, last_w, prereq});

    }
    return ans_set;
}
/*
ClassInfo CourseDatabase::get_one_class_info(const QString& course_basic_ID)
{
    return ClassInfo{}
}
*/
