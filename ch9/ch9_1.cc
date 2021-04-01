#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// 최적화 문제의 실제 답 계산하기

// 예제: 최대 증가 부분 수열 실제 출력

// int n, cache[100], S[100];
// int lis3(int start){
//     int& ret = cache[start + 1];
//     if(ret != -1) return ret;
//     //항상 S[start]는 존재하므로 최하 1의 길이, 이게 base case를 대체한다.
//     ret = 1;
//     for(int next = start + 1; next < n; ++next)
//         if(start ==  -1 || S[start] < S[next])
//             ret = max(ret, lis3(next) + 1);
//     return ret;
// }

// 우선적으로 생각할 수 있는 방법 --> lis3가 lis의 길이 대신 실제 배열을 반환하도록 하는 것.
// 직관적인 코드를 짤 수 있지만, 모든 부분 문제마다 최적해를 저장해야하니 느리고 메모리를 많이 차지함.
// 때문에 대개 동적 계획법을 사용하는 코드에서는 실제 답을 계산하는 과정을 별도로 구현한다.

// 부분문제가 주어질 떄 그 중 첫 번째 조각을 어떤 선택지로 채울지 하나 하나 시도하면서 최적해를 찾는다.
// 실제 답을 계산하기 위해서는 각 부분 문제마다 어떤 선택을 했을 때 최적해를 얻는지 기록하고, 별도의 재귀
// 함수를 이용, 각 조각에서 한 서택을 되짚어 가며 최적해를 생성해 내면 된다.

int n;

// cache
// S: 주어진 수열
// choices : 각 부분문제에서 선택
int cache[100], S[100], choices[100];

//S[start]에서 시작하는 증가 부분 수열 중 최대 길이를 반환한다.
int lis4(int start)
{
    int & ret = cache[start + 1];
    if(ret != -1) return ret;

    // 항상 S[start]는 존재하므로 길이는 최하 1
    ret = 1;
    int bestNext = -1;
    for(int next = start + 1; next < n; ++next)
        if(start == -1 || S[start] < S[next])
        {
            int cand = lis4(next) + 1;
            if(cand > ret)
            {
                ret = cand;
                bestNext = next;
            }
        }
    choices[start + 1] = bestNext;
    return ret;
}

// 꼭 재귀적으로 표현할 필요는 없지만, 메모이제이션을 사용하는 함수와 구조가 
// 비슷하게 되기 때ㅑ문에 재귀 호출을 이용하는 쪽이 코드를 설계하기 더 편함
void reconstruct(int start, vector<int> & seq)
{
    if(start != -1) seq.push_back(S[start]);
    int next = choices[start+1];
    if(next != -1) reconstruct(next, seq);
}

/*
TODO:
    1. 재귀 호출의 각 단계에서 최적해를 만들었던 선택을 별도의 배열에 저장해둔다.
    2. 별도의 재귀 함수를 이용해 이 선택을 따라가며 각 선택지를 저장 또는 출력한다.
*/