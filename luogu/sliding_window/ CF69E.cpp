/**
 * @Time : 2023/12/1-10:04 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5;
int nums[N], n, k;

int main() {
    cin >> n >> k;
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    unordered_map<int, int> cnt;
    set<int> set;
    for(int lo = 1, hi = 1; hi <= n; hi++) {
        int num1 = nums[hi];
        cnt[num1]++;
        if(cnt[num1] == 1) set.insert(num1);
        if(cnt[num1] == 2) set.erase(set.find(num1));
        if(hi - lo + 1 > k) {
            int num2 = nums[lo++];
            cnt[num2]--;
            if(cnt[num2] == 1) set.insert(num2);
            if(cnt[num2] == 0) set.erase(set.find(num2));
        }
        if(hi - lo + 1 == k) {
            if(set.empty()) cout << "Nothing" << endl;
            else cout << *set.rbegin() << endl;
        }
    }
    return 0;
}