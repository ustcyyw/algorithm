/**
 * @Time : 2023/12/17-9:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 假定前面区间已经划定 当前区间如何选取
 * 满足当前区间存在两个相同的数 就立即完成此区间的分割
 * 这样就能将更多的数留给后续区间 更加利于让下一个区间找到重复的数 从而更早地完成分割
 *
 * 贪心
 */
#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;
int n, nums[N];

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    bool flag = false;
    set<int> set;
    for(int i = 1; i <= n; i++) {
        cin >> nums[i];
        if(set.count(nums[i])) flag = true;
        set.insert(nums[i]);
    }
    if(!flag) { // 压根没有重复元素的情况
        cout << -1 << endl;
        return 0;
    }
    set.clear();
    vector<int> arr;
    int cnt = 0;
    for(int i = 1, j; i <= n; ) {
        j = i;
        while(j <= n && !set.count(nums[j]))
            set.insert(nums[j++]);
        // 最后一组没能划分出来的话 要和上一组合并在一起 组数就不用再+1
        if(j == n + 1) {
            arr.pop_back(), arr.push_back(n);
            break;
        }
        else arr.push_back(j);
        set.clear();
        i = j + 1, cnt++;
    }
    cout << cnt << endl;
    cout << 1;
    for(int i = 0; i < arr.size() - 1; i++) {
        cout << " " << arr[i] << "\n" << arr[i] + 1;
    }
    cout << " " << n << endl;
}