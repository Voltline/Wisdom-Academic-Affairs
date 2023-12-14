#ifndef COURSESYSTEM_MULTICOURSETIME_H
#define COURSESYSTEM_MULTICOURSETIME_H
#include "fenwick_tree.h"
#include <Qvector>
#include "coursetime.h"
namespace CourseSystem {

class multiCourseTime
{
public:
    multiCourseTime()=default;
private:
    Qvector<CourseTime> course_times;
    FenwickTree fenwick_tree;
};

} // namespace CourseSystem

#endif // COURSESYSTEM_MULTICOURSETIME_H
