#include "topsort.h"
namespace DataStructureAlgorithm
{
    TopSort::TopSort(vector<Course> courses, double max_credit)
    {
        n = courses.size();
        m = n * n;
        tot = 0;
        head = vector<int>(n + 1);
        ver = vector<int>(m + 1);
        nxt = vector<int>(n + 1);
        id_map = unordered_map<QString, int>();
        cnt = 0;
        this->max_credit = max_credit;
        for (auto course : courses)
        {

            if (id_map.find(course.get_course_basic_ID()) == id_map.end())
            {
                id_map[course.get_course_basic_ID()] = cnt++;
            }
        }
    }
}
