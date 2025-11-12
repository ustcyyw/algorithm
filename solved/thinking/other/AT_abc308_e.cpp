/**
 * @Time : 2023/9/15-11:22 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n, nums[N];
string s;

long long solve() {
    unordered_map<int, int> map;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            for(int k = 0; k < 3; k++) {
                for(int l = 0; l <= 3; l++)
                    if(l != i && l != j && l != k) {
                        map[i * 100 + j * 10 + k] = l;
                        break;
                    }
            }
        }
    }
    vector<vector<int>> ms(n, vector(3, 0));
    if(s[0] == 'M') ms[0][nums[0]]++;
    for(int i = 1; i < n; i++) {
        for(int j = 0; j < 3; j++)
            ms[i][j] = ms[i - 1][j];
        if(s[i] == 'M') ms[i][nums[i]]++;
    }
    vector<int> xs(3, 0);
    if(s[n - 1] == 'X') xs[nums[n - 1]]++;
    long long res = 0;
    for(int i = n - 2; i > 0; i--) {
        if(s[i] == 'E') {
            for(int j = 0; j < 3; j++) {
                if(!ms[i - 1][j]) continue;
                for(int k = 0; k < 3; k++)
                    res += (long long)ms[i - 1][j] * xs[k] * map[j * 100 + nums[i] * 10 + k];
            }
        } else if(s[i] == 'X') xs[nums[i]]++;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> nums[i];
    cin >> s;
    cout << solve() << endl;
}