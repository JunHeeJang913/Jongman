#include <iostream>
#include <vector>
#define MAX 10
#define INF 987654321
using namespace std;

int n;  //num of city
double dist[MAX][MAX];      //두 도시간 거리

//path : 지금까지 만든 경로
//visited : 각 도시의 방문 여부
//curLength : 지금까지 만든 경로의 길이
//나머지 도시들을 모두 방문하는 경로들 중 제일 짧은 것의 길이를 반환한다.
double shortestPath(vector<int>& path, vector<bool>& visited, double curLength){
    if(path.size() == n)
        return curLength+dist[path[0]][path.back()];
    double ret = INF;
    for(int next = 0; next < n; ++next){
        if(visited[next]) continue;
        int here = path.back();
        path.push_back(next);
        double cand = shortestPath(path, visited, curLength+dist[here][next]);
        ret = min(ret, cand);
        visited[next]=false;
        path.pop_back();
    }
    return ret;
}
