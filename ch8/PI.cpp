#include <iostream>
#include <string>
#include <vector>

using namespace std;

int cache[10001];
const int INF = 987654321;

bool isPattern4(const string& numbers, int start, int end){
    int diff = numbers[start] - numbers[start+1];
    for(int i = start + 1; i < end; ++i){
        if(numbers[i]-numbers[i+1] != diff) return false;
    }
    return true;
}

bool isPattern3(const string& numbers, int start, int end){
    int alter[2] = {numbers[start], numbers[start+1]};
    for(int i = 0; i < end - start; ++i){
        if(numbers[start+i] != alter[i%2]) return false;
    }
    return true;
}

bool isPattern2(const string& numbers, int start, int end){
    int diff = numbers[start] - numbers[start+1];
    if(diff != 1 || diff != -1) return false;
    for(int i = start + 1; i < end; ++i){
        if(numbers[i]-numbers[i+1] != diff) return false;
    }
    return true;
}

bool isPattern1(const string& numbers, int start, int end){
    for(int i = start; i < end; ++i){
        if(numbers[i] != numbers[i+1]) return false;
    }
    return true;
}

int packetDif(string numbers, int start, int end){
    if(isPattern1(numbers, start, end)) return 1;
    if(isPattern2(numbers, start, end)) return 2;
    if(isPattern3(numbers, start, end)) return 4;
    if(isPattern4(numbers, start, end)) return 5;
    return 10;
}

int wholeDif(string numbers, int start){
    if(start == numbers.size()) return 0;
    int & ret = cache[start];

    if(ret != -1) return ret;
    ret = INF;
    for(int L = 3; L <= 5; ++L){
        if(start + L <= numbers.size())
            ret = min(ret, wholeDif(numbers, start+L) + packetDif(numbers, start, start + L -1));
    }
}

int main(void){
    int C;
    cin >> C;
    for(int i = 0; i < C; ++i){
        string numbers;
        cin >> numbers;
        cout << wholeDif(numbers, 0) << endl;        
    }
    return 0;
}