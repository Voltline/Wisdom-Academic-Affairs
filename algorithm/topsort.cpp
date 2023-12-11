#include <bits/stdc++.h>
using namespace std;
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


Fenwick_Tree::Fenwick_Tree(int N):
    vec{vector<int>(N)},
    n{N}
{
}

void Fenwick_Tree::add(int x, int d)
{
    for(; x <= n; x += (x & -x))
        vec[x] += d;
}

void Fenwick_Tree::add(int x, int y, int d)
{
    add(x, d);
    add(y+1, -d);
}

int Fenwick_Tree::query(int x)
{
    int res = 0;
    for(; x; x -= (x & -x))
        res += vec[x];
    return res;
}

int Fenwick_Tree::query(int x, int y)
{
    return query(y) - query(x-1);
}

namespace TOP
{
const int MAXC = 14 * 7 + 10;//一天14节 上午五节下午五节晚上四节 7天 依次给一个编号
const int MAXN = 1e3+10;//课程数量
const int MAXM = MAXN * MAXN;//最差情况：建一个完全图
int head[MAXN], ver[MAXM], nxt[MAXM], edge[MAXM], tot;
int in[MAXN], out[MAXN];
int n;
inline void add(const int &x, const int &y, const int &z = 0)//加边
{
    ++in[y];++out[x];
    ver[++tot] = y;
    edge[tot] = z;
    nxt[tot] = head[x];
    head[x] = tot;
}
struct class_times //上课时间
{
    class_times() = default;
    class_times(int day_, int tm_):day{day_},tm(tm_){};
    int day;
    int tm;
    int to_id()
    {
        return (day-1) * 14 + tm;
    }
};
struct node
{
    class_times st, ed;
    int turn;
    int score;
}classes[MAXN];
}
int main()
{
    int x;
    cin >> x;
	cout << 1 << endl;
	return 0;
}
