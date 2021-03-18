#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;

// 확률
/*
    m 일 동안 n 미터인 우물
    비 올 확률 : 1/2
    비 오면 -> 2m
    비 안오면 -> 1m
    m일 안에 달팽이가 우물 끝까지 올라갈 확률은?
    (1, 1)
    (1, 2)
    (2, 1)
    (2, 2) 만약 4m였다면 2일 동안 1/4확률
    합이 n 이상인 경우 / 전체 경우(2^m)
*/

const int MAX = 1000;

int n, m;
double cache[MAX][2*MAX+1];

// 경우의 수 접근
/*
int climb(int day, int height)
{
    if(day == m) return height >= n? 1: 0;
    int & ret = cache[day][height];
    if(ret != -1) return ret;
    return ret = climb(day + 1, height + 1) + climb(day + 1, height + 2);
}*/

double climb2(int day, int height)
{
    if(day == m) return height >= n? 1: 0;
    double & ret = cache[day][height];
    if(ret != -1.0 ) return ret;
    return ret = 0.25*climb2(day + 1, height + 1) + 0.75*climb2(day + 1, height + 2);
}

int main()
{
    int C; cin >> C;
    for(int i = 0; i < C; ++i)
    {
        cin >> n >> m;
        for(int y = 0; y < m; ++y)
            for(int x = 0; x < 2*m +1; ++x)
                cache[y][x] = -1.0;
        cout.precision(11);
        cout << climb2(0, 0) << endl;
    }
    return 0;
}