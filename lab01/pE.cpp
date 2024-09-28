//
//  main.cpp
//  C++
//
//  Created by userwei
//

#include <bits/stdc++.h>
#include <bits/extc++.h>

#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

using namespace std;
// using namespace __gnu_pbds;

#define int long long
#define ull unsigned long long

#define For(z, x, y) for(int z = x; z <= y; z ++)
#define Ffor(z, x, y) for(int z = x; z >= y; z --)
#define lowbit(x) ((x) & -(x))

#define ef emplace_front
#define eb emplace_back
#define all(x) x.begin(), x.end()
#define sz(x) ((int) x.size())
#define rev(x) reverse(all(x))

#define mp make_pair
#define pii pair<int, int>
#define pdd pair<double, double>
#define F first
#define S second

#define mset(a, b) memset(a, b, sizeof(a))
#define mcpy(a, b) memcpy(a, b, sizeof(a))

#define endl '\n'

template<typename T> inline void chmin(T &_a, const T &_b) { if(_b < _a) _a = _b; }
template<typename T> inline void chmax(T &_a, const T &_b) { if(_b > _a) _a = _b; }

clock_t start;

void getAC(){
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
        freopen("error.txt", "w", stderr);
        start = clock();
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
}

void time(){
    #ifdef LOCAL
        cerr << "Execution Time : " << double(clock() - start) / CLOCKS_PER_SEC << " (s)" << endl;
        fclose(stdin), fclose(stdout), fclose(stderr);
    #endif
}

int max(int a, int b) { return a > b ? a : b; }
int gcd(int a, int b) { if(a == 0) return b; return b == 0 ? a : gcd(b, a % b); }

const double PI = acos(-1);
const int INF = 5000000000000000000;

struct custom_hash{
    // unordered_map<int, int, custom_hash> safe_map;
    // gp_hash_table<int, int, custom_hash> safe_hash_table;
    static uint64_t splitmix64(uint64_t x){
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const{
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count()); 

int a[200005], b[200005];

bool cmp(int x, int y){
    return x > y;
}

int32_t main(){
    getAC();
    
    int n, k;
    cin >> n >> k;

    For(i, 1, n){
        cin >> a[i];
    }
    For(i, 1, n){
        cin >> b[i];
    }

    sort(a + 1, a + n + 1);
    sort(b + 1, b + n + 1, cmp);

    int l = 0, r = (int)1e18;
    while(l != r){
        int mid = l + ((r - l) >> 1);
        int flg = 1, cnt = 0;
        For(i, 1, n){
            if(a[i] * b[i] > mid){
                int u = a[i] - mid / b[i];
                cnt += u;
            }
            
            if(cnt > k){
                flg = 0;
                break;
            }
        }
        if(flg){
            r = mid;
        }
        else{
            l = mid + 1;
        }
    }

    cout << l << endl;


    time();
    return 0;

}
