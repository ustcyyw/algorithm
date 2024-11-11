/**
 * @Time : 2024/2/27-10:51 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛386 t4 二分+反悔贪心
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 求最小时间 如果使用t秒可以完成 那么使用t+1,t+2秒一定可以完成。但是t-1秒不一定
     * 因此具有二分性质 对使用时间进行二分。
     *
     * 第s秒的一次操作 有三种选择
     * 1. nums[i]--
     * 2. nums[index[s]] 设置为0
     * 3. 将满足 nums[i] == 0的一个i进行标记
     *
     * 可以得出3个简单结论
     * a. 对于nums[i] == 0 使用操作2没意义；
     * nums[i] == 1 使用操作1和2都能一秒将其设置为0，且操作1时间更灵活
     * 因此对于 nums[i] <= 1 的下标不使用操作2
     * b. 对于nums[i] > 1的下标 能使用操作2会更节约时间
     * c. 可能会存在 index[s1] == index[s2] = temp, s1 < s2。在s1或者s2都能将nums[temp]设置为0
     * 但是在s1设置进行设置，后续任意时间都能使用操作3标记下标temp 优于在s2设置
     * 比如index[s1] == index[s2] = 1, s1 = 2, s2 = 4, 只有1这个下标需要标记。
     * 在s1设置nums[1] = 0, 第3秒完成操作；反之，则在第5秒完成操作
     *
     * 根据a和c的结论 我们先将无意义的index[s]标记为-1，那么在第s秒，就仅去考虑操作1和3
     *
     * check函数：假定在time秒结束标定 是否可行
     * 第time秒结束标定，如果index[time] != -1，也是无法使用操作2的
     * 因为使用之后 还需要1秒去使用操作3 将对应的下标进行标记
     * 从这个边界条件来看，检查某一秒应该如何操作 需要从后往前查看
     *
     * 只有在存在剩余空余时间能进行操作3的情况下 才可以使用操作2。用free来标记空余时间
     * 如果 index[i] == -1，说明第i秒不使用操作2，用于使用操作1和3，free++
     * 否则 应该使用操作2（因为比操作1节约用时）
     * a. 如果free足够 直接使用即可
     * b. 但是free不足，有些下标就没法使用操作2（否则时间不够使用操作3进行标记）
     * 那就只能放弃一些下标 让它们在靠前的时间使用操作1慢慢减少到1
     * 为了节约时间 显然是放弃那些对应值小的下标
     * 因此 应该使用优先队列去存放想使用操作2处理的下标 当free不足时 将值小的踢掉
     * 但是注意 先前时默认这个被踢掉的下标使用操作2，现在将其踢掉后 原本其占用的1秒 就应该计入free
     * （反悔贪心）
     *
     * 遍历结束后，所有剩余的free将用于操作1和3。操作1针对还没有使用操作2的下标，操作3针对所有下标
     * 记sum为 nums中元素和 + n, temp为使用操作2的元素和
     * sum - temp就是还需要多少次操作1和3， 如果free >= sum - temp，就可以在time秒内标记所有下标
     *
     */
    long long sum;
    int earliestSecondToMarkIndices(vector<int>& nums, vector<int>& index) {
        int n = nums.size(), m = index.size();
        if(n > m) return -1;
        sum = accumulate(nums.begin(), nums.end(), 0ll) + n;
        // 先将无意义的index[s]标记为-1，那么在第s秒，就仅去考虑操作1和3
        vector<bool> marked(n + 1, false);
        for(int i = 0; i < m; i++) {
            int id = index[i];
            if(marked[id] || nums[id - 1] <= 1) index[i] = -1;
            else marked[id] = true;
        }
        int lo = n, hi = m + 1;
        while(lo < hi) {
            int mid = (lo + hi) >> 1;
            if(check(nums, index, mid)) hi = mid;
            else lo = mid + 1;
        }
        return lo == m + 1 ? -1 : lo;
    }

    bool check(vector<int>& nums, vector<int>& index, int time) {
        priority_queue<int, vector<int>, greater<>> pq; // 最小优先队列
        int free = 0;
        for(int i = time - 1; i >= 0; i--) {
            if(index[i] == -1) free++;
            else {
                pq.push(nums[index[i] - 1]);
                if(pq.size() > free) pq.pop(), free++;
            }
        }
        long long temp = sum;
        while(!pq.empty()) {
            temp -= pq.top(), pq.pop();
        }
        return temp <= free;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}