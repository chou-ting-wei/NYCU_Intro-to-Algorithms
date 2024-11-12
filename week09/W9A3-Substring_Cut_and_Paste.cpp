//
//  main.cpp
//  C++
//
//  Created by userwei
//

// For Windows
// #include <bits/stdc++.h>
// #include <bits/extc++.h>

// #pragma GCC optimize("O3,unroll-loops")
// using namespace __gnu_pbds;

// For MacOS
#ifdef LOCAL
    #include "/Users/twchou/Coding/stdc++.h"
#else
    #include <bits/stdc++.h>
    #include <bits/extc++.h>
    #pragma GCC optimize("O3,unroll-loops")

    using namespace __gnu_pbds;
#endif

using namespace std;

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
        fclose(stdin);
        fclose(stdout);
        fclose(stderr);
    #endif
}

int max(int a, int b) { return a > b ? a : b; }
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

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

struct Treap{
    char c;
    int pri, size;
    Treap *l, *r;
    Treap(char _c): c(_c), pri(rng()), size(1), l(nullptr), r(nullptr) {}

    void pull(){
        size = 1;
        if(l) size += l -> size;
        if(r) size += r -> size;
    }
};

Treap* merge(Treap *a, Treap *b){
    if(a == nullptr) return b;
    if(b == nullptr) return a;

    if(a -> pri > b -> pri){
        a -> r = merge(a -> r, b);
        a -> pull();
        return a;
    }
    else{
        b -> l = merge(a, b -> l);
        b -> pull();
        return b;
    }
}

inline int size(Treap *p){
    return p ? p -> size : 0;
}

void split(Treap *p, Treap *&a, Treap *&b, int k){
    if(p == nullptr){
        a = b = nullptr;
        return;
    }
    if(size(p -> l) < k){
        a = p;
        split(p -> r, a -> r, b, k - size(p -> l) - 1);
        a -> pull();
    }
    else{
        b = p;
        split(p -> l, a, b -> l, k);
        b -> pull();
    }
}

void output(Treap *p){
    if(p == nullptr) return;
    output(p -> l);
    cout << p -> c;
    output(p -> r);
}

int32_t main(){
    getAC();

    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;

    Treap* root = nullptr;
    For(i, 0, n-1)  root = merge(root, new Treap(s[i]));

    For(i, 1, m){
        int l, r;
        cin >> l >> r;
        Treap *a, *b, *c;
        split(root, a, b, l-1);
        split(b, b, c, r-l+1);
        root = merge(a, merge(c, b));
    }

    output(root);

    time();
    return 0;
}