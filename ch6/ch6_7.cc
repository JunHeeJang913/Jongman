//Optimization problem
//ex : traveling salesman Problem
/*
    제한된 시간에 문제를 해결할 수 있는가?
    시작한 도시로 돌아오는 경로를 계산하기 때문에 아무 도시에서 출발해도 문제 없음.
    0번 도시로 제약을 준다. 
    남은 도시를 어떻게 방문할 것인가? -->  (n-1)!가지 --> n=10이므로 시간안에
    해결할 수 있음을 알 수 있다. (10^8)
*/
/*
    n개의 도시로 이루어져있기때문에, 문제를 n조각으로 나눠, 앞에서부터 도시를 하나씩 추가해 경로를 만들어간다.
    shortestPath(path) : path가 지금까지 만든 경로일 때, 나머지 도시들을 모두 방문하는 경로들 중 가장 짧은 것의 길이를 반환한다.
*/
#include <iostream>
#include <vector>

using namespace std;

const int MAX = 10;
int n_town;
double dist[MAX][MAX];
const int INF = 987654321;

double shortestPath(vector<int> & path, vector<bool> & visited, double cur_length){
    //base case : visited all city
    if(path.size() == n_town)
        return cur_length + dist[path[0]][path.back()];
    double ret = INF;
    //try all next town
    for(int next = 0; next < n_town; ++next){
        if(visited[next] == true) continue;
        int here = path.back();
        path.push_back(next);
        visited[next]=true;
        double cand = shortestPath(path, visited, cur_length + dist[here][next]);
        ret = min(ret, cand);
        visited[next] = false; path.pop_back();
    }
    return ret;
}

int main(void){

    return 0;
}