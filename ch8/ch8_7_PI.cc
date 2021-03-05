//원주율 외우기
#include <iostream>
#include <vector>
#include <string>

using namespace std;

string input;
vector<int> inputs;
vector<int> cache;
const int INF = 987'654'321;

// 3~5자리로 끊고 싶다.
bool isPat1(const vector<int>& piece){
    for(unsigned i = 0; i < piece.size() - 1; ++i){
        if(piece[i] != piece[i+1]) return false;
    }
    return true;
}
bool isPat2(const vector<int>& piece){
    int dif = piece[0] - piece[1];
    if(dif != 1 || dif != -1) return false;
    for(unsigned i = 1; i < piece.size() - 1; ++i){
        if(piece[i] - piece[i+1] != dif) return false;
    }
    return true;
}
bool isPat3(const vector<int>& piece){
    int num[] = {piece[0], piece[1]};
    for(unsigned i = 2; i < piece.size() - 1; ++i){
        if(piece[i] != num[i%2]) return false;
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
    if(begin >= inputs.size()) return 0;
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
}

void init(){
    cin >> input;
    inputs = vector<int>(input.size());
    for(unsigned int i = 0; i < input.size(); ++i){
        inputs[i] = input[i] - '0';
    }
    cache = vector<int>(input.size(), -1);
}

void solve(){
    init();
    cout << minScore(0) << endl;
}

int main(){
    int C; cin >> C;
    for(int i = 0; i < C; ++i){
        solve();
    }
    return 0;
}
