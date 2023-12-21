#include "ek.h"

namespace DataStructureAlgorithm
{
    EK::EK(vector<Course> courses)
    {
        this->courses = courses;
        n = 0;
        m = 0;
        s = 1;
        maxn = 1;
        maxm = 0;
        tot = 1;
        for (auto course : courses)
        {
            maxn += course.get_teacherCourse().size();
            for (auto teachercourse : course.get_teacherCourse())
            {
                course_id[course.get_course_basic_ID() + teachercourse.get_spid()] = (n += 2);
                teacherCourses.push_back(teachercourse);
            }
        }
        ++maxn;
        maxn = maxn * 2; // 拆点 所以2n
        t = n + 2;
        maxm = maxn * maxn; // 按完全图 计算
        head = vector<int>(maxn);
        v = vector<int>(maxn);
        incf = vector<int>(maxn);
        pre = vector<int>(maxn);
        ver = vector<int>(maxm);
        reverse = vector<int>(maxm);
        edge = vector<int>(maxm);
        nxt = vector<int>(maxm);
        edge_tm =vector<multiCourseTime>(maxm);
        incf_tm =vector<multiCourseTime>(maxm);
        d = vector<int>(maxn);
    }
    int EK::sov()
    {
        if (courses.empty())
            return 0;
        build();
        while (bfs())
        {
            update();
        }
        return maxflow;
    }

    void EK::debug()
    {
        for(auto [x,y] : course_id)
        {
            qDebug() << x << " " << y;
        }
    }
    void EK::build()
    {
        // s是源点 是1 t是汇点 是maxn
        // 每个课程拆点 边权选课上限
        // 每个课程向后续课程练无限边
        //

        // 添加自己的边
        for (int i = 0; i < courses.size(); ++i)
        {
            auto from = courses[i];
            for (auto teachercourse : from.get_teacherCourse())
            {
                add(course_id[from.get_course_basic_ID() + teachercourse.get_spid()],
                    course_id[from.get_course_basic_ID() + teachercourse.get_spid()] ^ 1,
                    courses[i].get_must() ? teachercourse.get_limits() : INF);
                add(course_id[from.get_course_basic_ID() + teachercourse.get_spid()] ^ 1,
                    course_id[from.get_course_basic_ID() + teachercourse.get_spid()],
                    0);
            }
        }
        // 添加无限边
        for (int i = 1; i < courses.size(); ++i)
        {
            auto from = courses[i - 1], to = courses[i];
            for (auto from_teachercourse : from.get_teacherCourse())
            {
                for (auto to_teachercourse : to.get_teacherCourse())
                {
                    if(!(from_teachercourse.get_times() ^ to_teachercourse.get_times())) continue;
                    add(course_id[from.get_course_basic_ID() + from_teachercourse.get_spid()] ^ 1,
                        course_id[to.get_course_basic_ID() + to_teachercourse.get_spid()],
                        INF,
                        1,
                        to_teachercourse.get_times());
                    add(course_id[to.get_course_basic_ID() + to_teachercourse.get_spid()],
                        course_id[from.get_course_basic_ID() + from_teachercourse.get_spid()] ^ 1,
                        0,
                        1,
                        ~to_teachercourse.get_times());
                }
            }
        }
        // 添加源点的边
        for (int i = 0; i < 1; ++i)
        {
            auto from = courses[i];
            for (auto teachercourse : from.get_teacherCourse())
            {
                add(s,
                    course_id[from.get_course_basic_ID() + teachercourse.get_spid()],
                    INF,
                    1,
                    teachercourse.get_times());
                add(course_id[from.get_course_basic_ID() + teachercourse.get_spid()],
                    s,
                    0,
                    1,
                    ~teachercourse.get_times());
            }
        }
        // 添加汇点的边
        for (int i = courses.size() - 1; i < courses.size(); ++i)
        {
            auto to = courses[i];
            for (auto teachercourse : to.get_teacherCourse())
            {
                add(course_id[to.get_course_basic_ID() + teachercourse.get_spid()] ^ 1,
                    t,
                    INF);
                add(t,
                    course_id[to.get_course_basic_ID() + teachercourse.get_spid()] ^ 1,
                    0);
            }
        }
    }
    bool EK::bfs()
    {
//        qDebug() << "bfs begin" << endl;
        v = vector<int>(maxn, 0);
        queue<std::pair<int,multiCourseTime> > q;
        // 将起点s压入队列q
        q.push({s, multiCourseTime()});
        v[s] = 1;
        incf[s] = INF;
        incf_tm[s] = multiCourseTime();
        // 当队列q不为空时，循环
        while (q.size())
        {
            // 取出队列q中的第一个元素
            int x = q.front().first;
            auto xtm = q.front().second;
            // 将该元素弹出队列q
            q.pop();
            // 遍历x的边
            for (int i = head[x]; i; i = nxt[i])
            {
                bool judge = 1;
                int y = ver[i];
                multiCourseTime ytm = edge_tm[i];
//                judge = xtm ^ ytm;
                // 如果该边的边权不为0
                if (edge[i] && !v[y] && judge)
                {

                    incf[y] = std::min(incf[x], edge[i]);
                    incf_tm[y] = xtm + ytm;
                    pre[y] = i;
                    // 将该边的终点压入队列q
//                    qDebug() << "add" << x << " " << ver[i];
                    (xtm + ytm).debug();
                    q.push({ver[i], xtm + ytm});
                    v[y] = 1;
                    if (ver[i] == t)
                        return 1;
                }
            }
        }
//        qDebug() << "bfs end" << endl;
        // 如果遍历完所有的边，没有找到终点t，返回false
        return 0;
    }

    void EK::update()
    {
        int x = t;
//        qDebug() << "update";
        while(x != s)
        {
//            qDebug() << x;
            int i = pre[x];
            edge[i] -= incf[t];
            edge[i^1] += incf[t];
            edge_tm[i] = edge_tm[i] - incf_tm[t];
            edge_tm[i^1] = edge_tm[i] + incf_tm[t];
            x = ver[i^1];
        }
        maxflow += incf[t];
    }
    void EK::add(int x, int y, int z, int rev, multiCourseTime tm)
    {
//        qDebug() << x <<  " " << y << " " << z;
        ver[++tot] = y;
        edge[tot] = z;
        nxt[tot] = head[x];
        reverse[tot] = rev;
        edge_tm[tot] = tm;
        head[x] = tot;
    }
}
