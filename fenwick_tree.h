#ifndef FENWICK_TREE_H
#define FENWICK_TREE_H
#include <vector>
using std::vector;
class Fenwick_Tree
{
private:
    vector<int> vec;
    int n;
public:
    Fenwick_Tree(int N);
    void add(int x, int d);
    void add(int x, int y, int d);
    int query(int x);
    int query(int x, int y);
};

#endif // FENWICK_TREE_H
