#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 1e6 + 5;

// 预处理 [1-N]范围内所有数的小于<=1000的因子
// 预处理每个数的所有因子，时间复杂度 O(MlogM)，M=1e5
// 外循环先枚举因子，内循环j代表包含该因子的数，显然是成倍增加的 j += i
vector<int> divisors[N];
int init = []() {
    for (int i = 1; i <= 1000; ++i)
        for (int j = i; j < N; j += i)
            divisors[j].push_back(i);
    return 0;
}();

class Solution {
public:
    long long numberOfSubsequences(vector<int>& nums) {
        int n = nums.size(), maxV = 0;
        for(int num : nums)
            maxV = max(num, maxV);
        vector<vector<int>> sum(n + 1, vector(maxV + 1, 0));
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j <= maxV; j++)
                sum[i][j] = sum[i - 1][j];
            sum[i][nums[i - 1]]++;
        }
        ll ans = 0;
        for(int p = 1; p <= n; p++) {
            for(int r = p + 4; r + 2 <= n; r++) {
                int num = nums[p - 1] * nums[r - 1];
                for(int f : divisors[num]) {
                    if(f > maxV || num / f > maxV) continue;
                    ans += (sum[r - 2][f] - sum[p + 2][f]) * (sum[n][num / f] - sum[r + 2][num / f]);
                }
            }
        }
        return ans;
    }
};

int main() {
    vector<int> arr1 = {2,2,3,3,4,3};
    vector<int> arr2 = {2,3,4};
    vector<int> arr3 = {1,2,3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"cd", "bcd", "xyz"};
    vector<vector<int>> arr4 = {{0,1},{0,2},{0,3},{0,4}};
    vector<vector<int>> arr6 = {{0,1},{1,2},{1,3}};
    Solution s;
    bitset<64> b1(864691128455135232), b2(864691128455135231), b3(576460752303423487);
    for(int i = 63; i >= 0; i--)
        cout << b1[i];
    cout << "\n";
    for(int i = 63; i >= 0; i--)
        cout << b2[i];
    cout << "\n";
    for(int i = 63; i >= 0; i--)
        cout << b3[i];
    cout << (864691128455135232 ^ 864691128455135231) << "\n";
}
