#include <iostream>
#include <cstring>

using namespace std;

const int MOD = 10 * 1000 * 1000;
int cache[101][101];

// poly(n, first): n개의 정사각형, 맨 위 가로줄에 first개의
// 정사각형을 포함하는 폴리오미노의 수를 반환한다.
int poly(int n, int first)
{
    // base case: n == first
    if(n == first) return 1;

    // memoization
    int & ret = cache[n][first];
    if(ret != -1) return ret;

    ret = 0;

    for(int second = 1; second <= n - first; ++second)
    {
        int add = second + first - 1;
        add *= poly(n - first, second);
        add %= MOD;
        ret += add;
        ret %= MOD;
    }
    return ret;
}

int main()
{
    int c; cin >> c;
    for(unsigned i = 0; i < c; ++i)
    {
        int n; cin >> n;
        memset(cache, -1, sizeof(cache));
        int sum = 0;
        for(int j = 1; j <= n; ++j)
        {
            sum += poly(n, j);
            sum %= MOD;
        }
        cout << sum << endl;
    }
}