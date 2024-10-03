//
//  main.cpp
//  C++
//
//  Created by userwei
//

#ifdef LOCAL
    #include "/Users/chou.ting.wei/Coding/stdc++.h"
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
#define Forr(z, x, y) for(int z = x; z >= y; z --)
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
 
void YES(bool b) { cout << (b ? "YES" : "NO") << endl; }
void Yes(bool b) { cout << (b ? "Yes" : "No") << endl; }
void sto(int k, int m) { cout << (k ? " " : "") << m; }
 
const double PI = acos(-1);
const int INF = 1e18;
 
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

const int MAXN = 1e5 + 5;

struct Node{
    Node *lch, *rch;
    int sum, cnt;
    int len;

    Node(){
        lch = rch = nullptr;
        sum = cnt = len = 0;
    }
    void build(int l, int r, vector<int> &val){
        if(l == r){
            len = val[l + 1] - val[l];
            return;
        }
        int mid = l + ((r - l) >> 1);
        lch = new Node();
        rch = new Node();
        lch -> build(l, mid, val);
        rch -> build(mid + 1, r, val);
        len = lch -> len + rch -> len;
    }
    void update(int l, int r, int ql, int qr, int type){
        if(ql > r || qr < l) return;
        if(l == ql && r == qr){
            if(type == 1){
                cnt ++;
                sum = len;
            }
            else{
                cnt --;
                if(cnt == 0){
                    sum = (lch ? lch -> sum + rch -> sum : 0);
                }
            }
        }
        else{
            int mid = l + ((r - l) >> 1);
            if(qr <= mid) lch -> update(l, mid, ql, qr, type);
            else if(ql > mid) rch -> update(mid + 1, r, ql, qr, type);
            else{
                lch -> update(l, mid, ql, mid, type);
                rch -> update(mid + 1, r, mid + 1, qr, type);
            }
            if(cnt > 0) sum = len;
            else sum = lch -> sum + rch -> sum;
        }
    }
};

struct Seg{
    int l, r;
    int y;
    int type;
    Seg(int _l, int _r, int _y, int _type): l(_l), r(_r), y(_y), type(_type) {}
};

bool cmp(Seg &a, Seg &b){
    return a.y < b.y;
}

vector<Seg> v;
vector<int> val;

int32_t main(){
    getAC();
    
    int T;
    cin >> T;
    For(i, 1, T){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        v.eb(x1, x2, y1, 1);
        v.eb(x1, x2, y2, -1);
    }

    for(auto &[l, r, y, t] : v){
        val.eb(l);
        val.eb(r);
    }

    sort(all(val));
    val.resize(unique(all(val)) - val.begin());
    
    for(auto &[l, r, y, t] : v){
        l = lower_bound(all(val), l) - val.begin();
        r = lower_bound(all(val), r) - val.begin();
    }

    int n = sz(val);

    sort(all(v), cmp);
    int ans = 0;

    Node *root = new Node();
    root -> build(0, n - 1, val);

    int lasty = v.front().y;
    for(auto now : v){
        if(lasty != now.y){
            ans += (root -> sum) * (now.y - lasty);
        }
        lasty = now.y;
        root -> update(0, n - 1, now.l, now.r - 1, now.type);
    }

    cout << ans << endl;

    time();
    return 0;
}
