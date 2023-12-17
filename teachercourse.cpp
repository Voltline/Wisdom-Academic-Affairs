#include "teachercourse.h"
namespace CourseSystem
{
    TeacherCourse::TeacherCourse(QString spid, QString teacher, int limits, multiCourseTime times)
    {
        this->spid = spid;
        this->teacher = teacher;
        this->limits = limits;
        this->times = new multiCourseTime;
        *(this->times) = times;
    }
    multiCourseTime &TeacherCourse::get_times()
    {
        return *times;
    }
}
