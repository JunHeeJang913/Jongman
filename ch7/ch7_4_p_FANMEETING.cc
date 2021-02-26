#include <iostream>
#include <vector>

using namespace std;

vector<int> multiply(const vector<int> & a,const vector<int> & b){
    vector<int> c(a.size()+b.size(), 0);
    for(int i = 0; i < a.size(); ++i){
        for(int j = 0; j < b.size(); ++j){
            c[i+j] += a[i]*b[j];
        }
    }

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
void addTo(vector<int> & a, const vector<int>& b, int k){
    int length = b.size();
    a.resize(max(a.size() +1, b.size()+k));
    for(int i = 0; i < length; ++i)
        a[i+k] += b[i];
    /*
    for(int i = 0; i < a.size(); ++i){
        if(a[i] >= 10){
            a[i+1] += a[i] % 10;
            a[i] %= 10;
        }
    }*/
}

//a -= b를 구현, a >= b 가정
void subFrom(vector<int> & a, const vector<int> & b){
    int length = b.size();
    a.resize(max(a.size() +1, b.size()+1));
    for(int i = 0; i < length; ++i)
        a[i] -= b[i];
    /*
    for(int i = 0; i < a.size(); ++i){
        if(a[i] < 0){
            a[i+1] -= 1;
            a[i] += 10;
        }
    }*/
}

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

//문제의 그림과 다르게 뒤집어 생각해보는 것도 도움이 될지도..
//문제를 아는 형태로 추상화하기.
// 카라츠바 알고리즘... 피우
int hugs(const string & members, const string& fans){
    int n_mem = members.size(); int n_fan = fans.size();
    vector<int> a(n_mem), b(n_fan);
    for(int i = 0; i < n_mem; ++i) a[i] = (members[i] == 'M');
    for(int i = 0; i < n_fan; ++i) b[n_fan - 1 - i] = (fans[i] == 'M');

    //karatsuba 알고리즘에서 자리 올림은 생략한다.
    vector<int> c = karatsuba(a,b);
    int allHugs = 0;
    for(int i = n_mem - 1; i < n_fan; ++i){
        if(c[i] == 0)
            ++allHugs; 
    }
    return allHugs;
}

void solve(){
    string members, fans;
    cin >> members >> fans;
    cout<< hugs(members, fans) << endl;
}

int main(void){
    int C; cin >> C;
    for(int i = 0; i < C; ++i){
        solve();
    }
    return 0;
}