#ifndef TRIE_H
#define TRIE_H
#include<QDebug>
#include<QString>
#include<QChar>
#include<QHash>
#include<string>
#include<unordered_map>
#include<set>
#include<vector>
using std::string;
using std::unordered_map;
using std::pair;
using std::set;
using std::vector;

//在std添加hash函数
namespace std {
    template<> struct hash<QChar> {
        size_t operator()(const QChar& key) const {
            return qHash(key);
        }
    };
}
class Trie
{
private:
    const size_t MAX_PRE;
    //自定义比较 按value从小到大 字典序从大到小排序 保证弹出的是value最小 字典序最大的
    struct custom_compare
    {
        bool operator()(const pair<long long,QString> &x,const pair<long long,QString> &y)
        {
            return x.first == y.first ?  x.second > y.second : x.first < y.first ;
        }
    };
    struct node
    {
        const size_t MAX_PRE;
        long long siz;
        set<pair<long long,QString>, custom_compare> pre;
        unordered_map<QChar, node*> son;
        void push(const long long& value,const QString& s);
        node(size_t max_pre) : MAX_PRE(max_pre),siz(0) {}
        ~node();
    };
    node* rt;
public:
    Trie(size_t max_pre=5);
    void insert(const long long& value,const QString &s);
    pair<int, vector<pair<QString, long long> > > find(const QString &prefix);
    ~Trie();
};

#endif // TRIE_H
