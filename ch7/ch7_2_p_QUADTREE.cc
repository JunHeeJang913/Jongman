#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*

상하로 뒤집은 출력
xwwwb - > xwbww
x{bw(xwbbw)b} --> x{(xwbbw를 뒤집은 것)b bw} --> x{x(bwwb)bbw}

x가 나오면 뭔가 달라진다. x를 기준으로 무엇인가 해보자!

좌상, 우상, 좌하, 우하 를 구분할 수 있을까?

*/

string picture;

//devide 함수와 reversePic함수가 합쳐져야함.
/*
string devide(string::iterator & it){a
    if(*it == 'x') return devide(++it);
    else {
        char temp = *it;    ++it;
        return string(1, temp);
    }
}

string reversePic(){
    string::iterator it = picture.begin();
    if(*it != 'x') return string(1, *it);
    string t_l = devide(it);
    string t_r = devide(it);
    string b_l = devide(it);
    string b_r = devide(it);

    return string(1, 'x') + b_l + b_r + t_l + t_r;
}*/

string divAndReverse(string::iterator & it){
    string temp = string(1,*it); ++it;
    //base case : 쪼갤것이 없는 경우
    if(temp != "x") return temp;    //명확한 의미를 위해서는 or연산을 쓰는게 좋겠지만,,,,

    string t_l = divAndReverse(it);
    string t_r = divAndReverse(it);
    string b_l = divAndReverse(it);
    string b_r = divAndReverse(it);

    return string(1, 'x') + b_l + b_r + t_l + t_r;
}

void init(){
    cin >> picture;
}

void solve(){
    init();
    string::iterator it = picture.begin();
    cout << divAndReverse(it) << endl;
}

int main(void){
    int C; cin >> C;

    for(int i = 0; i < C; ++i)
        solve();

    return 0;
}