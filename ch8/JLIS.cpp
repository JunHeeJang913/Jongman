#include <iostream>
#include <cstring>
#include <limits>

using namespace std;

int n, m;
const long long NEGINF = numeric_limits<long long>::min();
int A[100], B[100];
int cache[101][101];

int jlis(int indexA, int indexB){
    int & ret = cache[indexA+1][indexB+1];
    if(ret != -1) return ret;
    ret = 2;
    long long a = (indexA == -1 ? NEGINF: A[indexA]);
    long long b = (indexB == -1 ? NEGINF: B[indexB]);
    long long maxElement = max(a,b);

    for( int nextA = indexA+1; nextA < n; ++nextA)
        if(maxElement < A[nextA])
            ret = max(ret, jlis(nextA, indexB) + 1);
    for( int nextB = indexB+1; nextB < n; ++nextB)
        if(maxElement < B[nextB])
            ret = max(ret, jlis(indexA, nextB) + 1);
    
    return ret;
}

int main(void){
    int c;
    cin>>c;
    
    for(int i = 0; i < c; ++i){
        memset(cache, -1, sizeof(cache));
        cin>>n>>m;
        for(int j = 0; j < n; ++j){
            cin>>A[j];
        }
        for(int j = 0; j < m; ++j){
            cin>>B[j];
        }
        cout<<jlis(-1,-1)-2<<endl;
    }
}