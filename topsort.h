#ifndef TOPSORT_H
#define TOPSORT_H
#include <vector>
#include <unordered_map>
#include <QString>
#include <queue>
#include <string>
#include "AlgorithmException.h"
#include "stdAddition.h"
#include "dinic.h"
#include "course.h"
using CourseSystem::Course;
using std::deque;
using std::hash;
using std::unordered_map;
using std::vector;
namespace DataStructureAlgorithm
{
    class TopSort
    {
    public:
        TopSort(vector<Course>, vector<double> max_credit = {10, 10, 15, 15, 20, 20, 32, 32}, int limits = 120);
        bool cmp_out(int x, int y)
        {
            return out[x] > out[y];
        }
        vector<vector<Course>> sov(); // 直接调用返回答案
    private:
        vector<int> head, ver, nxt, in, out;
        unordered_map<QString, int> id_map;
        vector<Course> courses;
        vector<vector<int>> ans;
        int tot;
        int cnt;
        int n, m;
        vector<double> max_credit;
        int limits;
        void add(int x, int y)
        {
            ver[++tot] = y;
            ++in[y];
            ++out[x];
            nxt[tot] = head[x];
            head[x] = tot;
        }
        void build();   // TODO : 建图
        void topsort(); // TODO: topsort
        bool judge(vector<int>, int, double max_credit);
    };
}

#endif TOPSORT_H
