#include "topsort.h"
namespace DataStructureAlgorithm
{
    TopSort::TopSort(vector<Course> courses, vector<double> max_credit, int limits)
    {
        // TODO:检查课程合法性，是否有课程的总共选课人数也不够limits，或者课程的credi大于max_credit
        for (auto course : courses)
        {
            int sum_limits = 0;
            if (course.get_must())
            {
                for (auto x : course.get_teacherCourse())
                {
                    sum_limits += x.get_limits();
                }
                if (sum_limits < limits)
                    throw AlgorithmException::TopsortException(("课程" + course.get_course_basic_ID().toStdString() + "的总课程人数不足").c_str());
            }
        }
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
        this->limits = limits;
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
        // for(auto x : max_credit)
        //     qDebug() << x;
        // return;
        int turn = 0;
        while (que.size())
        {
            ++turn;
            qDebug() << "begin" << turn;

            vector<Course> node_now;
            while (que.size())
            {
                int x = que.front() - 1;
                //                qDebug() << x << courses[x].get_course_name() << " " << courses[x].priority;
                que.pop_front();
                courses[x].priority++;
                node_now.push_back(courses[x]);
            }
            // 奇数学期优先Spring 偶数学期优先Fall 并且按优先级进行计算
            if (turn & 1)
                sort(node_now.begin(), node_now.end());
            else
                sort(node_now.begin(), node_now.end(), std::greater<Course>());
            for (auto it : node_now)
            {
                qDebug() << it.get_course_name() << " " << it.priority << " " << it.get_semester();
            }
            vector<int> vec;
            vector<int> to_del;
            for (auto course : node_now)
            {
                int x = id_map[course.get_course_basic_ID()];
                if (judge(vec, x, turn > max_credit.size() ? 100000 : max_credit[turn - 1]))
                {
                    vec.push_back(x);
                    // 选课后 直接而后继增加
                    for (auto it : course.get_nxtrequisites())
                    {
                        int y = id_map[it];
                        qDebug() << "nxt" << course.get_course_name() << " " << it << " " << y;
                        if (y)
                        {
                            courses[y - 1].priority += 2;
                            qDebug() << courses[y - 1].get_course_name() << " " << courses[y - 1].priority;
                        }
                    }
                }
                else
                {
                    to_del.push_back(x);
                }
            }
            ans.push_back(vec);
            for (auto it = to_del.rbegin(); it != to_del.rend(); ++it)
                que.push_front(*it);
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
            qDebug() << "end";
        }
    }
    bool TopSort::judge(vector<int> now, int new_course_id, double max_credit)
    {
        //        qDebug() << "judge" << now.size() << " " << new_course_id;
        vector<Course> vec;
        for (auto x : now)
            vec.push_back(courses[x - 1]);
        vec.push_back(courses[new_course_id - 1]);
        double credit = 0;
        for (auto x : vec)
            credit += x.get_credit();
        if (credit > max_credit)
            return false;
        //        qDebug() << "Dinic";
        auto now_limits = Dinic(vec).sov();
        //        qDebug() << "finish judge";
        return now_limits >= limits;
    }
}
