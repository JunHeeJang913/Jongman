#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int cache[101][101];
string W, S;

bool matchMemoized(int w, int s){
    int & ret = cache[w][s];
    if(ret != -1) return ret;
    while(s < S.size() && w < W.size() &&(W[w] == '?' || S[s] == W[w])){
        ++w; ++s;
    }
    if(w==W.size()) return ret = (s == S.size());
    if(W[w] == '*')
        for(int skip = 0; s+skip <= S.size(); ++skip)
            if(matchMemoized(w+1, s+skip))
                return ret = 1;
    return ret = 0;
}

bool match(const string & w, const string & s){
    int pos = 0;
    while(pos < s.size() && pos < w.size() && (w[pos] == '?' || w[pos]==s[pos])){
        ++pos;
    }

    if(pos == w.size())
        return pos == s.size();

    if(w[pos] == '*')
        for(int skip = 0; pos+skip <= s.size(); ++skip)
            if(match(w.substr(pos+1), s.substr(pos+skip)))
                return true;
    
    return false;
}

int main(void){
    int C;
    cin>>C;
    for(int i = 0; i < C; ++i){
        cin>>W;
        int N;
        cin >> N;
        vector<string> result;
        result.reserve(50);
        for(int j = 0; j < N;++j){
            cin >> S;
            memset(cache,-1, sizeof(cache));
            if(matchMemoized(0,0)==1)
                result.push_back(S);
        }
        sort(result.begin(), result.end());
        for(int j = 0; j < result.size(); ++j){
            cout<<result[j]<<endl;
        }
    }
}