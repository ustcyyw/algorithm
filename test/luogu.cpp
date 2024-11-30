/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 1e6 + 5, mod = 1e9 + 7;
int T, n, c, nums[N], lo, hi;

int get_cnt(int num) {
    int cnt = 0;
    while(num > 1)
        num /= 2, cnt++;
    return cnt;
}

void fill_between(int l, int r, int cnt, int sign) {
    int i = sign == 1 ? l + sign : r + sign, base = nums[i - sign] == 1 ? 1 : -1;
    for(; i < r && i > l; i += sign) {
        if(cnt >= 0 && base == -1) {
            nums[i] = nums[i - sign] / 2, cnt--;
            if(cnt == -1 || nums[i] == 1) base = nums[i];
        } else {
            if(nums[i - sign] == base) nums[i] = base * 2;
            else nums[i] = base;
        }
    }
}

void fill(int l, int r, int cnt) {
    if(nums[l] > nums[r]) fill_between(l, r, cnt, 1);
    else fill_between(l, r, cnt, -1);
}

void fill_side(int idx, int sigh) {
    for(int j = idx + sigh; j >= 1 && j <= n; j += sigh) {
        int num = nums[j - sigh];
        if(num != 1) nums[j] = num / 2;
        else nums[j] = 2;
    }
}

bool solve() {
    if(lo == -1) {
        for(int i = 1; i <= n; i++)
            nums[i] = i % 2 == 1 ? 1 : 2;
        return true;
    }
    for(int i = lo; i <= hi; ) {
        int j = i + 1;
        while(j <= hi && nums[j] == -1) j++;
        if(j <= hi) {
            int diff = abs(get_cnt(nums[i]) - get_cnt(nums[j]));
            if((j - i - 1 + diff) % 2 == 0)
                return false;
            fill(i, j, diff);
        }
        i = j;
    }
    fill_side(lo, -1), fill_side(hi, 1);
    for(int i = 1; i < n; i++)
        if(nums[i] != nums[i + 1] / 2 && nums[i + 1] != nums[i] / 2)
            return false;
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n;
        lo = hi = -1;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            if(nums[i] != -1 && lo == -1) lo = i;
            if(nums[i] != -1) hi = i;
        }
        if(!solve()) cout << -1;
        else {
            for(int i = 1; i <= n; i++)
                cout << nums[i] << " ";
        }
        cout << "\n";
    };
};