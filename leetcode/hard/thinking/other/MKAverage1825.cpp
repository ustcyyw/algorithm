/**
 * @Time : 2023/3/31-4:49 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class MKAverage {
public:
    long long sum = 0;
    int k, m, n = 0, total;
    vector<int> nums;
    multiset<int> left, mid, right; // 分为最小的k个元素，最大的k个元素，和其余的中间元素
    MKAverage(int m, int k) {
        this->k = k, this->m = m;
        total = m - 2 * k;
        nums = vector(1e5 + 5, 0);
    }

    void addElement(int num) {
        nums[n++] = num;
        if(n == m) init();
        if(n > m){
            // 将新元素插入相应的区间
            if(num <= *--left.end()) left.insert(num);
            else if(num >= *right.begin()) right.insert(num);
            else mid.insert(num), sum += num;
            // 将要被移除的元素删除
            int t = nums[n - m - 1];
            if(left.count(t)) left.erase(left.find(t));
            else if(right.count(t)) right.erase(right.find(t));
            else mid.erase(mid.find(t)), sum -= t;
            // 三部分数字的数量调整正确
            if(left.size() > k){
                sum += *--left.end();
                mid.insert(*--left.end());
                left.erase(--left.end());
            } else if(left.size() < k) {
                sum -= *mid.begin();
                left.insert(*mid.begin());
                mid.erase(mid.begin());
            }
            if(right.size() > k) {
                sum += *right.begin();
                mid.insert(*right.begin());
                right.erase(right.begin());
            } else if(right.size() < k){
                sum -= *--mid.end();
                right.insert(*--mid.end());
                mid.erase(--mid.end());
            }
        }
    }

    void init(){
        vector<int> aux;
        for(int i = 0; i < m; i++)
            aux.push_back(nums[i]);
        sort(aux.begin(), aux.end());
        for(int i = 0; i < k; i++)
            left.insert(aux[i]);
        for(int i = m - k; i < m; i++)
            right.insert(aux[i]);
        for(int i = k; i < m - k; i++){
            mid.insert(aux[i]);
            sum += aux[i];
        }
    }

    int calculateMKAverage() {
        if(n < m) return -1;
        return sum / total;
    }
};

int main(){

    cout << 0 << endl;
}