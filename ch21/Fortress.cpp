#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int n, y[100], x[100], radius[100];

struct TreeNode{
    vector<TreeNode *> children;
};

int longest;

int height(TreeNode * root){
    vector<int> heights;
    for(int i = 0; i < root->children.size(); ++i){
        heights.push_back(height(root->children[i]));
    }

    if(heights.empty() == true) return 0;

    sort(heights.begin(), heights.end());
    
    if(heights.size() >= 2)
        longest = max(longest, 2+heights[heights.size()-2]+heights[heights.size()-1]);
    
    return heights.back() + 1;
}

int solve(TreeNode * root){
    longest = 0;
    int h = height(root);

    return max(longest, h);
}

int sqr(int x){
    return x*x;
}

int sqrdist(int a, int b){
    return sqr(y[a]-y[b])+sqr(x[a]-x[b]);
}

bool encloses(int a, int b){
    return radius[a] > radius[b] && sqrdist(a,b) < sqr(radius[a]-radius[b]);
}

bool isChild(int parent, int child){
    if(encloses(parent, child)==false) return false;
    for(int i = 0; i < n; ++i){
        if( i != parent && i != child && encloses(parent, i) && encloses(i,child))
            return false;
    }
    return true;
}

TreeNode * getTree(int root){
    TreeNode * ret = new  TreeNode();
    for(int ch = 0; ch < n; ++ch)
        if(isChild(root,ch))
            ret->children.push_back(getTree(ch));
    
    return ret;
}

int main(void){
    int C;
    cin >> C;
    for(int i = 0; i < C; ++i){
        cin >> n;
        memset(y, 0, sizeof(y));
        memset(x, 0, sizeof(x));
        memset(radius, 0, sizeof(radius));
        for(int j = 0; j < n; ++j){
            cin >> y[j] >> x[j] >> radius[j];
        }
        TreeNode * root = getTree(0);
        cout<<solve(root)<<endl;
    }
}