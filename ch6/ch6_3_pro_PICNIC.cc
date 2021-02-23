#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int> > f_pairs;
vector<bool> taken;

/*
int count(vector<bool>& taken){
    //base case : all students are taken
    bool count_done = true;
    for(bool elem : taken)
        if(elem != true){
            count_done = false;
            break;
        }
    if(count_done == true) return 1;
    int ret = 0;
    //서로 친구인 두 학생을 찾아 짝을 지어준다.
    //FIXME: 다른 순서로 학생들을 짝지어 주는 것을 서로 다른 경우로 카운트. 특정 형태를 갖는 답으로 강제.
    //남은 쌍 중 인덱스가 가장 앞인 것 부터~
    for(auto f_pair : f_pairs){
        int stu1 = f_pair.first, stu2 = f_pair.second;
        if(taken[stu1] == false && taken[stu2] == false){
            taken[stu1] = true; taken[stu2] = true;
            ret += count(taken);
            taken[stu1] = false; taken[stu2] = false;
        }
    }
    return ret;
}*/

bool areFriend(int a, int b){
    for(auto f_pair: f_pairs){
        int stu1 = f_pair.first, stu2 = f_pair.second;
        if(((a == stu1) && (b == stu2))||((a == stu2) && (b == stu1))) return true;
    }
    return false;
}

int count(vector<bool>& taken){
    //find lowest index student from remainder
    int firstFree = -1;
    for(int i = 0; i < taken.size(); ++i){
        if(taken[i] == false) { firstFree = i; break; }
    }
    //base case : all students are taken
    if(firstFree == -1) return 1;
    int ret = 0;
    //서로 친구인 두 학생을 찾아 짝을 지어준다.
    //FIXME: 다른 순서로 학생들을 짝지어 주는 것을 서로 다른 경우로 카운트. 특정 형태를 갖는 답으로 강제.
    for(int pairWith = firstFree + 1; pairWith < taken.size(); ++pairWith){ //taken.size == num of students
        if(!taken[pairWith] && areFriend(firstFree, pairWith)){
            taken[firstFree] = taken[pairWith] = true;
            ret += count(taken);
            taken[firstFree] = taken[pairWith] = false;
        }
    }

    return ret;
}

//전체 문제를 n/2로 쪼개서, 각 조각마다 짝을 만들어줘야함.
int main(void){
    int C; cin >> C;
    for(int i = 0; i < C; ++i){
        int n, m; cin >> n >> m;    // n : num of students, m : num of friend pairs
        f_pairs = vector<pair<int, int> >(m);
        taken = vector<bool>(n, false);
        for(int j = 0; j < m; ++j){
            int student1, student2; cin >> student1 >> student2;
            f_pairs[j] = make_pair(student1, student2);
        }
        cout << count(taken) << endl;
    }
    return 0;
}