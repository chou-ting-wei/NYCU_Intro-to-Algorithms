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

vector<int> val;

struct Node{
    Node *lch, *rch;
    int sum;
    int len, tag;
    Node() {
        lch = rch = nullptr;
        sum = len = tag = 0;
    }
    void pull(){
        if(tag > 0) sum = len;
        else if(lch) sum = ((lch -> tag > 0) ? lch -> len : lch -> sum) + ((rch -> tag > 0) ? rch -> len : rch -> sum);
        else sum = 0;
    }
    void push(int l, int r){
        if(tag != 0 && l != r){
            lch->tag += tag;
            rch->tag += tag;
            tag = 0;
        }
    }
    void push2(int l, int r){
        if(tag < 0 && l != r){
            push(l, r);
            int mid = l + ((r - l) >> 1);
            lch -> push2(l, mid);
            rch -> push2(mid + 1, r);
            pull();
        }
    }

    void build(int l, int r){
        if(l == r){
            len = val[l] - val[l - 1];
            return;
        }
        int mid = l + ((r - l) >> 1);
        lch = new Node();
        rch = new Node();
        lch -> build(l, mid);
        rch -> build(mid + 1, r);
        len = lch -> len + rch -> len;
    }

    void update(int l, int r, int ql, int qr, int type){
        if(ql > r || qr < l) return;
        if(ql <= l && r <= qr){
            tag += type;
            push2(l, r);
            return;
        }
        push(l, r);
        int mid = (l + r) / 2;
        lch->update(l, mid, ql, qr, type);
        rch->update(mid + 1, r, ql, qr, type);
        pull();
    }

    int query(int l, int r, int ql, int qr){
        if(ql > r || qr < l) return 0;
        else if(ql <= l && r <= qr){
            // pull();
            // return sum;
            if(tag > 0) return len;
            else if(lch) return ((lch -> tag > 0) ? lch -> len : lch -> sum) + ((rch -> tag > 0) ? rch -> len : rch -> sum);
            else return 0;
        }
        push(l, r);
        pull();
        int mid = l + ((r - l) >> 1);
        return lch ? lch -> query(l, mid, ql, qr) + rch -> query(mid + 1, r, ql, qr) : 0;
    }
};

int32_t main(){
    getAC();
    
    int n;
    cin >> n;

    For(i, 1, n){
        int k;
        cin >> k;
        val.eb(k);
    }

    Node *root = new Node();
    root -> build(1, n - 1);

    int q;
    cin >> q;
    while(q--){
        string s;
        cin >> s;
        int x, y;
        cin >> x >> y;

        if(s == "insert"){
            root -> update(1, n - 1, x, y - 1, 1);
        }
        else if(s == "delete"){
            root -> update(1, n - 1, x, y - 1, -1);
        }
        else{
            cout << root -> query(1, n - 1, x, y - 1) << endl;
        }
    }

    time();
    return 0;
}

