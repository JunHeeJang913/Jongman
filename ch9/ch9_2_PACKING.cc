#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

int n_want; // #wanted
int w_carrier; // weight of carrier

vector<pair<string, pair<int, int> > > list;    // name volume needed

// 잔여 capacity, item넣은 수가 주어질 때, 절박도
int cache[1001][101]; // max_capacity, max_item

void init()
{
    list.clear();
    cin >> n_want >> w_carrier;
    list.reserve(n_want);
    for(int i = 0; i < n_want; ++i)
    {
        string name;
        int volume, needed;
        cin >> name >> volume >> needed;
        list.push_back(make_pair(name, make_pair(volume, needed)));        
    }
    memset(cache, -1, sizeof(cache));
}

int pack(int capacity, int item)
{
    // base case: 더 담을 것이 없거나, 용량 초과.(안 담으면 그 뿐)
    if(item == n_want) return 0;

    // memoization
    int & ret = cache[capacity][item];
    if(ret != -1) return ret;

    ret = pack(capacity, item + 1);

    const int volume_item = list[item].second.first;
    const int needed_item = list[item].second.second;
    if(capacity >= volume_item)
        ret = max(ret, pack(capacity - volume_item, item + 1) + needed_item);
}

// reconstruct
void reconstruct(int capacity, int item, vector<string>& picked)
{
    if(item == n_want) return;
    if(pack(capacity, item) == pack(capacity, item + 1))
        reconstruct(capacity, item + 1, picked);
    else
    {
        picked.push_back(list[item].first);
        const int volume_item = list[item].second.first;
        reconstruct(capacity - volume_item, item + 1, picked);    
    }
}

void result(vector<string> & picked)
{
    int max_needed = pack(w_carrier, 0);
    reconstruct(w_carrier, 0, picked);
    cout << max_needed << " " << picked.size() << endl;
    for(auto e : picked)
    {
        cout << e << '\n';
    }
}

int main()
{
    int C; cin >> C;
    for(int i = 0; i < C; ++i)
    {
        init();
        
        vector<string> picked;
        
        result(picked);
    }

    return 0;
}