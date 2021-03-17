#include <iostream>
#include <vector>
#include <limits>
#include <cstring>

using namespace std;

// 입력이 32비트 부호 있는 정수의 모든 값을 가질 수 있으므로 임의최소치는 64비트 최소치여야한다.
const long long NEGINF = numeric_limits<long long>::min();
int n, m, A[100], B[100];
//
int cache[101][101];

// A[startA]와 B[startB]에서 시작하는 합친 증가 부분 수열의 최대 길이.
int jlis(int startA, int startB){
    //memoization
    int& ret = cache[startA + 1][startB + 1];   // input can be -1
    if(ret != -1) return ret;

    ret = 0;
    long long a = (startA == -1 ? NEGINF : A[startA]);
    long long b = (startB == -1 ? NEGINF : B[startB]);
    long long maxElem = max(a, b);

    //find next elem
    for(int nextA = startA + 1; nextA < n; ++nextA)
        if(maxElem < A[nextA])
            ret = max(ret, jlis(nextA, startB) + 1);
    for(int nextB = startB + 1; nextB < m; ++nextB)
        if(maxElem < B[nextB])
            ret = max(ret, jlis(startA, nextB) + 1);

    return ret;
}

void init()
{
    cin >> n >> m;
    for(int i = 0; i < n; ++i)
    {
        cin >> A[i];
    }
    for(int i = 0; i < m; ++i)
    {
        cin >> B[i];
    }
    memset(cache, -1, sizeof(cache));
}

int main(){
    int C; cin >> C;
    for(int i = 0; i < C; ++i)
    {
        init();
        cout << jlis(-1, -1) << endl;
    }
    return 0;
}