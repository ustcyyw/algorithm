/**
 * @Time : 2022/11/15-1:06 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * 正向来做 不知道加和后的数字放在数组的哪一个位置，可能性太多
     * 尝试逆向来做
     * 数组的当前最大值，一定是上一次数组和，然后选择一个位置放置而得到的
     * 从target逆向操作，看是否能还原成初始的数组
     *
     * 假定最大元素为cur_m, a为被当前最大元素替换的元素
     * 数组当前和为sum，除来当前最大元素以为的和为other
     * cur_m = other + a
     * a = cur_m - other
     * 如果a依旧是最大的，那么other并没有变
     * 再上一个元素就是 a - other = cur_m - other - other
     * 以此类推，直到 cur_m - k * other 不再是最大元素
     * 并且只要循环减去other的过程中，cur_m >= other, 那么cur_m大于其余元素之和，cur_m依旧是最大值
     * 因此 <直到 cur_m - k * other 不再是最大元素> 这个过程，会持续到 cur_m < other
     * 其结果就是 cur_m % other
     *
     * 至此完成了对当前最大元素的处理，接着处理变换后的数组中的最大元素
     * 以此类推，直到所有元素都是1
     */
    bool isPossible(vector<int>& target) {
        priority_queue<int> pq;
        long long sum = 0;
        for(int num : target){
            pq.push(num);
            sum += num;
        }
        while (pq.top() != 1){ // 最大元素不为1，说明还没有恢复到初始数组
            int cur_max = pq.top();
            pq.pop();
            long long other = sum - cur_max;
            // 当前最大元素不可能 <= 其它元素之和，否则就会出现该位置的上一个数是非正数的情况，矛盾了；
            // 其余元素之后，最小是1
            if(cur_max <= other || other < 1) return false;
            long long temp = cur_max % other;
            if(temp == 0) temp = other;
            pq.push(temp);
            sum = other + temp;
        }
        return true;
    }
};

int main(){
    Solution s;
    vector<int> arr = {1,1,2};
    s.isPossible(arr);
    cout << 0 << endl;
}