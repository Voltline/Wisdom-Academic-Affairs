#include "fenwick_tree.h"

namespace DataStructureAlgorithm
{
    Fenwick_Tree::Fenwick_Tree(int N) : vec{vector<int>(N)},
                                        n{N}
    {
    }

    void Fenwick_Tree::add(int x, int d)
    {
        for (; x <= n; x += (x & -x))
            vec[x] += d;
    }

    void Fenwick_Tree::add(int x, int y, int d)
    {
        add(x, d);
        add(y + 1, -d);
    }

    int Fenwick_Tree::query(int x)
    {
        int res = 0;
        for (; x; x -= (x & -x))
            res += vec[x];
        return res;
    }

    int Fenwick_Tree::query(int x, int y)
    {
        return query(y) - query(x - 1);
    }
}