/*
Quantization : 더 넓은 범위를 갖는 값들을 작은 범위를 갖는 값들로 근사해 표현 자료를 손실압축하는 과정
1000 이하의 수들로 구성된 수열을 s가지의 자연수만을 사용하도록 양자화하려고 한다.
residual-squared sum 을 최소화하고 싶음. ..? 머신러닝..?!
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;
/*
int n, s;
int avg = 0;
vector <int> seq;

// 수열의 순서가 중요한가? X
// --> 정렬을 해버리자..?, 배열을 묶어버리면 좋을 것 같은데...
void init()
{
    cin >> n >> s;
    seq = vector<int>(n);
    for(int i = 0; i < n; ++i)
    {
        cin >> seq[i];
        avg += seq[i];
    }
    avg /= n;

    sort(seq.begin(), seq.end());    
}*/

/*
    quantize(A) = A에 속한 수를 양자화해서 얻을 수 있는 최소 제곱 오차의 합
    지금까지 사용한 수들의 집합 또한 입력으로 받아야한다.
    quantize(A, U)  = U가 지금까지 한 번 이상 사용한 숫자들의 집합일 때 A에 속한 수를 양자화해서 얻을 수 있는 ~

    답의 형태 제한하기.
    a < b인 두 수에 대해 각각 대응되는 a', b'에 대해서 a' <= b'임을 알 수 있다.
    --> 주어진 수열을 정렬하면, 같은 수로 양자화되는 수들은 항상 인접해있다.

    --> 주어진 수열을 정렬한 뒤, 인접한 숫자끼리 묶음으로 적절히 분할, 각 묶음을 한 숫자로 표현해서 오류를 최소화한다.

    --> 수열을 s개의 묶음으로 나누는 문제가 된다. : 매 재귀 호출 때마다 첫 묶음의 크기가 얼마일지를 결정하면 된다.
    첫 묶음의 크기를 x라고 한다면, 이제 나머지 n-x개의 숫자를 s-1개의 묶음으로 나누는데, 이 때, s-1묶음의 오류 합이 최소여야
    전체도 최소오류가 되기때문에, 최적 부분 구조 또한 성립한다는 것을 알 수 있다.

    from 번째 이후의 숫자들을 parts개의 묶음으로 묶을 때, 최소 오류 제곱 합을 반환하는 함수
    quantize(from, parts) = (size = 1 ~ n-from) min[minError(from, from + size - 1) + quantize(from + size, parts - 1)]
*/

const int INF = 987654321;
int n, parts;
int A[101], pSum[101], pSqSum[101];

// A 정렬, 부분합 계산
void precalc()
{
    sort(A, A+n);
    pSum[0] = A[0];
    pSqSum[0] = A[0] * A[0];
    for(unsigned i = 1; i < n; ++i)
    {
        pSum[i] = pSum[i-1] + A[i];
        pSqSum[i] = pSqSum[i-1] + A[i]*A[i];
    }
}

int minError(int lo, int hi)
{
    int sum = pSum[hi] - (lo == 0 ? 0 : pSum[lo - 1]);
    int sqSum = pSqSum[hi] - (lo == 0? 0: pSqSum[lo-1]);
    int m = floor(0.5 + (double)sum / (hi - lo + 1));

    int ret = sqSum - 2*m*sum + m*m*(hi - lo + 1);
    return ret;
}

int cache[101][11];
int quantize(int from, int parts)
{
    //base case: all done
    if(from == n) return 0;
    // base case 2: done the grouping but still remaining number
    if(parts == 0) return INF;

    int & ret = cache[from][parts];
    if(ret != -1) return ret;
    ret = INF;

    for(int partSize = 1; from + partSize <= n; ++partSize)
        ret = min(ret, minError(from, from+partSize - 1) + quantize(from + partSize, parts-1));

    return ret;
}

void init()
{
    cin >> n >> parts;
    for(int i = 0; i < n; ++i)
        cin >> A[i];
    precalc();
    memset(cache, -1, sizeof(cache));
}

void solve()
{
    init();
    cout << quantize(0, parts) << endl;
}

int main()
{
    int C; cin >> C;
    for(unsigned i = 0; i < C; ++i)
    {
        solve();
    }
    return 0;
}