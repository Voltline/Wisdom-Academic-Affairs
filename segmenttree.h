#ifndef SEGMENTTREE_H
#define SEGMENTTREE_H
#include <vector>
using std::vector;
namespace DataStructureAlgorithm
{
    class SegmentTree
    {

    public:
        SegmentTree() = default;
        SegmentTree(int N);
        void build(int tr, int l, int r);
        void change(int tr, int l, int r, int L, int R, int d);
        int query(int tr, int l, int r, int L, int R);

    private:
        vector<int> lazy, tree;
        int n;
    };

}
#endif // SEGMENTTREE_H
