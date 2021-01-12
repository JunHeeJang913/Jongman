#include <iostream>
#include <queue>

using namespace std;

struct RNG {
    unsigned int seed;
    RNG(){
        seed = 1983;
    }
    unsigned int next(){
        unsigned int ret = seed;
        seed = ((seed * 214013u) + 2531011u);
        return ret % 10000 + 1;
    }
};

int countRanges(int k, int n){
    RNG rng;    //random number generator
    queue<int> range;   //present interval's number
    int ret = 0 , rangeSum = 0;
    for(int i = 0; i < n; ++i){
        int newSignal = rng.next();
        rangeSum += newSignal;
        range.push(newSignal);

        while(rangeSum > k){
            rangeSum -= range.front();
            range.pop();
        }

        if(rangeSum == k) ++ret;
    }
    return ret;
}

int main(void){
    int C, K, N;
    cin>> C;
    for(int i = 0; i < C; ++i){
        cin>>K>>N;
        cout<<countRanges(K,N)<<endl;
    }
}