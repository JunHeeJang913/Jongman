#include <iostream>
#include <cstring>

using namespace std;

const int MOD = 1000000007;

// 어떤 사건이 일어날 경우의 수 = 전체 경우의 수 - 어떤 사건이 안 일어날 경우의 수

int n;

// 너비가 주어질 때, 전체 경우의 수 저장 배열
int cache[101];

// 타일링 할 수 있는 경우의 수
int tiling(int width)
{
    // base case: width <= 1
    if(width <= 1) return 1;

    //memoization
    int & ret = cache[width];
    if(ret != -1) return ret;
    return ret = (tiling(width-1) + tiling(width-2)) % MOD;
}

int asymTiling(int width){
    if(width % 2 == 1) return (tiling(width) - tiling(width/2) + MOD) % MOD;

    int ret = tiling(width);
    ret = (ret - tiling(width/2) + MOD) % MOD;
    ret = (ret - tiling(width/2-1) + MOD) % MOD;

    return ret;
}

int main()
{
    int C; cin >> C;
    // 어차피 경우의 수는 너비에 따라 일정하니까!
    memset(cache, -1, sizeof(cache));

    for(int i = 0; i < C; ++i)
    {
        cin >> n;  
        cout << asymTiling(n) << endl;
    }

    return 0;
}