#include "dinic.h"

namespace DataStructureAlgorithm
{
    Dinic::Dinic(vector<Course> courses)
    {
        this->courses = courses;
        n = m = 0;
        s = t = 0;
        tot = 1;
        for(auto x : courses)
        {
            n += x.get_teacherCourse().size();
        }

    }
}
