#include <iostream>
#include <string>

using namespace std;

string reverse(string::iterator& it){
    char head = *it;
    ++it;
    //baseCase
    if(head=='b'||head=='w')
        return string(1,head);
    //devide and conquer
    string upperLeft = reverse(it);
    string upperRight = reverse(it);
    string lowerLeft = reverse(it);
    string lowerRight = reverse(it);

    return "x"+lowerLeft+lowerRight+upperLeft+upperRight;
}

int main(void){
    int C;
    cin>>C;

    for(int i = 0; i<C; ++i){
        string s; 
        cin>>s;
        string::iterator it = s.begin();
        cout<<reverse(it)<<endl;
    }

    return 0;
}