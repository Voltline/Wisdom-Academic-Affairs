#include "trie.h"

Trie::Trie(size_t max_pre):
    MAX_PRE(max_pre)
{
    rt = new node(MAX_PRE);
}

void Trie::insert(const long long &value, const QString &s)
{
    node* p = rt;
    QString lowers = s.toLower();
    for(const auto& c : lowers)
    {
        p->push(value, s);
        ++(p->siz);

        if(p->son.find(c) == p->son.end())
        {
            p->son[c] = new node(MAX_PRE);
        }
        p = p->son[c];
    }
    p->push(value, s);
    ++(p->siz);
}

pair<int, vector<pair<QString, long long> > > Trie::find(const QString &prefix)
{
    node*p = rt;
    QString lowers = prefix.toLower();
    for(const auto& c : lowers)
    {
        if(p->son.find(c) == p->son.end())
            return {0, vector<pair<QString, long long>>()};
        p = p->son[c];
    }
    vector<pair<QString, long long>> res;
    for(const auto& item : p->pre)
        res.push_back({item.second, item.first});
    std::reverse(res.begin(), res.end());
    return {p->siz, res};
}

Trie::~Trie()
{
    delete rt;
}


void Trie::node::push(const long long &value, const QString &s)
{
    pre.insert({value, s});
    if(pre.size() > MAX_PRE)
    {
        pre.erase(pre.begin());
    }
}

Trie::node::~node()
{
    for(auto &item : son)
    {
        delete item.second;
        item.second = nullptr;
    }
}
