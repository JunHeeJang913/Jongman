// 예제: 타일링 방법의 수 세기 TILING2
// tiling(n) = tiling(n-1) +tiling(n-2)
#include <iostream>
#include <cstring>

using namespace std;

const int MOD = 1000000007;
int cache[101];

int tiling(int width)
{
    // base case: width <= 1
    if(width <= 1) return 1;

    //memoization
    int & ret = cache[width];
    if(ret != -1) return ret;
    return ret = (tiling(width-1) + tiling(width-2)) % MOD;
}

int main()
{
    int T; cin >> T;
    for(int i = 0; i < T; ++i)
    {
        memset(cache, -1, sizeof(cache));
        int n; cin >> n;
        cout << tiling(n) << endl;
    }
}