// 전통적 최적화 문제
#include <iostream>
#include <vector>
#include <string>

/*
    삼각형 위의 최대 경로
완전 탐색으로 시작하기:
    pathSum(y, x, sum) = 현재 위치가 (y, x)이고, 지금까지 만난 수의 합의 sum일 때,
    이 경로를 맨 아래줄까지 연장해서 얻을 수 있는 최대 합을 반환한다.

    path1(y, x, sum0) 
        = max(path(y+1, x, sum + triangle[y][x]), path(y+1, x+1, sum + triangle[y][x]))

    --> 답을 구하기 위해 모든 경로를 다 만들어 봐야 한다는 문제.
*/

// 무식하게 메모이제이션 적용하기
/*
    int n, triangle[100][100];
    int cache[100][100][MAX_NUMBER*100+1];

    --> 문제 : 메모리 너무 많이 사용, + 특정 입력에 대해서는 완전 탐색처럼 동작
            이 말이 무슨 말이냐면, 똑같은 (y,x)위치로 와도 경로마다 다른 합을 갖는다는 것.
*/

/*
입력 걸러내기
    재귀함수의 입력을 두 부류로 나눠보면 얻을 수 있다.
    1. y, x는 재귀 호출이 풀어야 할 부분 문제를 지정, 이 두 입력이 정해지면 앞으로 만들 수 있는 경로가 정해짐.
        앞으로 풀어야 할 조각들에 대한 정보를 주는 입력
    2. 반면 sum은 지금까지 어떤 경로로 이 부분 문제에 도달했는지를 나타낸다.
        지금까지 풀어온 조각들에 대한 정보를 주는 입력

    (y, x)에서 맨 아래줄까지 내려가는 최대 경로는 sum과 무관하다. sum을 입력으로 안받으면 빨라질 것.
    단, 재귀 함수에서 sum을 입력으로 받지 않으면, 이전까지 어떤 숫자를 만났는지 알 수 없기 떄문에, 전체경로의 최대 합을 반환할 수 없음
    따라서 함수의 반환값을 전체 경로의 최대치가 아닌 (y, x)에서 시작하는 부분 경로의 최대치로 바꿀 필요가 있다.

    path2(y, x) = (y, x)에서 시작해서 맨 아래줄까지 내려가는 부분 경로의 최대합을 반환한다.

    path2(y, x) = triangle[y][x] + max(path(y+1, x),path(y+1, x+1))
*/

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

/*
이론적 배경: 최적 부분 구조
    지금까지 어떤 경로로 이 부분 문제에 도달했던, 남은 부분 문제는 항상 최적으로 풀어도 상관없다는 의미
    --> 효율적인 동적 계획법 알고리즘을 적용하기 위해 아주 중요한 조건, 최적 부분 구조

    각 부분 문제의 최적해만 있으면 전체 문제의 최적해를 쉽게 얻어낼 수 있을 경우 이 조건이 성립
    대다수의 경우 직관적으로 이해할 수 있으며 부드드드득이 하게 증명이 필요한 경우 대우를 이용해 증명하게 된다.
*/

// 최대 증가 부분 수열
/*
완전 탐색

//처음 호출 시에는 원 수열 S가 들어온다
// 최대 증가 수열의 길이를 반환
int lis(const vector<int> & A){
    //base case: A is empty
    if(A.empty()) return 0;

    int ret = 0;
    for(int i = 0; i < A.size(); ++i){
        vector<int> B;  // A[i] 보다 큰 수만이 있는 배열
        for(int j = i + 1; j < A.size(); ++j)
            if(A[i] < A[j])
                B.push_back(A[j]);
        ret = max(ret, 1 + lis(B));
    }
    return ret;
}
입력이 정수의 배열이기 떄문에 메모이제이션 적용이 까다롭다.
A의 정의를 이용해 A를 좀더 간단하게 표현하는 방법을 생각해보자.
    1.원래 주어진 수열 S
    2.원래 주어진 수열 S[i]에 대해, S[i+1...] 부분 수열에서 S[i]보다 큰 수들만을 포함하는 부분 수열 == B

2번 정의에서 이전에 선택한 수들이 정의에 포함되지 않은 데 유념한다.
이전에 선택된 수들은 어차피 마지막에 선택된 수보다 전에 있고, 더 작기 때문에 이들보다
뒤에 있고 커야한다는 조건은 2번 조건만으로 모두 만족된다.

또 유념할 부분은 2번 정의의 A는 S의 인덱스와 1:1 대응된다는 점 --> A로 주어질 수 있는 입력인 배열은 N+1이 전부인 점
lis(start) = S[start]에서 시작하는 부분 증가 수열 중 최대의 길이

int n, cache[100], S[100];
int lis2(int start){
    int& ret = cache[start];
    if(ret != -1) return ret;
    //항상 S[start]는 존재하므로 최하 1의 길이, 이게 base case를 대체한다.
    ret = 1;
    for(int next = start + 1; next < n; ++next)
        if(S[start] < S[next])
            ret = max(ret, lis2(next) + 1);
    return ret;
}

//시간복잡도 분석
어림분석은 (존재한느 부분문제의 수) * (한 부분문제를 풀 때 필요한 반복문의 수행회수) 이다.
부분문제의 수는 n+1, 수행회수는 n이므로 O(n^2)임을 알 수 있다.

lis2를 호출할 때는 항상 증가 부분 수열의 시작 위치를 지정해 줘야 하므로, 처음에 호출할 때 각 위치를 순회하면서 최대 값을
찾는 다음과 같은 형태의 코드를 작성해야 한다. 
int maxLen = 0;
for(int begin = 0; begin < n; ++begin)
    maxLen = max(maxLen, lis2(begin));

이것이 귀찮다면, 다음과 같은 간단한 변형으로 코드를 제거할 수 있다.
S[-1] = -inf라고 가정하는 코드를 작성한다.(수열의 초항이 -inf인것)
그렇게 된다면, 모든 시작위치를 자동으로 시도한다.

int n, cache[100], S[100];
int lis3(int start){
    int& ret = cache[start];
    if(ret != -1) return ret;
    //항상 S[start]는 존재하므로 최하 1의 길이, 이게 base case를 대체한다.
    ret = 1;
    for(int next = start + 1; next < n; ++next)
        if(start ==  -1 || S[start] < S[next])
            ret = max(ret, lis3(next) + 1);
    return ret;
}
*/