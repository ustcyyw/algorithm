/**
 * @Time : 2024/1/12-2:20 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 枚举出现的字符数 k = 1,2,..,26 要能被n整除
  * 每一份的字符数为 m = k / n
  *
  * 在固定k的情况下，保留下的字符应该选最多的k个 这样才能让修改次数最少
  * 因此 统计字符串出现次数 按统计数量排序
  * 保留下来的字符 下标范围是[lo, 25]   其中lo = 25 - k + 1
  * 对于下标 小于 lo 的字符 如果存在，要将其变为下标在[lo, 25]中的字符
  * 下标在[lo, 25] 的字符，并且数量 > m 的 要将其变为数量 < m的字符
  * 最终 下标范围是[lo, 25] 的字符都出现m次
  *
  */
#include<bits/stdc++.h>
using namespace std;
string s;
int T, n;

void change(vector<int>& arr1, vector<int>& arr2, int c) {
    int index = arr1.back();
    s[index] = (char)(c + 'a'), arr2.push_back(index);
    arr1.pop_back();
}

void solve() {
    vector<pair<int, vector<int>>> infos;
    for(int i = 0; i < 26; i++)
        infos.push_back({i, {}});
    for(int i = 0; i < n; i++)
        infos[s[i] - 'a'].second.push_back(i);
    sort(infos.begin(), infos.end(),
         [](auto& a, auto& b) -> bool {return a.second.size() < b.second.size();});
    int val = INT_MAX, k = -1;
    for(int i = 1; i <= 26; i++) {
        if(n % i != 0) continue;
        int m = n / i, temp = 0, lo = 25 - i + 1;
        for(int j = 0; j < 26; j++) {
            int sz = (int)infos[j].second.size();
            if(j < lo) temp += sz;
            else if(sz > m) temp += sz - m;
        }
        if(val > temp) val = temp, k = i;
    }
    cout << val << endl;
    int m = n / k, lo = 25 - k + 1, j = lo;
    for(int i = 0; i < lo; ) {
        while(infos[j].second.size() < m && !infos[i].second.empty())
            change(infos[i].second, infos[j].second, infos[j].first);
        if(infos[j].second.size() == m) j++;
        if(infos[i].second.size() == 0) i++;
    }
    for(int i = 25; j >= lo && infos[i].second.size() > m; ) {
        while(infos[j].second.size() < m && infos[i].second.size() > m)
            change(infos[i].second, infos[j].second, infos[j].first);
        if(infos[j].second.size() == m) j++;
        if(infos[i].second.size() == m) i--;
    }
    cout << s << endl;
}

int main(){
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        cin >> s;
        solve();
    }
}