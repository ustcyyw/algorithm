/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
/*
 * a = a | b操作 按位分析
 * 1.a和b某一位同为0或者1，操作之后a和b该位仍然相同
 * 2.a的该位是0，b的该位是1，操作之后a的该位变为1，和b相同
 * 3.a的该位是1，b的该位是0，操作之后a的该位是1，b的还是0 出现不同
 * 因此操作后 如果不出现情况3 a和b就相等了
 * 也就是说只要让 a为1，b为0的位消失（通过+1操作） 通过一次或运算就能得到结果
 *
 * 对于a来说 使用或运算后一定有 a = a | b >= b
 * 因此运算后再进行+运算没有任何意义（a越增加只会比b大得更多）
 * 并且各测试用例中b之和不超过1e6，那么枚举或运算前a使用+操作的次数i 时间复杂度足够
 * 然后考虑b应该怎么调整使得 at | b = at, at = a + i
 * 就是将at为1，b为0的位消除，at固定了，那么就是遇到at为1的时候 b相应地增加 2 ^ j
 * 但是如果存在低位k 该位b为1，a为0，将b的这一位变为0不会影响at | b = at的要求
 * 那么在第j位的+操作 可以相应地节约 2 ^ k次
 */
#include"bits/stdc++.h"
typedef long long ll;
using namespace std;
const int N = 1e6 + 5;
int T, a, b, digit_a[32], digit_b[32], p[32];

int init = []() -> int {
    for(int i = 0, t = 1; i <= 20; i++)
        p[i] = t, t *= 2;
    return 0;
}();

void init_digit(int* arr, int num) {
    for(int i = 0; i <= 20; i++) {
        if((1 << i) & num)
            arr[i] = 1;
    }
}

int cal(int at) {
    memset(digit_a, 0, sizeof(digit_a));
    init_digit(digit_a, at);
    int cost = 0;
    for(int i = 20; i >= 0; i--) {
        if(digit_a[i] && digit_b[i] == 0) cost += p[i];
        if(digit_a[i] == 0 && digit_b[i] && cost > p[i]) cost -= p[i];
    }
    return cost + 1; // 1是最后的一次或操作
}

void solve() {
    memset(digit_b, 0, sizeof(digit_b));
    init_digit(digit_b, b);
    int ans = b - a;
    for(int i = 0; a + i < b; i++)
        ans = min(ans, i + cal(a + i));
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> a >> b;
        solve();
    }
};