//원주율 외우기
#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

string input;
int cache[10002];
const int INF = 987654321;
/*
bool isPat1(const vector<int>& piece){
    for(unsigned i = 0; i < piece.size() - 1; ++i){
        if(piece[i] != piece[i+1]) return false;
    }
    return true;
}

bool isPat4(const vector<int>& piece){
    int dif = piece[0] - piece[1];
    for(unsigned i = 1; i < piece.size() - 1; ++i){
        if(piece[i] - piece[i+1] != dif) return false;
    }
    return true;
}

bool isPat2(const vector<int>& piece){
    int dif = piece[0] - piece[1];
    if(isPat4(piece) == true && (dif == 1 || dif == -1)) return true;
    return false;
}

bool isPat3(const vector<int>& piece){
    int num[] = {piece[0], piece[1]};
    for(unsigned i = 2; i < piece.size() - 1; ++i){
        if(piece[i] != num[i%2]) return false;
    }
    return true;
}


int difficulty(const vector<int>& piece){
    if(isPat1(piece)) return 1;
    if(isPat2(piece)) return 2;
    if(isPat3(piece)) return 4;
    if(isPat4(piece)) return 5;
    return 10;
}

// minScore = min(f(n-3)+difficulty(3), f(n-4)+difficulty(4), f(n-5)+difficulty(5));
// f = minScore
int minScore(int begin){
    // base case:
    if(begin == inputs.size()) return 0;
    // memoization
    int & ret = cache[begin];
    if(ret != -1) return ret;
    ret = INF;
    vector<int> piece = {inputs[begin], inputs[begin+1]};
    for(unsigned int i = 3; i <= 5; ++i){
        piece.push_back(inputs[begin + i - 1]);
        if(begin + i <= inputs.size())
            ret = min(ret, minScore(begin + i) + difficulty(piece));
    }
    return ret;
}*/

/*
//input[a,b] 구간의 난이도를 반환한다.
int classify(int a, int b)
{
    string sub = input.substr(a, b-a+1);
    // 첫글자만으로 이뤄진 문자열인가?
    if(sub == string(sub.size(), sub[0])) return 1;
    // 등차수열?(2점 또는 5점)
    bool progressive = true;
    int diff = sub[1] - sub[0];
    for(unsigned i = 0; i < sub.size()-1; ++i)
        if(sub[i+1] - sub[i] != diff)
            progressive = false;
    // 공차가 1 또는 -1
    if((diff == 1 || diff == -1)&&progressive == true) return 2;

    // alternative?
    bool alternating = true;
    for(unsigned i = 0; i < sub.size(); ++i)
        if(sub[i] != sub[i%2]) 
            alternating = false;
    
    if(alternating == true) return 4;
    if(progressive == true) return 5;
    return 10;
}

// 수열 input[begin ...] 을 외우는 방법 중 난이도의 최소 합을 반환한다.
int memorize(int begin)
{
    // base case: end of sequence
    if(begin == input.size()) return 0;
    // memoization
    int& ret = cache[begin];
    if(ret != -1) return ret;
    ret = INF;
    for(unsigned L = 3; L <= 5; ++L)
        if(begin + L <= input.size())
            ret = min(ret, memorize(begin+L) + classify(begin, begin + L - 1));
    return ret;
}*/

void init(){
    cin >> input;
    memset(cache, -1, sizeof(cache));
}

void solve(){
    init();
    cout << memorize(0) << endl;
}

int main(){
    int C; cin >> C;
    for(int i = 0; i < C; ++i){
        solve();
    }
    return 0;
}
