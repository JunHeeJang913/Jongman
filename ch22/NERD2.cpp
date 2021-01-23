#include <iostream>
#include <map>

using namespace std;

//현재 다른 점에 지배당하지 않는 점들의 목록을 저장한다.
map <int, int> coords;

bool isDominated(int x, int y){
    //x보다 오른쪽에 있는 점 중 가장 왼쪽에 있는 점을 찾는다.
    map<int, int> :: iterator it = coords.lower_bound(x);
    //그런 점이 없으면 (x,y)는 지배 당하지 않는다.
    if(it == coords.end()) return false;
    //이 점은 x보다 오른쪽에 잇는 점 중에 가장 위에 있는 점이므로
    //x,y가 어느 점에 지배 되려면 이 점에도 지배되어야 한다.
    return y < it->second;
}

void removeDominated(int x, int y){
    map<int, int>::iterator it = coords.lower_bound(x);
    //(x,y)보다 왼쪽에 있는 점이 ㅇ벗다.
    if(it == coords.begin()) return;
    --it;
    //반복문 불변식 : it는 (x,y)의 바로 왼쪽에 있는 점.
    while(true){
        //(x,y) 바로 왼쪽에 오는 점을 찾는다.
        //it 가 표시하는 점이 (x,y) 에 지배되지 않는다면 곧장 종료.
        if(it->second > y) break;
        //이전 점이 더 없으므로 it만 지우고 종료한다.
        if(it == coords.begin()){
            coords.erase(it);
            break;
        }else{  //이전 점으로 이터레이터를 하나 옮겨놓고 it를 지운다
            map <int, int>::iterator jt = it;
            --jt;
            coords.erase(it);
            it = jt;
        }
    }
}

// 새 점 (x,y)가 추가되었을 때, coords를 갱신하고,
// 다른 점에 지배당하지 않는 점들의 개수를 반환한다.

int registered(int x, int y){
    if(isDominated(x,y)) return coords.size();
    removeDominated(x,y);
    coords[x] = y;
    return coords.size();
}