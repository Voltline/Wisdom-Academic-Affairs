#ifndef TOPSORT_H
#define TOPSORT_H
#include <vector>
#include <unordered_map>
#include <QString>
#include <queue>
#include "stdAddition.h"
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
        TopSort(vector<Course>, double max_credit = 32);
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
        double max_credit;
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
    };
}

#endif TOPSORT_H
