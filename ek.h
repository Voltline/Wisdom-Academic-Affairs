#ifndef EK_H
#define EK_H
#include "CourseSystem.h"
#include "stdAddition.h"
#include <vector>
#include <QString>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <QDebug>
using CourseSystem::Course;
using CourseSystem::multiCourseTime;
using CourseSystem::TeacherCourse;
using std::min;
using std::queue;
using std::unordered_map;
using std::vector;

namespace DataStructureAlgorithm
{
    class EK
    {
    public:
        EK(vector<Course> courses);
        int sov();
        void debug();
    private:
        vector<int> head, ver, nxt, edge, d, reverse;
        vector<int> v, incf, pre;
        vector<multiCourseTime> edge_tm, incf_tm;
        vector<Course> courses;
        vector<TeacherCourse> teacherCourses;
        unordered_map<QString, int> course_id;
        int tot = 1;
        int n, m, s, t;
        int maxn, maxm;
        int maxflow;
        const static int INF = 10000;
        void build();
        bool bfs();
        void update();
        void add(int x, int y, int z, int rev = 0, multiCourseTime tm = multiCourseTime());
    };
}

#endif EK_H
