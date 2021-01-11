#include <iostream>
#include <vector>

using namespace std;

//각 판쟈의 높이 저장 배열.
vector<int> h;
//구간 [left, right]에서 찾을 수 있는 가장 큰 사각형의 넓이를 반환한다.
int solve(int left, int right){
    //base Case: 판자가 하나.
    if(left==right) return h[left];
    //devide
    int mid = (left+right)/2;

    //conquer
    int ret = max(solve(left,mid), solve(mid+1, right));
    //sub prob 3: layered
    int lo = mid, hi = mid+1;
    int height = min(h[lo],h[hi]);
    //[mid, mid+1] width = 2 square
    ret = max(ret, height*2);
    while(left < lo || hi < right){
        if(hi<right && (lo == left || h[lo-1] < h[hi+1])){
            ++hi;
            height = min(height, h[hi]);
        }else{
            --lo;
            height = min(height, h[lo]);
        }
        //square's area after expand
        ret = max(ret, height*(hi-lo+1));
    }
    return ret;
}

int main(void){
    int C;
    cin>>C;
    for(int i=0;i<C;++i){
        int N;
        cin>>N;
        h.resize(N);
        for(int j = 0;j<N;++j){
            int n;
            cin>>n;
            h[i]=n;
            cout<<h[i];
        }
        cout<<solve(0, N-1)<<endl;
    }
    

    return 0;
}