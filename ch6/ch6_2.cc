#include <iostream>
#include <vector>

using namespace std;

/*TODO:
컴퓨터가 수행하는 많은 작업 --> 작은 조각들로 나누어보기
들여다보는 범위가 작아질수록 각 조각들의 형태가 유사해지는 경우 다수
for문과 같은 반복문, 혹은 재귀 함수, 재귀 호출

재귀함수:   자신이 수행할 작업을 유사한 형태의 여러 조각으로 쪼갠 뒤 그 중 한 조각을 수행,
            나머지를 자기 자신을 호출해 실행하는 함수.
*/

//TODO:다음 예를 본다.

//필수 조건 : n >= 1
//결과: 1~n의 합을 반환한다.
int sum(int n){
    int ret = 0;
    for(int i = 1; i <= n; ++i){
        ret += i;
    }
    return ret;
}//-->재귀함수로 어떻게 바꿀 것인가??

//TODO:
//n개의 숫자의 합을 구하는 작업을 n개의 조각으로 쪼개, 더할 각 숫자가 하나의 조각이 되도록 한다.
//조각 중 하나를 자신이 해결하고 나머지를 자기 자신을 호출해 해결
//n만을 빼내면, 1 ~ n-1 조각이 남음, 이들 모두 처리한 결과는 1 ~ n-1의 합
//1을 빼내면 원래 문제와는 형태가 달라짐.

int recursiveSum(int n){
    if(n == 1) return 1;    // 더 이상 쪼개지지 않을 때, 기저 사례! 중요!
    return n + recursiveSum(n-1);
}

/*TODO:
    기저사례 선택시 존재하는 모든 입력이 항상 기저 사례의 답을 이용해 계산될 수 있도록 신경써야한다.
    반복문을 사용해 작성하던 코드를 다르게 짤 수 이는 방법 제공, 문제의 특성에 따라 재귀 호출은
    코딩을 훨씬 간편하게 해 줄 수 있는 강력한 무기가 된다.
*/

//TODO: ex 0 부터 n까지의 원소 중 4개를 고르는 모든 경우를 출력하는 코드
void doSomething(int n){
    for(int i = 0; i < n; ++i)
        for(int j = i + 1; j < n; ++j)
            for(int k = j + 1; k < n; ++k)
                for(int l = k + 1; l < n; ++l)
                    cout << i << " " << j << " " << k << " " << l << endl;
}
//5개를 골라야한다면? 6개를 골라야한다면??
//재귀 호출을 사용하면 간결하고 유연한 코드 가능

//4개의 조각으로 분할 후 각 조각에서 하나의 원소를 고른다.
//남은 원소들을 고르는 작업을 자기 자신에게 떠넘기는 재귀함수.
/*
    작업:
        원소들의 총 개수
        더 골라야 할 원소들의 개수
        지금까지 고른 원소들의 번호
*/

void printPicked(vector<int> & picked){
    for(auto elem : picked){
        cout << elem << " ";
    }
    cout << endl;
}

void pick(int n, vector<int> & picked, int toPick){
    // base case : no need to select
    if(toPick == 0) { printPicked(picked); return;}
    //고를 수 있는 가장 작은 번호
    int smallest = picked.empty() ? 0 : picked.back() + 1;
    for(int next = smallest; next < n; ++next){
        picked.push_back(next);
        pick(n, picked, toPick - 1);
        picked.pop_back();
    }
}

//완전 탐색 시에 매우 유용한 도구!

int main(void){

}