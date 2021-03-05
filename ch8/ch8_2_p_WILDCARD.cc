#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

/*
    와일드카드 패턴과 함계 파일명의 집합이 주어질 때, 그중 패턴에 대응되는
    파일명들을 찾아내는 프로그램을 작성하라.
    *: 0개 이상, ?: 문자와 대응 --> 패턴을 *을 기준으로 쪼개야겠다.
*/
string pattern;
vector<string> f_names;
int cache[101][101];

void init(){
     cin >> pattern;
    int n; cin >> n;
    f_names = vector<string>(n);
    for(unsigned int i = 0; i < n; ++i){
        cin >> f_names[i];
    }
    memset(cache, -1, sizeof(cache));
}



bool matchMemoization(int w, int s, const string& f_name){
    int & ret = cache[w][s];
    if(ret != -1) return ret;
    while(s < pattern.size() && w < f_name.size() && (pattern[w] == '?' || pattern[w] == f_name[s])){
        ++w; ++s;
    }
    if(w == pattern.size()) return ret = (s == f_name.size());

    if(pattern[w] == '*')
        for(int skip = 0; skip + s <= f_name.size(); ++skip)
            if(matchMemoization(w+1, s+skip, f_name))
                return ret = true;
    
    return ret = false;
}

bool match(const string& w, const string& s){
    int pos = 0;
    while(pos < s.size() && pos < w.size() && (w[pos] == '?' || w[pos] == s[pos]))
        ++pos;
    if(pos == w.size())
        return pos == s.size();
    if(w[pos] == '*')
        for(int skip = 0; pos + skip <= s.size(); ++skip){
            if(match(w.substr(pos+1), s.substr(pos+skip)))
                return true;
        }
    return false;
}

void solve(){
    init();

    for(auto & elem: f_names)
        match(pattern, elem);   
}

int main(){
    int C; cin >> C;
    
    for(unsigned i = 0; i < C; ++i){
        solve();
    }
    
    return 0;
}