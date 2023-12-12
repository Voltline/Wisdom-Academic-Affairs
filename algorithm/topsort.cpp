#include <bits/stdc++.h>
using namespace std;
namespace TOP
{
    const int MAXC = 14 * 7 + 10; // 一天14节 上午五节下午五节晚上四节 7天 依次给一个编号
    const int MAXN = 1e3 + 10;    // 课程数量
    const int MAXM = MAXN * MAXN; // 最差情况：建一个完全图
    
    int treep[MAXN];
    int head[MAXN], ver[MAXM], nxt[MAXM], edge[MAXM], tot;
    int in[MAXN], out[MAXN];
    int n;
    inline void add(const int &x, const int &y, const int &z = 0) // 加边
    {
        ++in[y];
        ++out[x];
        ver[++tot] = y;
        edge[tot] = z;
        nxt[tot] = head[x];
        head[x] = tot;
    }
    struct class_times // 上课时间
    {
        class_times() = default;
        class_times(int day_, int tm_) : day{day_}, tm(tm_){};
        int day;
        int tm;
        int to_id()
        {
            return (day - 1) * 14 + tm;
        }
    };
    struct node
    {
        class_times st, ed;
        int turn;
        int score;
    } classes[MAXN];
}
/*
    input
    课程名 课程
*/
int main()
{
    int x;
    cin >> x;
    cout << 1 << endl;
    return 0;
}
