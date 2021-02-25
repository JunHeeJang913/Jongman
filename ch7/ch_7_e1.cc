//수열의 빠른 합과 행렬의 빠른 제곱
#include <iostream>

using namespace std;
/*
    1부터 n까지의 합을 n개의 조각으로 나눈 뒤 이를 절바느올 뚝 잘라 
    n/2개의 조각들로 만들어진 부분 문제 두 개를 만든다. (편의상 n 은 짝수)
    fastSum(n)   = 1 + 2 + .. + n
                = (1 + 2 + .. + n/2) + ((n/2+1)+ ... + n)
                = fastSum(n/2) + ???
    ((n/2+1)+ ... + n)  = n/2 * n/2 + (1 + 2 + ... + n/2)
                        = n/2 * n/2 + fastSum(n/2)
    therefore, fastSum(n) = 2 * fastSum(n/2) + n^2 / 4
*/
//필수 조건 : n은 자연수
//1 + 2 + .. + n 을 반환
int fastSum(int n){
    //base case;
    if(n == 1) return 1;
    //when the n is odd;
    if(n % 2 == 1) return fastSum(n-1) + 1;
    //devide and merge;
    return 2 * fastSum(n/2) + (n/2) * (n/2);
}

//행렬의 거듭제곱 
//A^m = A^m/2 * A^m/2
class SquareMatrix;
// n by n identity matrix
SquareMatrix identity(int n);
// A ^ m
SquareMatrix pow(const SquareMatrix & A, int m) {
    // base case 
    if(m == 0) return identity(A.size());
    if(m % 2 > 0) return pow(A, m -1) * A;
    SquareMatrix half = pow(A, m/2);
    return half * half;
}

int main(void){

    return 0;
}