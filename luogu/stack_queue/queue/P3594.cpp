/**
 * @Time : 2023/5/18-5:15 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 要维护两个区间 内区间是长度为d的 要将所有元素变为0的区间
 * 外区间则是答案所求的 在进行操作后 总和<=p的最长区间
 * 滑动窗口 要找外区间内部最大的内区间和，这样才能让外区间减小更多，尽可能大
 * 内区间最大和 就类似于找窗口内的最大值一样 采用单调队列进行优化
 */
#include<bits/stdc++.h>

using namespace std;
# define ll long long
const int N = 2e6 + 5;
int n, d;
ll p, nums[N];

int max_range() {
    deque<vector<ll>> queue;
    int left = 1, right = 1, ans = -1;
    ll sum_in = 0, sum_out = 0; // 维护内外两个区间和
    while (right <= n) {
        ll num = nums[right];
        sum_out += num, sum_in += num;
        int lo = right - d;
        if(lo >= 1) sum_in -= nums[lo];
        while (!queue.empty() && queue.back()[1] <= sum_in)
            queue.pop_back();
        queue.push_back({max(1, lo + 1), sum_in});
        if(queue.front()[0] < left) queue.pop_front();
        ll t = queue.empty() ? 0 : queue.front()[1];
        if(sum_out - t <= p) ans = max(ans, right - left + 1); // 外区间和<=p 继续尝试区间右扩
        else sum_out -= nums[left++]; // 否则以left为左端点的外区间不可能满足要求了，只能枚举left + 1为左端点的外区间
        right++;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    cin >> n >> p >> d;
    for (int i = 1, num; i <= n; i++) {
        cin >> num;
        nums[i] = num;
    }
    cout << max_range() << endl;
}