#ifndef TOPSORT_H
#define TOPSORT_H
#include <vector>
#include <unordered_map>
#include <QString>
#include "stdAddition.h"
#include "course.h"
using CourseSystem::Course;
using std::hash;
using std::unordered_map;
using std::vector;
namespace DataStructureAlgorithm
{
    class TopSort
    {
    public:
        TopSort(vector<Course>, double max_credit = 32);

    private:
        vector<int> head, ver, nxt;
        unordered_map<QString, int> id_map;
        int tot;
        int cnt;
        int n, m;
        double max_credit;
        void add(int x, int y)
        {
            ver[++tot] = x;
            nxt[tot] = head[x];
            head[x] = tot;
        }
        void build();   // TODO : 建图
        void topsort(); // TODO: topsort
        void get_and(); // 整理返回值
        void sov();     // 直接调用返回答案
    };
}

#endif TOPSORT_H
