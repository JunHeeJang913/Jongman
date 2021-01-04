#include <iostream>
#include <vector>

using namespace std;

//주어진 칸을 덮을 수 있는 네가지 방법
//블록을 구성하는 세 칸의 상대적 위치 (dy,dx)의 목록

const int coverType[4][3][2]={
    {{0,0},{1,0},{0,1}},
    {{0,0},{0,1},{1,1}},
    {{0,0},{1,0},{1,1,}},
    {{0,0},{1,0},{1,-1}}
};

//board의 (y,x)를 type번 방법으로 덮거나, 덮었던 블록을 없앤다.
//delta = 1이면 덮고, -1이면 덮었던 블록을 없앤다.
//만약 블록이 제대로 덮이지 않은 경우, false 를 반환한다.
bool set(vector<vector<int> >& board, int y, int x, int type, int delta){
    bool ok = true;
    for(int i = 0;i < 3; ++i){
        //type은 4가지의 set 중 어떤 것을 고를래??
        //i는 set에서 세 좌표 중 하나
        //[0],[1]은  y,x 좌표
        const int ny = y + coverType[type][i][0];
        const int nx = x + coverType[type][i][1];
        
        if(ny < 0 || ny >= board.size() || nx<0 || nx >= board[0].size())   //밖에 나감.
            ok = false;
        else if((board[ny][nx] += delta) > 1)       //겹쳐짐
            ok = false;
    }
    return ok;
}

/*
board의 빈칸을 덮을 수 있는 방법의 수 반환
1 :  이미 덮인 칸 or 검은 칸
0 : 안 덮인 칸
*/
int cover(vector<vector<int> > & board){
    //아직 채우지 못한 칸 중 최좌측상단의 칸을 찾는다.
    int y = -1, x = -1;
    for(int i = 0; i<board.size();++i){
        for(int j = 0; j < board[i].size(); ++j){
            if(board[i][j] == 0){
                y = i;
                x = j;
                break;
            }
        }
        if(y != -1) break;
    }

    //기저 사례: 모든 칸을 채웟으면 1 반환
    if( y == -1 ) return 1;
    int ret = 0;
    for(int type = 0;type < 4;++type){
        if(set(board, y, x, type, 1))
            ret += cover(board);
        set(board, y, x, type, -1);
    }
    return ret;
}

int main(void){
    int cases;
    cin >> cases;
    while (cases--) {
        int H, W;
        cin >> H >> W;
        //vector초기화 할때 크기와 원소 지정해 주는 방법.
        //board는 H개의 vector<int>를 원소로 갖고 각 vector<int>는 W개의 0 원소를 갖는다.
        vector<vector<int> > board(H, vector<int>(W, 0));
        int whites = 0;
        for (int i = 0; i < H; i++) {
            string s;
            cin >> s;
            for (int k = 0; k < W; k++) {
                if (s[k] == '#')
                    board[i][k] = 1;
                else{
                    board[i][k] = 0;
                    ++whites;
                }                    
            }
        }
        if(whites%3==0)
            cout<<cover(board)<<endl;
        else
            cout<<0<<endl;        
    }
    return 0;
}