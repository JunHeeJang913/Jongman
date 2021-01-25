#include <iostream>

using namespace std;

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