#ifndef DINIC_H
#define DINIC_H
#include "CourseSystem.h"
#include "stdAddition.h"
#include <vector>
#include <QString>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <QDebug>
using CourseSystem::Course;
using std::min;
using std::queue;
using std::unordered_map;
using std::vector;

namespace DataStructureAlgorithm
{
    class Dinic
    {
    public:
        Dinic(vector<Course> courses);
        int sov();

    private:
        vector<int> head, ver, nxt, edge, d;
        vector<Course> courses;
        unordered_map<QString, int> course_id;
        int tot = 1;
        int n, m, s, t;
        int maxn, maxm;
        int maxflow;
        const static int INF = 10000;
        void build();
        bool bfs();
        int dinic(int x, int flow);
        void add(int x, int y, int z);
    };
}

#endif DINIC_H
