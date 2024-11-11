/**
 * @Time : 2022/7/4-8:24 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class MedianFinder {
private:
    priority_queue<int> maxPQ; // 默认是最大优先队列
    priority_queue<int, vector<int>, greater<>> minPQ; // 最小优先队列

public:
    MedianFinder() {

    }

    void addNum(int num) {
        if(maxPQ.size() == 0) {
            maxPQ.push(num);
            return;
        }
        minPQ.push(num);
        maxPQ.push(minPQ.top());
        minPQ.pop();
        if(maxPQ.size() > minPQ.size() + 1){
            minPQ.push(maxPQ.top());
            maxPQ.pop();
        }
    }

    double findMedian() {
        if(maxPQ.size() == minPQ.size())
            return (maxPQ.top() + minPQ.top()) * 1.0 / 2;
        return maxPQ.top();
    }
};

int main(){
    
    cout << 0 << endl;
}