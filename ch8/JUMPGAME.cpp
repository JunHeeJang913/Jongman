#include <iostream>
#include <cstring>

int n , board[100][100];
int cache[100][100];

using namespace std;

//brute Force way;
bool jump(int y, int x){
    //base case: out of range
    if(n <= y || n <= x) return false;
    //base case: success
    if(y == n-1 && x == n-1) return true;

    int jumpSize = board[y][x];
    return jump(y+jumpSize,x) || jump(y,x + jumpSize);
}

int jump2(int y, int x){
    //base case: out of range
    if(n <= y || n <= x) return false;
    //base case: success
    if(y == n-1 && x == n-1) return true;
    
    //memoization
    int& ret = cache[y][x];
    if(ret != -1) return ret;

    int jumpSize = board[y][x];
    return ret = (jump2(y+jumpSize, x) || jump2(y, x+jumpSize));
}

int main(void){
    int C;
    cin>>C;
    for(int i=0; i < C; ++i){
        cin>>n;
        for(int j = 0; j < n; ++j){
            for(int k = 0; k < n; ++k){
                cin >> board[j][k];
            }
        }
        memset(cache, -1, sizeof(cache));
        if(jump2(0,0) == 0) cout<<"NO"<<endl;
        else cout<< "YES" <<endl;
    }
}