#ifndef COURSESYSTEM_MULTICOURSETIME_H
#define COURSESYSTEM_MULTICOURSETIME_H
#include "fenwick_tree.h"
#include <QVector>
#include "coursetime.h"
namespace CourseSystem {

class multiCourseTime
{
public:
    multiCourseTime()=default;
private:
    QVector<CourseTime> course_times;
};
bool judge_conflict(const multiCourseTime &course_time_1, const multiCourseTime &course_time_2);
} // namespace CourseSystem

#endif // COURSESYSTEM_MULTICOURSETIME_H
