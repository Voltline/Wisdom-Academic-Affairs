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
    ClassInfo get_one_class_info(const QString& course_basic_ID);
};
