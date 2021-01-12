#include <iostream>
#include <list>

using namespace std;

void josephus(int n, const int k){
    list<int> survivors;
    for(int i = 1;i<=n;++i) survivors.push_back(i);
    
    auto kill = survivors.begin();

    while(n>2){
        kill = survivors.erase(kill);
        if(kill == survivors.end()) kill = survivors.begin();
        --n;
        for(int i = 0; i < k -1; ++i){
            ++kill;
            if(kill == survivors.end()) kill = survivors.begin();
        }
    }
    cout << survivors.front() << " " << survivors.back() << endl;
}

int main(void){
    int C,N,K;
    cin>>C;
    for(int i = 0; i<C;++i){
        cin>>N>>K;
        josephus(N,K);
    }
    return 0;
}