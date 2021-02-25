//Karatsuba의 빠른 곱셈 알고리즘
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//초등학교 산수 시간 방식

//num[]의 자릿수 올림을 처리한다.
void normalize(vector<int> & num){
    num.push_back(0);
    //자리수 올림을 처리한다. 
    for(int i = 0; i + 1 < num.size(); ++i){
        if(num[i] < 0) {
            int borrow = (abs(num[i]) + 9) / 10;
            num[i+1] -= borrow;
            num[i] += borrow * 10;
        } else {
            num[i+1] += num[i] / 10;
            num[i] %= 10;
        }
    }
    while(num.size() > 1 && num.back() == 0) num.pop_back();
}

// two big natural num's multiply
// 각 배열에는 각 수의 자릿수가 1의 자리에서부터 시작해 저장되어있다.(직관적으로 처리 가능);
// 예 : multiply([3,2,1] , [6,5,4]) = 123 * 456 = 56088 = [8,8,0,6,5];
vector<int> multiply(const vector<int> & a,const vector<int> & b){
    vector<int> c(a.size()+b.size(), 0);
    for(int i = 0; i < a.size(); ++i){
        for(int j = 0; j < b.size(); ++j){
            c[i+j] = a[i]*b[j];
        }
    }

    normalize(c);
    return c;
}
//매우 단순한 알고리즘이지만, 이보다 빠른 것을 고안하는 것은 어렵다.

/*  카라츠바의 알고리즘
    두 수를 각각 절반으로 쪼갠다. 256자리인 두 수를 생각해보자.
    a = a_1 * 10^128 + a_0
    b = b_1 * 10^128 + b_0

    a * b = a_1*b_1*10^256 + 10^128(a_1*b_0 + a_0*b_1) + a_0*b_0 
    여전히 O(n^2), 네번의 곱셈
    그러나 위의 식을 z2 * 10^256 + z1 * 10^128 + z0로 표현한다면
    (a1 + a0) * (b1 + b0)를 활용해서 세번의 곱셈으로 구할 수 있다
*/

// a += b * 10^k 
void addTo(vector<int> & a, const vector<int>& b, int k);

//a -= b를 구현, a >= b 가정
void subFrom(vector<int> & a, const vector<int> & b);

//두 긴 정수의 곱을 반환한다. 
vector<int> karatsuba(const vector<int> & a, const vector<int> &b){
    int an = a.size(); int bn = b.size();
    //a가 b보다 짧다면 둘을 바꾼다.
    if(an < bn) return karatsuba(b,a);
    //base case
    if(an == 0 || bn == 0) return vector<int>();
    //base case : a가 비교적 짧을 경우 O(n^2) 곱셈으로 변경한다.
    if(an < 50) return multiply(a,b);
    int half = an / 2;
    //a 와 b를 둘로 쪼갠다.
    vector<int> a0(a.begin(), a.begin()+half);  //TODO: 이런 식으로 벡터를 추출할 수 있음을 봐두자.
    vector<int> a1(a.begin()+half, a.end());
    vector<int> b0(b.begin(), b.begin()+min<int>(half, bn));
    vector<int> b1(b.begin()+min<int>(half, bn), b.end());

    vector<int> z2 = karatsuba(a1, b1);
    vector<int> z0 = karatsuba(a0, b0);
    
    addTo(a0, a1, 0); addTo(b0, b1, 0);

    vector<int> z1 = karatsuba(a0, b0);
    subFrom(z1, z0); subFrom(z1, z2);
    
    vector<int> ret;
    addTo(ret, z0, 0); addTo(ret, z1, half); addTo(ret, z2, half+half);

    return ret;
}