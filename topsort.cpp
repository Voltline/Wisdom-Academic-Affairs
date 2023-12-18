#include "topsort.h"
namespace DataStructureAlgorithm
{
    TopSort::TopSort(vector<Course> courses, double max_credit)
    {
        this->courses = courses;
        n = courses.size();
        m = n * n;
        tot = 0;
        head = vector<int>(n + 1);
        ver = vector<int>(m + 1);
        nxt = vector<int>(n + 1);
        in = vector<int>(n + 1);
        out = vector<int>(n + 1);
        ans = vector<vector<int>>();
        id_map = unordered_map<QString, int>();
        cnt = 0;
        this->max_credit = max_credit;
        for (int i = 0; i < courses.size(); ++i)
        {
            auto &course = courses[i];
            if (id_map.find(course.get_course_basic_ID()) == id_map.end())
            {
                id_map[course.get_course_basic_ID()] = i + 1;
            }
        }
    }
    vector<vector<Course>> TopSort::sov()
    {
        vector<vector<Course>> res;
        build();
        topsort();
        for (auto line : ans)
        {
            vector<Course> temp;
            for (auto course_id : line)
            {
                temp.push_back(courses[course_id - 1]);
            }
            res.push_back(temp);
        }
        return res;
    }
    void TopSort::build()
    {
        for (auto course : courses)
        {
            for (auto pre : course.get_prerequisites())
            {
                int x = id_map[course.get_course_basic_ID()];
                int y = id_map[pre];
                if (x == y)
                    continue;
                if (y == 0)
                    continue;
                add(y, x); // 添加y-x的有向边
            }
        }
    }
    void TopSort::topsort()
    {
        deque<int> que;
        for (int i = 1; i <= n; ++i)
        {
            if (in[i] == 0)
                que.push_back(i);
        }
        int turn = 0;
        while (que.size())
        {
            ++turn;
            vector<int> vec;
            while (que.size())
            {
                vec.push_back(que.front());
                que.pop_front();
            }
            // sort(vec.begin(), vec.end(), cmp_out); // 目前先按照最少影响去拿
            ans.push_back(vec);
            for (int x : vec)
            {
                for (int i = head[x]; i; i = nxt[i])
                {
                    int y = ver[i];
                    --in[y];
                    if (in[y] == 0)
                    {
                        que.push_back(y);
                    }
                }
            }
        }
    }
}
