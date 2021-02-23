#include <iostream>
#include <vector>
#include <string>

using namespace std;

/* TODO: 문제의 분할
가장 자연스럽게 조각내는 방법 --> 각 글자를 하나의 조각으로 만들기.
함수 호출 시에 단어의 시작 위치를 정해 주기 때문에 문제의 조각들 중 첫 번째
글자에 해당하는 조각을 간단하게 해결할 수 있음.
TODO: 기저사례의 선택
1. 위치(y,x)에 있는 글자가 원하는 단어의 첫 글자가 아닌 경우 항상 실패
2. (1번에 해당하지 않을 경우) 원하는 단어가 한 글자인 경우 항상 성공

FIXME: 간결한 코드를 작성하는 팁
입력이 잘못되거나 범위에서 벗어난 경우도 기저 사례로 택하여 맨 처음에 처리.
*/

const int dx[] = {-1, -1, -1, 1, 1, 1, 0, 0};
const int dy[] = {-1, 0, 1, -1, 0, 1, -1, 1};

char board[5][5];

bool inRange(int y, int x){
    if( y < 0 || y >= 5 || x < 0 || x>= 5) return false;
    return true;
}

// 보글 게임판의 (y, x)에서 시작하는 단어 word의 존재 여부를 판단한다.
bool hasWord(int y,int x,const string & word){
    if(!inRange(y, x)) return false;
    if(board[y][x] != word[0]) return false;
    if(word.size() == 1) return true;

    for(int direction = 0; direction < 8; ++direction){
        int nextY = y + dy[direction], nextX = x + dx[direction];
        if(hasWord(nextY, nextX, word.substr(1)))
            return true;
    }
    return false;
}

bool solve(const string & word){
    for(int y = 0; y < 5; ++y)
        for(int x = 0; x < 5; ++x){
            if(hasWord(y, x, word) == true)
                return true;
        }
    return false;
}

void initBoard(){
    for(int y = 0; y < 5; ++y){
        for(int x = 0; x < 5; ++x){
            cin >> board[y][x];
        }
    }
}

int main(void){
    int C; cin >> C;
    for(int i = 0; i < C;  ++i){
        initBoard();
        int N; cin >> N;
        for(int j = 0; j < N; ++j){
            string word; cin >> word;
            if(solve(word)) cout << word << " YES" << endl;
            else cout << word << " NO" << endl;
        }
    }
}