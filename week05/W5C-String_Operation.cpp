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

const int MOD = 1e9+7;

vector<vector<int> > mmul(vector<vector<int> > a, vector<vector<int> > b){    
    int n = sz(a), m = sz(b[0]), k = sz(b);
    vector<vector<int> > c(n, vector<int>(m, 0));
    For(i, 0, n-1){
        For(j, 0, m-1){
            For(kk, 0, k-1){
                c[i][j] += a[i][kk] * b[kk][j];
                c[i][j] %= MOD;
            }
        }
    }
    
    return c;
}

vector<vector<int> > mpow(vector<vector<int> > a, int b){
    int n = sz(a);
    vector<vector<int> > ret(n, vector<int>(n, 0));
    For(i, 0, n-1) ret[i][i] = 1;
    while(b){
        if(b & 1) ret = mmul(ret, a);
        a = mmul(a, a);
        b >>= 1;
    }
    return ret;
}

vector<vector<int> > M(26, vector<int>(26, 0));
vector<vector<int> > C(26, vector<int>(1, 0));

int32_t main(){
    getAC();
    
    int n, m;
    cin >> n >> m;

    string s;
    cin >> s;

    For(i, 0, n-1){
        C[s[i]-'a'][0] ++;
    }

    int t;
    cin >> t;
    For(i, 0, t-1){
        string tmp;
        cin >> tmp;
        int k = sz(tmp);
        For(j, 0, k-1){
            M[i][tmp[j]-'a'] ++;
        }
    }

    vector<vector<int> > tt = mpow(M, m);

    int res = 0;
    For(i, 0, 25){
        For(j, 0, 25){
            res += tt[i][j] * C[i][0];
            res %= MOD;
        }
    }

    cout << res << endl;

    time();
    return 0;
}
