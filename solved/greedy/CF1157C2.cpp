/**
 * @Time : 2024/1/23-9:34 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 对比两个端点 i < j
 * 假定nums[i] < nums[j]，应该将nums[i]弹出
 * 这样两端的数依旧可以选择 nums[i + 1], nums[j](保留着选nums[j - 1]的可能)
 * 但如果是将nums[j]弹出 后续就只能选nums[j - 1]
 * 因此应该优先选择小的数弹出。
 * 直到遇到 nums[i] == nums[j]，选其中一个 另外一个就无法选择 那么那一端就再也选不了了
 * 此时就需要考虑 从哪一端可以拿到更长的上升序列
 *
 * 以上的前提都是 当前选择的数比上一次选择的数更大 因此用last记录上一次选择的数
 */
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int n, nums[N];

void append(string& s, int cnt, char c) {
    while(cnt-- > 0) s.push_back(c);
}

void solve() {
    string s;
    int i = 0, j = n - 1, last = -1;
    while(i < j && nums[i] != nums[j] && max(nums[i], nums[j]) > last) {
        bool left = false;
        if(nums[i] < nums[j]) {
            if(nums[i] > last) left = true;
        } else { // nums[i] > nums[j]
            if(nums[j] <= last) left = true;
        }
        if(left) s.push_back('L'), last = nums[i++];
        else s.push_back('R'), last = nums[j--];
    }
    if(i == j && nums[i] > last) s.push_back('L');
    else if(nums[i] > last){ // 遇到相等的两端 只能取其中一个递增序列了
        int lo = i + 1, hi = j - 1;
        while(lo < j && nums[lo] > nums[lo - 1]) lo++;
        while(hi > i && nums[hi] > nums[hi + 1]) hi--;
        int cnt1 = lo - i, cnt2 = j - hi;
        if(cnt1 >= cnt2) append(s, cnt1, 'L');
        else append(s, cnt2, 'R');
    }
    cout << s.size() << endl;
    cout << s << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> nums[i];
    solve();
}