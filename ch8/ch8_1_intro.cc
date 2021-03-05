#include <iostream>
#include <vector>
#include <string>

using namespace std;
/*
    큰 의미에서 분할접근과 같은 접근 방식 의미
    문제를 더 작은 문제로 나눈뒤, 이 답들로부터 원래 문제에 대한 답을 계산
    문제를 나누는 방식에서 차이 발생, 어떤 부분 문제는 두 개 이상의 문제를 푸는데 
    사용될 수 있기 때문에, 이 문제의 답을 여러 번 계산하는 대신 한 번만 계산하고 계산
    결과를 재활용함으로써 속도의 향상을 꾀할 수 있다.

    저장하는 공간 Cache
    반복되는 부분 문제를 중복되는 부분 문제(overlapping subproblem)이라한다.
*/

// 유명한 문제 Binomial coefficient 이항계수
int bino(int n, int r){
    if(r == 0|| r ==n) return 1;
    return bino(n-1, r-1) + bino(n-1,r);    // 나쁘지 않다. 그러나 같은 함수가 여러번 호출!
}

// 입력인 n,r이 정해져있을 때 bino(n, r)의 반환값이 항상 일정하다는 사실을 
// 이용하면, 이 문제에서 중복 계산을 제거할 수 있다. 
// memoization : 함수의 결과를 저장하는 장소를 마련해 두고, 한 번 계산한 값을 저장해뒀다 재활용하는 최적화 기법
int cache[30][30];
int bino2(int n, int r){
    //base case;
    if(r == 0|| r ==n) return 1;
    //
    if(cache[n][r] != -1) return cache[n][r];
    return cache[n][r] = bino2(n-1,r-1) + bino2(n-1,r);
}

/*
    입력값만으로 함수의 반환 값을 결정되는가 여부 :참조적 투명성(referential transparency)
    메모이제이션은 참조적 투명 함수의 경우에만 적용할 수 있음
    메모이제이션은 흔한 유형 중 하나이기 때문에, 한 가지 패턴을 정해두고 항상 같은 형태로
    구현하기로 하면 작성하기도, 버그를 찾기도 쉬워진다. 
*/
/*
//전부 -1로 초기화한다.
int cache[][]; // 상황에 따라 달라질수도 있음
int doSomething(int a, int b){
    //기저사례를 항상 맨 처음에 처리한다.
    if(...) return ...;
    //(a,b)에 대한 답을 구한 적이 있으면 곧장 반환
    int & ret = cache[a][b]; // 실수를 줄여준다.
    if(ret != -1) return ret;

    // 답을 계산한다.
    
    return ret;
}

int main(){
    memset(cache, -1, sizeof(cache))
}
*/

/*
메모이제이션의 시간복잡도 분석:
    (존재하는 부분 문제의 수) * (한 부분 문제를 풀 때 필요한 반복문의 최대 수행 횟수)
*/

// Ex : 외발뛰기(JUMPGAME)

// 동적 계획법 알고리즘의 첫 단계 : 재귀적으로 해결하는 완전 탐색 알고리즘

//jump(y, x) = (y,x)에서부터 맨 마지막 칸까지 도달할 수 있는지 여부를 반환한다.
// 외발뛰기 문제를 해결하는 재귀 호출 알고리즘
int n, board[100][100];
bool jump(int y, int x){
    // base case: out of range
    if(y >= n || x >= n) return false;
    // base case: arrive at the destination
    if(y == n-1 && x == n-1) return true;
    
    int jumpSize = board[y][x];
    return jump(y+jumpSize, x) || jump(y, x+jumpSize);
}
/*
    메모이제이션 적용하기
    답의 존재여부를 완전 탐색으로 구할 때 흔히 가장 문제가 되는 것은,
    원하는 답은 없는데 전체 답의 개수는 무지막지하게 많은 경우

    여기서 주목할 사실은 입력은 100 * 100 = 10000이 최대인데, 경로는 보다 많으니,
    비둘기집의 원리에 의해 반드시 중복으로 해결되는 부분문제가 존재함. --> 메모이제이션
*/
int cache[100][100];
int jump2(int y, int x){
    //base case
    if(y >= n || x >= n) return 0;
    if(y == n-1 && x == n-1) return 1;
    //memoization
    int& ret = cache[y][x];
    if(ret != -1) return ret;
    int jumpSize = board[y][x];
    return jump2(y+jumpSize, x) || jump2(y, x + jumpSize);
}

// 이 문제는 사실 그래프로 모델링해보면 아주 간단한 도달 가능성 문제가 된다.
// 재귀 호출을 이용하지 않고도 동적 계획법 알고리즘을 구현할 수 있음
// 반복적 동적 계획법이라고 부르며 많은 장점이 있지만, 메모이제이션을 통한
// 접근이 조금 더 직관적이기 때문에, 기본적으로 모든 동적계획법 알고리즘을 재귀 호출을 통해 
// 구현한다. 9.21절에서 반복적 동적 계획법을 다룬다.