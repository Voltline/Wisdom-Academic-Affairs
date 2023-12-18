#include "dinic.h"

namespace DataStructureAlgorithm
{
    Dinic::Dinic(vector<Course> courses)
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
            }
        }
        ++maxn;
        maxn = maxn * 2; // 拆点 所以2n
        t = n+2;
        maxm = maxn * maxn; // 按完全图 计算
        head = vector<int>(maxn);
        ver = vector<int>(maxm);
        edge = vector<int>(maxm);
        nxt = vector<int>(maxm);
        d = vector<int>(maxn);
    }
    int Dinic::sov()
    {
        if(courses.empty()) return 0;
        build();
        int flow = 0;
        while(bfs())
        {
            while(flow = dinic(s, INF))
                maxflow += flow;
        }
        return maxflow;
    }
    void Dinic::build()
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
                    teachercourse.get_limits());
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
                    add(course_id[from.get_course_basic_ID() + from_teachercourse.get_spid()] ^ 1,
                        course_id[to.get_course_basic_ID() + to_teachercourse.get_spid()],
                        INF);
                    add(course_id[to.get_course_basic_ID() + to_teachercourse.get_spid()],
                        course_id[from.get_course_basic_ID() + from_teachercourse.get_spid()] ^ 1,
                        0);
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
                    INF);
                add(course_id[from.get_course_basic_ID() + teachercourse.get_spid()],
                    s,
                    0);
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
    bool Dinic::bfs()
    {
        // 初始化距离数组
        d = vector<int>(maxn);
        // 将队列q中的元素全部弹出
        queue<int> q;
        // 将起点s压入队列q
        q.push(s);
        // 距离数组d中s的距离设置为1
        d[s] = 1;
        // 当队列q不为空时，循环
        while (q.size())
        {
            // 取出队列q中的第一个元素
            int x = q.front();
            // 将该元素弹出队列q
            q.pop();
            // 遍历x的边
            for (int i = head[x]; i; i = nxt[i])
            {
                // 如果该边的边权不为0，且距离数组d中该边的距离为0
                if (edge[i] && !d[ver[i]])
                {
                    // 将该边的终点压入队列q
                    q.push(ver[i]);
                    // 将该边的距离设置为x的距离加1
                    d[ver[i]] = d[x] + 1;
                    // 如果该边的终点是终点t，返回true
                    if (ver[i] == t)
                        return 1;
                }
            }
        }
        // 如果遍历完所有的边，没有找到终点t，返回false
        return 0;
    }
    int Dinic::dinic(int x, int flow)
    {
        // 如果已经到达汇点，则返回已经流过的水量
        if (x == t)
            return flow;
        // 剩余水量
        int rest = flow, k;
        // 遍历x的边
        for (int i = head[x]; i && rest; i = nxt[i])
        {
            // 如果该边的容量大于0，且源点为x，汇点为ver[i]
            if (edge[i] && d[ver[i]] == d[x] + 1)
            {
                // 调用dinic函数，计算从ver[i]到汇点的最大流
                k = dinic(ver[i], min(rest, edge[i]));
                // 如果最大流为0，则将源点d[ver[i]]置为0
                if (!k)
                    d[ver[i]] = 0;
                // 更新边的容量
                edge[i] -= k;
                edge[i ^ 1] += k;
                // 更新剩余水量
                rest -= k;
            }
        }
        // 返回已经流过的水量
        return flow - rest;
    }
    void Dinic::add(int x, int y, int z)
    {
        qDebug() << x <<  " " << y << " " << z;
        ver[++tot] = y;
        edge[tot] = z;
        nxt[tot] = head[x];
        head[x] = tot;
    }
}
