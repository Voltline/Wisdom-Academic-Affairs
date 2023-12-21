#include "multicoursetime.h"
namespace CourseSystem
{
    multiCourseTime::multiCourseTime(const vector<ClassPeriod> &cps)
    {
        for (auto cp : cps)
        {
            push_back(CourseTime(cp));
        }
    }

    void multiCourseTime::push_back(const CourseTime &course_time)
    {
        course_times.push_back(course_time);
    }

    void multiCourseTime::erase(const CourseTime &course_time)
    {
        auto it = course_times.begin();
        for(it; it != course_times.end(); ++it)
        {
            if((*it) == course_time)
                break;
        }
        if(it != course_times.end())
            course_times.erase(it);
    }

    void multiCourseTime::debug()
    {
        {
            for(auto tm : course_times)
                tm.debug();
        }
    }
    bool judge_conflict(const multiCourseTime &course_time_1, const multiCourseTime &course_time_2)
    {
        SegmentTree tree(MAX_CLASS_ID);
        for (const auto &time : course_time_1.course_times)
        {
            tree.change(1, 1, MAX_CLASS_ID, time.get_start_class_id(), time.get_end_class_id(), time.reverse);
        }
        for (const auto &time : course_time_2.course_times)
        {
            if (tree.query(1, 1, MAX_CLASS_ID, time.get_start_class_id(), time.get_end_class_id()) != 0)
                return false;
        }
        return true;
    }
    bool operator^(const multiCourseTime &course_time_1, const multiCourseTime &course_time_2)
    {
        return judge_conflict(course_time_1, course_time_2);
    }

    multiCourseTime operator+(const multiCourseTime &course_time_1, const multiCourseTime &course_time_2)
    {
        auto res = course_time_1;
        for(auto it : course_time_2.course_times)
        {
            bool find = 0;
            for(int i = 0; i < res.course_times.size(); ++i)
            {
                if(res.course_times[i] == it)
                {
                    find = 1;
                    res.course_times[i].reverse += it.reverse;
                }
            }
            if(!find)
            {
                res.push_back(it);
            }
        }
        return res;
    }

    multiCourseTime operator-(const multiCourseTime &course_time_1, const multiCourseTime &course_time_2)
    {
        auto res = course_time_1;
        for(auto it : course_time_2.course_times)
        {
            bool find = 0;
            for(int i = 0; i < res.course_times.size(); ++i)
            {
                if(res.course_times[i] == it)
                {
                    find = 1;
                    res.course_times[i].reverse -= it.reverse;
                }
            }
            if(!find)
            {
                auto tmp = it;
                tmp.reverse = -tmp.reverse;
                res.push_back(tmp);
            }
        }
        return res;
    }

    multiCourseTime operator~(const multiCourseTime &course_time)
    {
        auto res = course_time;
        for(auto& it : res.course_times)
        {
            it.reverse = -it.reverse;
        }
        return res;
    }

} // namespace CourseSystem
