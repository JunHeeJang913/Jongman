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