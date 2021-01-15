#include <iostream>
#include <cstring>

using namespace std;

int n, triangle[100][100];
int cache[100][100];

int path2(int y, int x){
    //base case
    if( y == n-1 ) return triangle[y][x];

    int & ret = cache[y][x];
    if(ret != -1) return ret;
    return ret = max(path2(y+1, x), path2(y+1,x+1))+triangle[y][x];
}

int main(void){
    int C;
    cin>> C;
    for(int i = 0; i < C; ++i){
        cin>>n;
        for(int j = 0; j < n;++j){
            for(int k = 0; k <= j; ++k){
                cin>>triangle[j][k];
            }
        }
        memset(cache, -1, sizeof(cache));
        cout<< path2(0,0) << endl;
    }
}