/**
 * @Time : 2024/4/10-5:07 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 能被25整除 最后两位是00 50 25 75中的一个
 * 枚举最后两位的情况 找其中最小的交换次数
 *
 * 具体枚举其中一种情况时 假设第二位的数是a，第一位的数是b
 * 从右到左 找到第一个出现的a或者b
 * 如果是b 正好将其交换到第一位
 * 如果是a 将其交换到第一位之后 后续再找最靠右的b 将b交换到最右侧 a就自然到了第二位
 * 在种情况下 最靠右的b也在这个a的左边 非得先将b交换到最右侧 那么也会有一次a和b的互换
 * 和先把a换到第一位无区别 所以不用非得先找一个b交换到最右边
 * 注意找不到a和b的情况，以及a或者b出现在最高位时，避免高位为0的情况
 */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll N = 2e5 + 5, T = 2e9 + 1;
int n, p[4][2] = {{0, 0}, {5, 0}, {2, 5}, {7, 5}};
string num, s;

// 找到最靠end的指定的数
int find(int a, int b, int end) {
    for(int i = end; i >= 0; i--)
        if(s[i] - '0' == a || s[i] - '0' == b) return i;
    return -1;
}

// 找到最靠左的非0数
int find2(int end) {
    for(int i = 1; i <= end; i++)
        if(s[i] != '0') return i;
    return -1;
}

// 将i1字母一步一步向右换到i2
void changeRight(int i1, int i2) {
    char c = s[i1];
    for(int i = i1; i < i2; i++)
        s[i] = s[i + 1];
    s[i2] = c;
}

int cal(int a, int b) {
    s = num;
    int res = 0;
    int idx1 = find(a, b, n - 1);
    if(idx1 <= 0) return INT_MAX; // idx1 == -1说明两个要求的数都不存在，idx1 == 0说明只有一个要求的数
    // 将该数交换到最右边
    res += n - 1 - idx1;
    changeRight(idx1, n - 1);
    // 找另外一个要交换的数
    int other = (s[n - 1] - '0' == a) ? b : a;
    int idx2 = find(other, other, n - 2);
    if(idx2 == -1) return INT_MAX; // 找不到另外一个要交换的数
    if(idx2 == 0) { // 要交换的数处于最高位 要避免出现首位为0
        int idx3 = find2(n - 1);
        // 找不到非0数来置换 注意如果n > 2并且找到的非0数是a或b两个数之一 也说明无非将a和b换到末尾
        if(idx3 == -1 || (idx3 == n - 1 && n != 2)) return INT_MAX;
        res += idx3, idx2++; // 此时b被换到了索引为1的位置
    }
    res += n - 2 - idx2; // 将other交换到第二位 如果它等于b，还要再交换一次
    if(other == b && a != b) res++;
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> num;
    if(stoll(num) % 25 == 0) {
        cout << "0";
        return 0;
    }
    n = num.size();
    int res = INT_MAX;
    for(int i = 0; i < 4; i++)
        res = min(res, cal(p[i][0], p[i][1]));
    cout << (res == INT_MAX ? -1 : res);
};