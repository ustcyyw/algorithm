/**
 * @Time : 2024/4/3-4:22 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 圆的五种位置关系 分类计算
 */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
const ld pi = 3.1415926535897932384626433832;
using namespace std;

ld get_angle(ll a, ll b, ld c) { // 余弦定律求角度
    ld val = (b * b + c * c - a * a) * (ld)0.5 / (b * c);
    return acos(val);
}

ld part_s(ld angle, ll r) {
    ld d = r * cos(angle), h = r * sin(angle);
    ld s1 = d * h, s2 = r * r * angle;
    return s2 - s1;
}

ld solve() {
    ll x1, y1, r1, x2, y2, r2;
    cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
    ll dx = x1 - x2, dy = y1 - y2;
    ld c = sqrt(dx * dx + dy * dy);
    if(c >= r1 + r2) return 0; // 相切 相离的情况
    if(c <= abs(r1 - r2)) { // 内含的情况
        ll r = min(r1, r2);
        return pi * r * r;
    }
    ld angle1 = get_angle(r2, r1, c), angle2 = get_angle(r1, r2, c);
    return part_s(angle1, r1) + part_s(angle2, r2);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    printf("%.10Lf", solve());
};