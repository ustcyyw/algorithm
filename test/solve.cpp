#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int P = 13331;

class Solution {
public:
    vector<ull> h, x;
    void str_hash(vector<int>& s) {
        int n = s.size();
        h = vector(n + 1, 0ull), x = vector(n + 1, 0ull);
        h[0] = 0, x[0] = 1;
        for (int i = 1; i <= n; i++) {
            h[i] = h[i - 1] * P + s[i - 1];
            x[i] = x[i - 1] * P;
        }
    }

    ull get_hash(int l, int r) {
        return h[r + 1] - h[l] * x[r - l + 1];
    }

    int beautifulSplits(vector<int>& nums) {
        int cnt = 0, n = nums.size();
        str_hash(nums);
        for(int i = 0; i < n - 1; i++) {
            for(int j = 0; j < i; j++) {
                // [0,j],[j+1,i],[i+1,n-1]
                if(check(0, j, i) || check(j + 1, i, n - 1))
                    cnt++;
            }
        }
        return cnt;
    }

    bool check(int lo, int mid, int hi) {
        int len = mid - lo + 1;
        if(len > hi - mid) return false;
        return get_hash(lo, mid) == get_hash(mid + 1, len + mid);
    }


    int makeStringGood(string s) {
        int maxC = 0;
        vector<int> cnt(26, 0);
        for(char c : s) {
            cnt[c - 'a']++;
            maxC = max(maxC, cnt[c - 'a']);
        }
        vector<vector<int>> infos;
        for(int i = 0; i < 26; i++) {
            if(cnt[i] > 0)
                infos.push_back({cnt[i], i});
        }
        int ans = s.size(), lc = infos.size();
        sort(infos.begin(), infos.end());
        for(int c = 1; c <= maxC; c++) {
            for(int left = 1; left <= lc; left++)
                ans = min(cal(infos, cnt, c, left), ans);
        }
        return ans;
    }

    int cal(vector<vector<int>>& infos, vector<int> arr, int cnt, int left) {
        int ans = 0;
        for(int m = infos.size(), i = 0; i < m - left; i++) {
            ans += arr[infos[i][1]];
            arr[infos[i][1]] = 0;
        }
        return ans + cal(arr, cnt);
    }

    int cal(vector<int>& arr, int cnt) {
        int ans = 0;
        for(int i = 0; i < 26; i++) {
            if(arr[i] == 0) continue;
            if(arr[i] <= cnt) {
                ans += cnt - arr[i];
                continue;
            }
            // 原本的字符多 可以考虑删除 或者考虑转移给下一个字符
            int t1 = arr[i] - cnt;
            if(i + 1 < 26 && arr[i + 1] > 0 && arr[i + 1] < cnt) {
                int need = cnt - arr[i + 1];
                if(t1 > need) arr[i + 1] = cnt, t1 -= need;
                else arr[i + 1] += t1, t1 = 0;
            }
            ans += t1;
        }
        return ans;
    }
};

int main() {
    vector<int> arr1 = {3,8,7,8,7,5};
    vector<int> arr2 = {2,3,4};
    vector<int> arr3 = {1,2,3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"cd", "bcd", "xyz"};
    vector<vector<int>> arr4 = {{0,1},{0,2},{0,3},{0,4}};
    vector<vector<int>> arr6 = {{0,1},{1,2},{1,3}};
    Solution s;
    cout << s.makeStringGood("ruuu");
}
