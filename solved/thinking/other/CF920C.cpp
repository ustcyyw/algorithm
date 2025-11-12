/**
 * @Time : 2023/12/8-12:15 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * s标记了一些可以自由交换的子数组 子数组排序后 最小的数应该大于其前面的数
 * 并且最大的数放置在最后面 以便和后面的子数组进行比较
 * 注意边界处理
 */
#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;
int n, arr[N];
string s;

string solve() {
    for(int i = 0, j = 0; i < n - 1; ) {
        if(s[i] == '0') {
            if(i > 0 && arr[i] < arr[i - 1]) return "NO";
            i++;
            continue;
        }
        j = i;
        int minV = arr[i], maxV = arr[i];
        while(j < n - 1 && s[j] == '1') {
            minV = min(arr[j + 1], minV), maxV = max(arr[j + 1], maxV);
            j++;
        }
        if(i > 0 && minV < arr[i - 1]) return "NO";
        arr[j] = maxV;
        i = j;
    }
    return arr[n - 1] >= arr[n - 2] ? "YES" : "NO";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    memset(arr, 0, sizeof(arr));
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> arr[i];
    cin >> s;
    cout << solve() << endl;
}