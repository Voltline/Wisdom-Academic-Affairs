#include<bits/stdc++.h>
#include<fenwick_tree.h>
using namespace std;
namespace TOP
{
constexpr int MAXC = 14 * 7 + 10;//一天14节 上午五节下午五节晚上四节 7天 依次给一个编号
constexpr int MAXN = 1e3+10;//课程数量
constexpr int MAXM = MAXN * MAXN;//最差情况：建一个完全图
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
void topsort()
{
    deque<int> que;
    for(int i = 1; i <= n; ++i)
    {
        if(in[i] == 0)
            que.push_back(i);
    }
    int turn = 0;
    while(que.size())
    {
        ++turn;
        Fenwick_Tree tree(MAXC);
        vector<int> vec;
        while(que.size())
        {
            vec.push_back(que.front());
            que.pop_front();
        }
        sort(vec.begin(), vec.end(),[](int x, int y){
            return out[x] > out[y];
        });//目前先按照最少影响去拿
        for(int x : vec)
        {
            if(tree.query(classes[x].st.to_id(), classes[x].ed.to_id()) >= 0)//课程冲突
            {
                que.push_front(x);
                continue;
            }
            tree.add(classes[x].st.to_id(), classes[x].ed.to_id());
            classes[x].turn = turn;
            for(int i = head[x]; i; i = nxt[i])
            {
                int y = ver[i];
                --in[y];
                if(in[y] == 0)
                {
                    que.push_back(y);
                }
            }
        }
    }
}
void sov()
{

}
}
