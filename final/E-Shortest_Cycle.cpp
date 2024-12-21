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

// For macOS
#ifdef LOCAL
    #include "/Users/twchou/workspace/personal/template/stdc++.h"
#else
    #include <bits/stdc++.h>
    #include <bits/extc++.h>
    #pragma GCC optimize("O3,unroll-loops")

    // using namespace __gnu_pbds;
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

priority_queue<int, vector<int>, greater<int> > pq;

int32_t main(){
    getAC();

    int n, m;
    cin >> n >> m;

    vector<vector<int> > adj(n + 1, vector<int>());
    for(int i=0; i<m; ++i){
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    vector<int> distance_arr(n+1, -1);
    vector<int> parent(n+1, -1);
    vector<int> mark(n+1, 0);
    int current_mark = 1;
    int min_cycle = INF;
    vector<int> q(n+1);
    
    For(u, 1, n){
        mark[u] = current_mark;
        distance_arr[u] = 0;
        parent[u] = -1;
        q[0] = u;
        int front = 0, back = 1;
        
        while(front < back){
            int v = q[front ++];
            for(auto &w : adj[v]){
                if(mark[w] != current_mark){
                    mark[w] = current_mark;
                    distance_arr[w] = distance_arr[v] + 1;
                    parent[w] = v;
                    q[back ++] = w;
                }
                else if(w != parent[v]){
                    int cycle_length = distance_arr[v] + distance_arr[w] + 1;
                    if(cycle_length < min_cycle){
                        min_cycle = cycle_length;
                    }
                }
            }
        }
        
        For(i, 0, back-1){
            int node = q[i];
            distance_arr[node] = -1;
            parent[node] = -1;
        }
        current_mark++;
    }
    
    if(min_cycle == INF){
        cout << -1;
    }
    else{
        cout << min_cycle;
    }

    time();
    return 0;
}