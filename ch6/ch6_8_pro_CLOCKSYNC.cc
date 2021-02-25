#include <iostream>
#include <vector>
using namespace std;

const int INF = 987654321;
const int n_clock = 16;
int clocks[n_clock];
const int n_switches = 10;
const vector<vector<int> > switches({
    vector<int>({0,1,2}),
    vector<int>({3,7,9,11}),
    vector<int>({4, 10, 14, 15}),
    vector<int>({0, 4, 5, 6, 7}),
    vector<int>({6, 7, 8, 10, 12}),
    vector<int>({0, 2, 14, 15}),
    vector<int>({3, 14, 15}),
    vector<int>({4, 5, 7, 14, 15}),
    vector<int>({1, 2, 3, 4, 5}),
    vector<int>({3, 4, 5, 9, 13})
});

void init(){
    for(int i = 0; i < n_clock; ++i){
        cin >> clocks[i];
    }
}

bool areAligned(){
    for(auto elem : clocks){
        if(elem != 12) return false;
    }
    return true;
}

void push(int s_index){
    for(int i = 0; i < switches[s_index].size(); ++i){
        int clock = switches[s_index][i];
        clocks[clock] += 3;
        if(clocks[clock] == 15) clocks[clock] = 3;
    }
}

//s_index : index of switch to push
int sync(int s_index){
    //base case : pushed all switches
    if(s_index == n_switches) return areAligned() ? 0 : INF;
    //try to push switches for 3 times;
    int ret = INF;
    for(int cnt = 0; cnt < 4; ++cnt){
        ret = min(ret, cnt + sync(s_index + 1));
        push(s_index);      //note on the sequence of two sentence
    }
    //because we call the push() 4times, clock is same as the initial condition
    return ret;
}

void solve(){
    init();
    int n_click = sync(0);
    if(n_click >= INF) cout << -1 << endl;
    else cout << n_click << endl;
}

int main(void){
    int C; cin >> C;
    for(int i = 0; i < C; ++i){
        solve();
    }
    return 0;
}