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
    memset(d, 0, sizeof(d));
    while (q.size())
        q.pop();
    q.push(s);
    d[s] = 1;
    while (q.size())
    {
        int x = q.front();
        q.pop();
        for (int i = head[x]; i; i = nxt[i])
        {
            if (edge[i] && !d[ver[i]])
            {
                q.push(ver[i]);
                d[ver[i]] = d[x] + 1;
                if (ver[i] == t)
                    return 1;
            }
        }
    }
    return 0;
}

int dinic(int x, int flow)
{
    if (x == t)
        return flow;
    int rest = flow, k;
    for (int i = head[x]; i && rest; i = nxt[i])
    {
        if (edge[i] && d[ver[i]] == d[x] + 1)
        {
            k = dinic(ver[i], min(rest, edge[i]));
            if (!k)
                d[ver[i]] = 0;
            edge[i] -= k;
            edge[i ^ 1] += k;
            rest -= k;
        }
    }
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