#pragma once
#include <vector>
using std::vector;
namespace DataStructureAlgorithm
{
    class Fenwick_Tree
    {
    private:
        // 存储 树状数组 的数组
        vector<int> vec;
        // Fenwick Tree 的大小
        int n;

    public:
        // 构造函数，初始化大小为 n 的 树状数组
        Fenwick_Tree(int N = 100);
        // 向 树状数组 中添加一个元素，下标为 x，值为 d
        void add(int x, int d);
        // 向 树状数组 中添加一个区间，下标为 x，y，值为 d
        void add(int x, int y, int d);
        // 查询 树状数组 中下标为 x 的元素
        int query(int x);
        // 查询 树状数组 中下标为 x 和 y 的元素
        int query(int x, int y);
    };
}
