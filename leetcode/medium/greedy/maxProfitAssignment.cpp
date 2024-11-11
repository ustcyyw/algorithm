/**
 * @Time : 2022/4/23-9:04 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
    vector<int> points(100001);
    for(int i = 0; i < difficulty.size(); i++){
        int d = difficulty[i], p = profit[i];
        points[d] = max(points[d], p);
    }
    for(int i = 0, maxP = 0; i < points.size(); i++){
        maxP = max(points[i], maxP);
        points[i] = maxP;
    }
    int res = 0;
    for(int &work : worker)
        res += points[work];
    return res;
}

int main(){

}