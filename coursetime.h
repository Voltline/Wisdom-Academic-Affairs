#ifndef COURSESYSTEM_COURSETIME_H
#define COURSESYSTEM_COURSETIME_H


namespace CourseSystem {

class CourseTime
{
public:
    CourseTime()=default;
    CourseTime(int day, int start_class, int end_class);
    int day;
    int start_class, end_class;
};
bool judge_conflict(CourseTime &c1, CourseTime &c2)
{
    if(c1.day != c2.day) return false;
    if(c1.start_class > c2.end_class) return false;
    if(c2.start_class > c1.end_class) return false;
    return true;
}
} // namespace CourseSystem

#endif // COURSESYSTEM_COURSETIME_H
