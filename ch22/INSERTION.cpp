#include <iostream>
#include <vector>

using namespace std;

//Treap

typedef int KeyType;

struct Node {
    KeyType key;
    //우선순위, 현 노드를 루트로 하는 서브트리의 크기
    int priority, size;
    Node *left, *right;
    //생성자에서 난수 우선순위를 생성하고, size와 left/right 초기화
    Node(const KeyType& _key) : key(_key), priority(rand()),size(1), left(nullptr), right(nullptr){
    }
    void setLeft(Node*newLeft) { left = newLeft; calcSize(); }
    void setRight(Node * newRight) { right = newRight; calcSize(); }
    void calcSize(){
        size = 1;
        if(left) size += left -> size;
        if(right) size += right ->size;
    }
};

//쪼개기 구현
typedef pair<Node*, Node*> NodePair;
//root를 루트로 하는 트립을 key미만의 값과 이상의 값을 갖는 
//두 개의 트립으로 분리한다.
NodePair split(Node*root, KeyType key){
    if(root == nullptr) return NodePair(nullptr, nullptr);
    //루트가 key미만이면 오른쪽 서브트립을 쪼갠다.
    if(root->key < key){
        NodePair rs = split(root->right, key);
        root->setRight(rs.first);
        return NodePair(root, rs.second);
    }
    //루트가 key 이상이면 왼쪽 서브트리를 쪼갠다.
    NodePair ls = split(root->left, key);
    root->setRight(ls.second);
    return NodePair(ls.first, root);
}

//root를 루트로 하는 트립에 새 노드 node 를 삽입한 뒤 결과 트립의
//루트를 반환한다.
Node * insert(Node * root, Node * node){
    if(root == nullptr) return node;
    //node가 root를 대체해야한다. 해당 서브트립을
    //반으로 잘라 각각의 자손으로 한다.
    if(root->priority < node->priority){
        NodePair splitted = split(root, node->key);
        node->setLeft(splitted.first);
        node->setRight(splitted.second);
        return node;
    }
    else if(node->key < root -> key)
        root->setLeft(insert(root->left, node));
    else
        root->setRight(insert(root->right, node));
    return root;        
}
//treap의 루트를 가리키는 포인터 root가 있을 때 다음과 강티 추가 가능 
//root = insert(root, new Node(Value));

//a와 b가 두개의 트립이고, max(a) < min(b)일 때 이 둘을 합친다.
Node * merge(Node * a, Node * b){
    if(a == nullptr) return b;
    if(b == nullptr) return a;
    
    if(a->priority < b->priority){
        b->setLeft(merge(a, b->left));
        return b;
    }
    a->setRight(merge(a->right, b));
    return a;
}

//root를 루트로 하는 트립에서 key를 지우고 결과트립의 루트를 반환한다.
Node * erase(Node * root, KeyType key){
    if(root == nullptr) return root;
    //루트를 지우고 양 서브트리를 합친뒤 반환한다.
    if(root->key == key){
        Node * ret = merge(root->left, root->right);
        delete root;
        return ret;
    }
    if(key < root -> key)
        root -> setLeft(erase(root->left, key));
    else
        root -> setRight(erase(root->right, key));
    return root;
}

//root를 루트로 하는 트리 중에서 k번째 원소를 반환한다.
Node * kth(Node * root, int k){
    int leftSize = 0;
    if(root->left != nullptr) leftSize = root->left->size;
    if(k <= leftSize) return kth(root->left, k);
    if(k == leftSize +1) return root;
    else return kth(root->right, k - leftSize - 1);
}

//key 보다 작은 키 값의 수를 반환한다.
int countLessThan(Node * root, KeyType key){
    if(root == nullptr) return 0;
    if(root->key >= key)
        return countLessThan(root->left, key);
    int ls = (root->left ? root->left->size : 0);
    return ls + 1 + countLessThan(root->right, key);
}

int n, shifted[50000];
int A[50000];

void solve(){
    //1 ~ N 까지 수를 모두 저장하는 트립
    Node * candidates = nullptr;
    for(int i = 1; i <= n; ++i)
        candidates = insert(candidates, new Node(i));
    //뒤에서 부터 A[]를 채워나간다.
    for(int i = n-1; i >= 0; --i){
        //후보 중 이 수보다 큰 수가 larger개 있다.
        int larger = shifted[i];
        Node * k = kth(candidates, i + 1 - larger);
        A[i] = k->key;
        candidates = erase(candidates, k->key);
    }
}


int main(void){
    int C;
    cin >> C;
    for(int i = 0; i < C; ++i){
        cin >> n;
        for(int j = 0; j < n; ++j){
            cin >> shifted[j];
        }
        solve();
        for(int j = 0 ; j < n; ++j){
            cout << A[j];
        }
        cout << endl;
    }
    return 0;
}