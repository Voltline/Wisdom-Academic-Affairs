#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e4 + 10;
const int MAXM = 3e5 + 10;
const int INF = LONG_LONG_MAX;
int head[MAXN], ver[MAXM], nxt[MAXM], edge[MAXM], d[MAXM];
int n, m, s, t, tot = 1, maxflow;
queue<int> q;

void add(const int &x, const int &y, const int &z)
{
    ver[++tot] = y;
    edge[tot] = z;
    nxt[tot] = head[x];
    head[x] = tot;
}
bool bfs()
{
    // 初始化距离数组
    memset(d, 0, sizeof(d));
    // 将队列中的元素全部弹出
    while (q.size())
        q.pop();
    // 将起点加入队列
    q.push(s);
    // 距离数组中起点的位置置为1
    d[s] = 1;
    // 当队列不为空时
    while (q.size())
    {
        // 取出队列中的第一个元素
        int x = q.front();
        // 将该元素弹出队列
        q.pop();
        // 遍历该元素的所有出边
        for (int i = head[x]; i; i = nxt[i])
        {
            // 如果该边存在，并且距离数组中该顶点的位置为0
            if (edge[i] && !d[ver[i]])
            {
                // 将该顶点加入队列
                q.push(ver[i]);
                // 将该顶点的位置置为该元素的位置加1
                d[ver[i]] = d[x] + 1;
                // 如果该顶点为终点，返回true
                if (ver[i] == t)
                    return 1;
            }
        }
    }
    // 如果遍历完所有的边，没有找到终点，返回false
    return 0;
}

int dinic(int x, int flow)
{
    // 如果已经到达汇点，则返回已经流过的水量
    if (x == t)
        return flow;
    // 剩余水量
    int rest = flow, k;
    // 遍历x的边
    for (int i = head[x]; i && rest; i = nxt[i])
    {
        // 如果该边的容量大于0，且该边的深度为x的深度加1
        if (edge[i] && d[ver[i]] == d[x] + 1)
        {
            // 递归调用dinic函数，获取从该边流过的水量
            k = dinic(ver[i], min(rest, edge[i]));
            // 如果从该边流过的水量为0，则将该边的深度设为0
            if (!k)
                d[ver[i]] = 0;
            // 更新该边的容量
            edge[i] -= k;
            edge[i ^ 1] += k;
            // 更新剩余水量
            rest -= k;
        }
    }
    // 返回已经流过的水量
    return flow - rest;
}
void luogu()
{
}

signed main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    cin >> n >> m;
    cin >> s >> t;
    tot = 1;
    for (int i = 1; i <= m; i++)
    {
        int x, y, c;
        cin >> x >> y >> c;
        add(x, y, c);
        add(y, x, 0);
    }
    int flow = 0;
    while (bfs())
    {
        while (flow = dinic(s, INF))
            maxflow += flow;
    }
    cout << maxflow << endl;
    cout << maxflow << endl;
}