#include <iostream>
#include <cstring>

using namespace std;

int countCache[100][100];

int n, triangle[100][100];
int cache[100][100];

int path2(int y, int x){
    // base case
    if(y == n-1) return triangle[y][x];
    //memoization
    int& ret = cache[y][x];
    if(ret != -1) return ret;
    return ret = triangle[y][x] + std::max(path2(y+1, x),path2(y+1, x+1));
}

//(y,x)에서 시작해서 맨 아래줄까지 내려가는 경로 중 최대 경로의 개수를 반환한다.
int count(int y, int x)
{
    // base case:bottom line
    if(y == n - 1) return 1;
    // memoization
    int & ret = countCache[y][x];
    if(ret != -1) return ret;
    ret = 0;
    if(path2(y+1, x+1) >= path2(y+1, x)) ret += count(y+1, x+1);
    if(path2(y+1, x+1) <= path2(y+1, x)) ret += count(y+1, x);

    return ret;
}

void init()
{
    memset(countCache, -1, sizeof(countCache));
    memset(cache, -1, sizeof(cache));

    cin >> n;
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j <= i; ++j)
        {
            cin >> triangle[i][j];
        }
    }
}

int main()
{
    int C; cin >> C;
    for(int i = 0; i < C; ++i)
    {
        init();
        cout << count(0,0) << endl;
    }
    return 0;
}