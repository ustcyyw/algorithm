/**
 * @Time : 2025/3/24-11:10 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF961C 1400 暴力枚举 模拟
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e5 + 15, mod = 1e9 + 7;
int T, n, marked[4];
string base[4][105];
vector<vector<int>> p;

void backTrack(vector<int>& arr, int idx) {
    if(idx == 4) {
        vector<int> temp = arr;
        p.push_back(temp);
        return;
    }
    for(int i = 0; i < 4; i++) {
        if(!marked[i]) {
            marked[i] = true;
            arr.push_back(i);
            backTrack(arr, idx + 1);
            arr.pop_back();
            marked[i] = false;
        }
    }
}

vector<string> build(vector<int>& arr) {
    vector<string> ans;
    for(int i = 0; i < 4; i += 2) {
        for(int j = 0; j < n; j++) {
            string temp = base[arr[i]][j] + base[arr[i + 1]][j];
            ans.push_back(temp);
        }
    }
    return ans;
}
// flag = 1表示该行偶数位置是1，奇数位置是0
// flag = 0表示该行偶数位置是0，奇数位置是1
int cal(vector<string>& matrix, int flag) {
    int cnt = 0;
    for(string& line : matrix) {
        for(int i = 0; i < line.size(); i++) {
            if(i % 2 == 0) {
                if(line[i] == '0' && flag == 1) cnt++;
                if(line[i] == '1' && flag == 0) cnt++;
            } else {
                if(line[i] == '0' && flag == 0) cnt++;
                if(line[i] == '1' && flag == 1) cnt++;
            }
        }
        flag = !flag;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n;
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < n; j++)
                cin >> base[i][j];
        }
        int ans = INT_MAX;
        vector<int> arr;
        backTrack(arr, 0);
        for(vector<int>& t : p) {
            vector<string> matrix = build(t);
            ans = min({ans, cal(matrix, 0), cal(matrix, 1)});
        }
        cout << ans;
    }
}