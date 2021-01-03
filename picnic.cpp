#include <iostream>

using namespace std;
/*
int count = 0;
bool done[10]={false};

bool countPossiblePair(int numOfPeople, int numOfFriend){
    if(numOfFriend<numOfPeople/2) return false;
    if(numOfPeople==2){ ++count; return true; }
    
    countPossiblePair(numOfPeople-2, numOfFriend-1);
}

int main(void){
    //C<=50, 2<=n<=10 1<=m<=55
    int numOfCase, numOfPeople, numOfFriend;
    cin>>numOfCase>>numOfPeople>>numOfFriend;
    
    for(int j = 0; j<numOfCase; ++j){
        static bool areFriend[10][10]={false};
        for(int i = 0; i < numOfFriend;++i){
            int a,b;
            cin>>a>>b;
            areFriend[a][b]=true; areFriend[b][a]=true;
        }
        if(countPossiblePair(numOfPeople,numOfFriend))
            cout<<count<<endl;
        else cout<<"불가능합니다"<<endl;
    }
}*/

int n;
bool areFriend[10][10]={false};

int countPairings(bool taken[10]){
    //남은 학생들 중 가장 번호가 빠른 학생
    int firstFree = -1;
    for(int i=0;i<n;++i){
        if(!taken[i]){
            firstFree=i;
            break;
        }
    }

    //기저 사례:모든 학생이 짝을 찾았으면 한가지 방법을 찾았으므로 종료한다.
    if(firstFree==-1) return 1;
    
    int ret=0;
    //가장 번호가 빠른 학생과 짝지을 학생을 결정한다.
    for(int pairWith = firstFree+1;pairWith<n;++pairWith){
        if(!taken[pairWith]&&areFriend[firstFree][pairWith]){
            taken[firstFree] = taken[pairWith] = true;
            ret += countPairings(taken);
            taken[firstFree] = taken[pairWith] = false;
        }
    }

    return ret;
}

int main(void){
    //C<=50, 2<=n<=10 1<=m<=55
    int numOfCase, numOfPeople, numOfFriend;
    cin>>numOfCase>>numOfPeople>>numOfFriend;

    n=numOfCase;
    
    for(int j = 0; j<numOfCase; ++j){
        for(int i = 0; i < numOfFriend;++i){
            int a,b;
            cin>>a>>b;
            areFriend[a][b]=true; areFriend[b][a]=true;
        }
    }

    bool taken[10] = {false};
    cout<<countPairings(taken);
}

/*
TODO:
왜? 완전 탐색을 생각했는가??
    -->경우가 그렇게 많지 않은 조합의 수 문제였기 때문에
나는 어디까지 생각했나:
    max가 10명-->bool[10][10]으로 친구관계를 표현하자.
    count를 할건데, return 은 bool으로 하고, 함수내부에서 전역변수count의 값을 증가시켜주기로
    재귀함수를 쓸건데, 기저단계가 뭐가 있을까??
        남은사람수/2>친구쌍수 ==> false
        남은사람수 == 2 ==> ++count return true
    호출은 어떻게?? ~~(np-2,np-1)
무엇을 생각못했나?:
    어떻게 하면 쌍을 지을 수 있을까??
    쌍을 짓는 것을 보고 나서-->왜 중복은 나는 고려하지 못했지??
    중복은 어떻게 하면 없앨 수 있나:
        특정 형태를 갖는 답만을 센다.-->코드를 유심히 보자.
        ex) 흔한 형태로는 사전순으로 가장 먼저 오는 답 만을 세어주는 방법이 있다.

FIXME:
시간 초과.... 개선할 방법은???
*/