#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;



vector<int> slice(const vector<int>& v, int a, int b){
    //구간을 주면 그만큼을 반환하는듯...
    return vector<int>(v.begin()+a, v.begin()+b);
}

void printPostorder(const vector<int> & preorder, const vector<int> & inorder){
    //size of tree
    const int N=preorder.size();

    //base Case
    if(preorder.empty()==true) return;
    
    //preorder's first elem is root of the tree
    const int root=preorder[0];

    //이 트리의 좌측 서브트리의 크기는 중위 탐색 결과에서 루트의 위치를 찾아서 알 수 있다.
    //반복자 간의 차를 이용해 인덱스를 반환하는 기술.
    const int L = find(inorder.begin(), inorder.end(), root) - inorder.begin();
    const int R{N-1-L};

    printPostorder(slice(preorder, 1, L+1),slice(inorder, 0, L));
    printPostorder(slice(preorder, L+1, N), slice(inorder, L+1, N));

    cout << root << ' ';
}

int main(void){
    int C;
    cin>>C;

    for(int i = 0; i < C; ++i){
        int N;
        cin >> N;

        //FIXME: 선언을 밖에 해두고 push back만을 하니.. 다음의 트리가 이전의 트리를 포함했다.
        vector<int> preorder;
        vector<int> inorder;
        preorder.reserve(N);
        inorder.reserve(N);
        int value;
        for(int j = 0; j < N; ++j){
            cin >> value;
            preorder.push_back(value);
        }
        for(int j = 0; j < N; ++j){
            cin >> value;
            inorder.push_back(value);
        }
        printPostorder(preorder, inorder);
        cout<< endl;
    }
}