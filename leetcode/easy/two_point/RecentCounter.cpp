/**
 * @Time : 2022/5/7-1:07 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class RecentCounter {
public:
    vector<int> arr;
    int lo = 0;
    RecentCounter() {

    }
    int ping(int t) {
        arr.push_back(t);
        while (lo < arr.size() && arr[lo] + 3000 < t)
            lo++;
        return arr.size() - lo;
    }
};

int main(){

}