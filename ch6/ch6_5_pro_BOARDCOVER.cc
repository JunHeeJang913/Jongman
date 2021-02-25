#include <iostream>
#include <string>

//문제를 N조각(블록의 수)로 나누어 한 조각에서 한 블록을 내려놓는다.

using namespace std;

const int MAX = 20;
/* 블록의 모양.
0
0 0
*/
int board[MAX][MAX];
int H, W;   //height, width
int n_white = 0;
int n_possible = 0;

const int cover_type[4][3][2] = {
    {{0, 0}, {0, 1}, {1, 0}},
    {{0, 0}, {0, 1}, {1, 1}},
    {{0, 0}, {1, 0}, {1, 1}},
    {{0, 0}, {1, 0}, {1, -1}}
};

bool inRange(int y, int x){
    if(y < 0 || y >= H || x < 0 || x >=W) return false;
    return true;
}

//try to set block, if it fails, return false;
bool set(int y, int x, int type, int delta){
    bool ok = true;
    for(int i = 0; i < 3; ++i){
        const int ny = y + cover_type[type][i][0];
        const int nx = x + cover_type[type][i][1];
        if(inRange(ny, nx) == false) ok = false;
        else if((board[ny][nx] += delta) > 1) ok = false;
    }
    return ok;
}

//it returns the possible numbers of covering
int cover(){
    //base base case
    if(n_white % 3 != 0) return 0;
    //find the top-left unfilled block
    int y = -1, x = -1;
    for(int it_y = 0; it_y < H; ++it_y){
        for(int it_x = 0; it_x < W; ++it_x){
            if(board[it_y][it_x] == 0){
                y = it_y; x = it_x; break;
            }
        }
        if(y != -1) break;
    }
    

    //base case; if it filled all, return 1;
    if(y == -1) return 1;
    int ret = 0;
    for(int type = 0; type < 4; ++type){
        if(set(y, x, type, 1) == true)
            ret += cover();
        set(y, x, type, -1);
    }
    return ret;
}

void init(){
    cin >> H >> W;
    n_white = 0;
    for(int i = 0 ; i < H; ++i){
        string s; cin >> s;
        for(int j = 0; j < s.size(); ++j)
            if(s[j] == '#') board[i][j] = 1;
            else{
                ++n_white;
                board[i][j] = 0;
            }
    }
}

void solve(){
    init();
    n_possible = cover();
    cout << n_possible << endl;
}

int main(void){
    int C; cin >> C;
    for(int i = 0; i < C; ++i){
        solve();
    }
    return 0;
}