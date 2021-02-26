#include <iostream>
#include <vector>

using namespace std;

int l_fences;
vector<int> h_fences;

void init(){
    cin >> l_fences;
    h_fences = vector<int>(l_fences);
    for(int i = 0; i < l_fences; ++i){
        cin >> h_fences[i];
    }
}

//가장 간단한 솔루션 : findMinHeight n; findMaxArea n^2 * n ==> n^3, 20000^3은 시간초과.
/*
int findMinHeight(int from, int to){
    int min = 987654321;
    for(int i = from; i <= to; ++i)
        if(min > h_fences[i])
            min = h_fences[i];

    return min;
}
int findMaxArea(){
    int maxArea = -987654321;
    for(int i = 0; i < l_fences; ++i){
        for(int j = i; j < l_fences; ++j){
            int tempArea = (j - i + 1)*findMinHeight(i, j);
            if (tempArea > maxArea) maxArea = tempArea;
        }
    }
    return maxArea;
}*/

//조금 나아졌을지도..?
int findMaxWidth(int i){    //O(n)
    int width = 0;
    //현 지점에서 왼쪽으로 갈 수 있는 최대
    for(int x = i; 0 <= x; --x){
        if(h_fences[x] < h_fences[i]) break;
        ++width;
    }
    //현 지점에서 오른쪽으로 갈 수 있는 최대
    for(int x = i; x < l_fences; ++x){
        if(h_fences[x] < h_fences[i]) break;
        ++width;
    }
    return width - 1;
}
int findMaxArea(){  
    // O(n^2) , 20000^2 => 4 * 10 ^ 8인데, 끝까지 가는 경우는 잘 없으니,, 가능하지 않을까?  
    // TODO: 풀렸다! 오예 기분째지네, 생각보다 되게 빨랐다.
    // FIXME:   만약 판자들 높이가 전부같았다면 꼼짝없이 시간초과이다.
    //          분할 정복으로 풀어내는 법을 익히자!
    int maxArea = 0;
    for(int i = 0; i < l_fences; ++i){
        int tempArea = h_fences[i] * findMaxWidth(i);
        if(maxArea < tempArea) maxArea = tempArea;
    }
    return maxArea;
}

//Devide and Conquer
/*
Design : n개의 판자를 절반으로 나눠 두 개의 부분 문제를 만든다. 
가장 큰 직사각형은
    -왼쪽 부분 문제에서 등장
    -오른쪽 부분 문제에서 등장
    -걸쳐서 등장 -> 진짜 부자연스러운 것 같다..ㅜ 자연스러워지길

첫번째의 경우와 두번째의 경우는 각각을 재귀호출하여 쉽게 구할 수 있다.
걸친 케이스만 잘 해결할 수 있으면 해결!

양쪽 부분 문제에 걸친 경우의 답
    걸치려면 경계의 좌, 우의 두 판자는 반드시 포함해야함.
    너비를 좌측이나 우측으로 한칸씩 넓혀가면서, 본다.
*/

int solution(int left, int right){
    //base case : one fence
    if(left == right) return h_fences[left];
    //[left, mid], [mid+1, right] 두 구간으로 나눠 해결한다.
    int mid = (left+right)/2;
    int ret = max(solution(left, mid), solution(mid+1, right));

    //부분문제 3 : 두 부분에 모두 걸치는 사각형 중 제일 큰 것을 찾는다.
    int lo = mid, hi = mid + 1;
    int height = min(h_fences[lo], h_fences[hi]);
    //[mid, mid+1]만 포함하는 너비 2인 사각형을 고려한다.
    ret = max(ret, height * 2);
    //사각형이 입력 전체를 덮을 때까지 확장해 나간다.
    while(hi < right || left < lo){     //while문안에서 확장해 나갈 예정이니까 같을 때는 빼준다.
        //사각형에 인접한 판자 중, 더 높은 판자로 확장한다.
        if(hi < right &&(lo == left || h_fences[lo-1] < h_fences[hi+1])){
            // 오른쪽 판자가 더 높거나, 확장할 수 있는 곳이 오른쪽 밖에 없거나.
            ++hi;
            height = min(height, h_fences[hi]);
        } else {
            --lo;
            height = min(height, h_fences[lo]);
        }
        
        ret = max(ret, height * (hi - lo + 1));
    }
    return ret;
}

void solve(){
    init();
    cout << solution(0, l_fences - 1) << endl;
}

int main(void){
    int C; cin >> C;
    
    for(int i = 0; i < C; ++i)
        solve();

    return 0;
}