#include "segmenttree.h"
namespace DataStructureAlgorithm
{
#define ls (tr << 1)
#define rs (tr << 1 | 1)
    SegmentTree::SegmentTree(int N)
    {
        n = N;
        lazy = vector<int>(4 * (N + 1), 0);
        tree = vector<int>(4 * (N + 1), 0);
        build(1, 1, n);
    }

    void SegmentTree::build(int tr, int l, int r)
    {
        if (l == r)
        {
            tree[tr] = 0;
            return;
        }
        int mid = (l + r) / 2;
        build(ls, l, mid);
        build(rs, mid + 1, r);
        tree[tr] = tree[ls] + tree[rs];
    }

    void SegmentTree::change(int tr, int l, int r, int L, int R, int d)
    {
        if (l == L && r == R)
        {
            tree[tr] += d * (r - l + 1);
            lazy[tr] += d;
            return;
        }
        int mid = (l + r) >> 1;
        if (lazy[tr])
        {
            change(ls, l, mid, l, mid, lazy[tr]);
            change(rs, mid + 1, r, mid + 1, r, lazy[tr]);
            lazy[tr] = 0;
        }
        if (R <= mid)
            change(ls, l, mid, L, R, d);
        else if (L > mid)
            change(rs, mid + 1, r, L, R, d);
        else
        {
            change(ls, l, mid, L, mid, d);
            change(rs, mid + 1, r, mid + 1, R, d);
        }
        tree[tr] = tree[ls] + tree[rs];
        return;
    }
    int SegmentTree::query(int tr, int l, int r, int L, int R)
    {
        if (l == L && r == R)
        {
            return tree[tr];
        }
        int mid = (l + r) >> 1;
        if (lazy[tr])
        {
            change(ls, l, mid, l, mid, lazy[tr]);
            change(rs, mid + 1, r, mid + 1, r, lazy[tr]);
            lazy[tr] = 0;
        }
        if (R <= mid)
            return query(ls, l, mid, L, R);
        else if (L > mid)
            return query(rs, mid + 1, r, L, R);
        else
            return query(ls, l, mid, L, mid) + query(rs, mid + 1, r, mid + 1, R);
    }
#undef ls
#undef rs
}