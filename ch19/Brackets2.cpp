#include <iostream>
#include <string>
#include <stack>

using namespace std;

const string OPENING{"({["}, CLOSING{")}]"};

bool wellMatched(const string& formula){
    stack<char> openStack;
    for(int i = 0; i<formula.size();++i){
        /*TODO:
            string.found --> 글자의 위치를 반환한다. 없을 경우 string::npos 반환
            npos는 unsigned int --> int로 변환하게 되면 -1 이다.
        */
       //여는 괄호일 경우
        if(OPENING.find(formula[i]) != string::npos){
            openStack.push(formula[i]);
        } else {
            //닫는 괄호일 경우
            //스택이 비어있으면, 당연히 매칭 안됨.
            if(openStack.empty() == true) return false;
            //스택의 맨위와 매칭이 안됨.
            if(OPENING.find(openStack.top()) != CLOSING.find(formula[i]))
                return false;
            openStack.pop();
        }
    }
    return openStack.empty();
}

int main(void){
    string bracket;
    int C;
    cin>>C;
    
    for(int i = 0; i<C ; ++i){
        cin>>bracket;
        if(wellMatched(bracket)==true) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }

    return 0;
}