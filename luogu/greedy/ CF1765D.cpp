/**
 * @Time : 2024/1/15-4:40 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 节约时间的方式只有一种：看一个视频的时候 同时下载另外一个视频
 * 直观的贪心想法：一个小的接一个大的
 * 但是从用例来看 在无法重叠利用时间的时候 优先排大的比较好
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
long long n, m, nums[N];

void solve() {
    sort(nums, nums + n);
    long long res = 0;
    for(int i = 0, j = n - 1, flag = 1; i <= j; ) {
        if(i == j) { // 最后一个任务 要计算1分钟看的时间
            res += nums[i] + 1;
            break;
        }
        if(flag) { // 先排占空间大的
            while(j >= 0 && nums[j] + nums[i] > m)
                res += nums[j--] + 1;
            // 将无法交叉的安排完之后 优先安排一个大的进行下载（但前提是还有没安排的 也就是 j > i）
            if(j > i) res += nums[j--];
        } else res += nums[i++];
        flag = flag ? 0 : 1;
    }
    cout << res << endl;
}

int main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++)
        cin >> nums[i];
    solve();
}