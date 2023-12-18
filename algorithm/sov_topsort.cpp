#include <bits/stdc++.h>
using namespace std;
namespace TOP
{
    const int MAXC = 14 * 7 + 10; // 一天14节 上午五节下午五节晚上四节 7天 依次给一个编号
    const int MAXN = 1e3 + 10;    // 课程数量
    const int MAXM = MAXN * MAXN; // 最差情况：建一个完全图
    const int MAXD = 100;         // 98次课
    int n, m;
    // 树状数组
    int tree[MAXD];
    void change(int x, int d)
    {
        for (x; x < MAXD; x += (x & -x))
            tree[x] += d;
    }
    int query(int x)
    {
        int res = 0;
        for (; x; x -= (x & -x))
            res += tree[x];
        return res;
    }
    void change(int l, int r, int d)
    {
        change(l, d);
        change(r + 1, -d);
    }
    int query(int l, int r)
    {
        return query(r) - query(l - 1);
    }
    // 建图
    int head[MAXN], ver[MAXM], nxt[MAXM], edge[MAXM], tot;
    int in[MAXN], out[MAXN];
    inline void add(const int &x, const int &y, const int &z = 0) // 加边
    {
        ++in[y];
        ++out[x];
        ver[++tot] = y;
        edge[tot] = z;
        nxt[tot] = head[x];
        head[x] = tot;
    }
    // 存储课程
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
        vector<pair<class_times, class_times>> times;
        int turn;
        double score;
        string name;
    } classes[MAXN];

    // topsort
    void topsort()
    {
        deque<int> que;
        for (int i = 1; i <= n; ++i)
        {
            if (in[i] == 0)
                que.push_back(i);
        }
        int turn = 0;
        while (que.size())
        {
            ++turn;
            vector<int> vec;
            while (que.size())
            {
                vec.push_back(que.front());
                que.pop_front();
            }
            sort(vec.begin(), vec.end(), [](int x, int y)
                 { return out[x] > out[y]; }); // 目前先按照最少影响去拿
            for (int x : vec)
            {
                bool isattak = 0;
                for (auto Tm : classes->times)
                {
                    if (query(Tm.first.to_id(), Tm.second.to_id()) >= 0) // 课程冲突
                    {
                        isattak = true;
                        break;
                    }
                }
                if (isattak)
                {
                    que.push_front(x);
                    continue;
                }
                else
                {
                    for (auto Tm : classes->times)
                    {
                        add(Tm.first.to_id(), Tm.second.to_id()); // 添加课程
                    }
                }
                classes[x].turn = turn;
                for (int i = head[x]; i; i = nxt[i])
                {
                    int y = ver[i];
                    --in[y];
                    if (in[y] == 0)
                    {
                        que.push_back(y);
                    }
                }
            }
        }
    }
    unordered_map<string, int> classid;
    void sov()
    {
        cin >> n >> m;
        for (int i = 1; i <= n; ++i)
        {
            cin >> classes[i].name >> classes[i].score;
            int k;
            cin >> k;
            for (int j = 1, l, r; j <= k; ++j)
            {
                int day;
                cin >> day >> l >> r;
                classes[i].times.push_back({{day, l}, {day, r}});
            }
            classid[classes[i].name] = i;
        }
        for (int i = 1; i <= m; ++i)
        {
            string x, y;
            cin >> x >> y;
            add(classid[x], classid[y]);
        }
        topsort();
        for (int i = 1; i <= n; ++i)
        {
            cerr << classes[i].name << " " << classes[i].score << " " << classes[i].turn << endl;
        }
    }
}
/*
    input
    n表示有n个课程 m表示有m条边
    之后3*n行，表示n组数据
    第一组是一个字符串 表示课程id
    第二行是一个double表示学分
    第三行一个k表示上课时间数 之后k个3元组 表示每个课的上课时间段
    之后m行 每行一个pair表示一条边


    output
    8行 每行输出一个k，之后k个数表示课程id
*/
int main()
{
    int n, m;
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    TOP::sov();
}
