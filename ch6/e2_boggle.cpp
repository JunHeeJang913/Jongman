#include <iostream>
#include <string>

#define BX 5
#define BY 5

using namespace std;

const char board[BY][BX] = {
    {'N','N','N','N','S'},
    {'N','E','E','E','N'},
    {'N','E','Y','E','N'},
    {'N','E','E','E','N'},
    {'N','N','N','N','N'},
};

const int dx[8]={-1,-1,-1,1,1,1,0,0};
const int dy[8]={-1,0,1,-1,0,1,-1,1};

bool inRange(int x, int y){
    if(BX<=x||BY<=y)
        return false;
    return true;
}

bool hasWord(int y, int x, const string&word){
    if(!inRange(y,x)) return false;
    if(board[y][x]!=word[0]) return false;
    if(word.size()==1) return true;

    for(int direction = 0;direction < 8; ++direction){
        int nextY = y + dy[direction];
        int nextX = x + dx[direction];

        if(hasWord(nextY, nextX, word.substr(1)))
            return true;
    }

    return false;
}

int main(void){
    if(hasWord(2,2,"YES"))
        cout<<"yes"<<endl;
    else
        cout<<"no"<<endl;    
}