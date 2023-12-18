#ifndef DINIC_H
#define DINIC_H
#include "CourseSystem.h"
#include <vector>
using CourseSystem::Course;
using std::vector;
namespace DataStructureAlgorithm
{
    class Dinic
    {
    public:
        Dinic(vector<Course> courses);
        int sov();
    private:
        vector<int> head, vec, nxt, edge, d;
        vector<Course> courses;
        int tot = 1;
        int n, m, s, t;
        int maxflow;
        const static int INF = 0x3f3f3f3f;
        void build();
        void bfs();
        int dinic(int x, int flow);
    };
}

#endif DINIC_H
