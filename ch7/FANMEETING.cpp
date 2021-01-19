#include <iostream>
#include <vector>
#include <string>

using namespace std;

void init(vector<char> & something){
    string line;
    cin >> line;
    for( int i = 0; i < line.length(); ++i)
        something.push_back(line[i]);
}

//brute Force
int brtSolve(int memSize, int fanSize, const vector<char> mem, const vector<char> fan){
    int count = 0;
    for(int start = 0; start < fanSize - memSize +1; ++start){
        if(allHuged(start, mem.size(), mem, fan) == true) ++count;
    }
    return count;
}

bool allHuged(int fanStart, int memSize, const vector<char> mem, const vector<char> fan){
    for(int i = 0; i < memSize; ++i){
        if(mem[i]=='M' && fan[fanStart+i] == 'M')
            return false;
    }
    return true;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


int main(void){
    int C;
    cin >> C;
    
    for(int i = 0; i < C; ++i){
        vector<char> fan;
        vector<char> mem;
        init(mem); init(fan);
        brtSolve(mem.size(), fan.size(), mem, fan);
    }
}