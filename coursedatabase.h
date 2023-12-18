#pragma once
#include "dbhandler.h"
#include "classinfo.h"
#include <vector>
using std::vector;

class CourseDatabase
{
private:
    DatabaseHandler db;
public:
    CourseDatabase();
    CourseDatabase(const CourseDatabase& cdb);
    CourseDatabase(CourseDatabase&& cdb) noexcept;
    ~CourseDatabase() = default;

    vector<ClassInfo> get_all_class_info();
    vector<ClassInfo> get_one_class_info(const QString& course_basic_ID);
    vector<ClassInfo> get_class_from_dept(const QString& dept);
    // void get_construct_data();
};
