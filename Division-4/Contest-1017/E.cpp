/*
 █████    ███████    ███████████   █████████       Competitive Programming Template
░░███   ███░░░░░███ ░█░░░███░░░█  ███░░░░░███       Author    : Iota (1OT4)
 ░███  ███     ░░███░   ░███  ░  ░███    ░███       Handle    : 1ota (Codeforces)
 ░███ ░███      ░███    ░███     ░███████████       Template  : CP Boilerplate v1.0
 ░███ ░███      ░███    ░███     ░███░░░░░███       Language  : C++20 (GCC/Clang Optimized)
 ░███ ░░███     ███     ░███     ░███    ░███       Compiler  : g++ -std=c++20 -O2 -Wall -Wextra
 █████ ░░░███████░      █████    █████   █████      Shortcut  : precode.cpp
░░░░░    ░░░░░░░       ░░░░░    ░░░░░   ░░░░░       GitHub    : github.com/1OT4/cp-templates

─────────────────────────────────────────────────────────────────────────────
     ⚔️  Let the code battle begin! May the bugs tremble in fear.
─────────────────────────────────────────────────────────────────────────────
*/

#include <bits/stdc++.h>
using namespace std;
 
#ifndef ONLINE_JUDGE
vector<string> DBGc{ "\033[0m", "\033[36m", "\033[33m", "\033[35m" }; // Debugging colors
void dbg_out() { cout << DBGc[0] << endl; }
template<typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) { cout << DBGc[3] << H; if(sizeof...(T)) cout << ", "; dbg_out(T...); }
#define dbg(...) cout << endl << DBGc[1] << "[line" << ":" << __LINE__ << "] " << DBGc[2] << #__VA_ARGS__ << " = ", dbg_out(__VA_ARGS__)
#else
#define dbg(...) void(false)
#endif

#define int64 long long
#define endl "\n"
#define append push_back
#define pii pair<int, int>
#define ff first
#define ss second
#define entire(x) (x).begin(), (x).end()
#define rsort(x) sort((x).rbegin(), (x).rend())
 
int64 mod = 9e18;
 
auto descending = [](auto a, auto b){ return a > b; };
auto Minimum = [](const auto &a, const auto &b){return min(a, b);};
auto Maximum = [](const auto &a, const auto &b){return max(a, b);};
auto XorOperation = [](const auto &a, const auto &b){return (a^b);};
auto ModAddition = [](const auto &a, const auto &b){return (a + b) % mod;};
auto ModMultiply = [](const auto &a, const auto &b){return (a % mod)*(b % mod) % mod;};

struct DSU {
    vector<int> parent, size;

    DSU(int n) : parent(n), size(n, 1) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    
    int find(int v) {
        if (parent[v] != v) parent[v] = find(parent[v]);
        return parent[v];
    }
    
    void merge(int u, int v) {
        int pu = find(u), pv = find(v);
        if (pu == pv) return;
        if (size[pu] < size[pv]) swap(pu, pv);
        parent[pv] = pu, size[pu] += size[pv];
    }
    
    int getSize(int v) { return size[find(v)]; }
};

template <typename var>
struct SegTree{
    int n;
    vector<var> tree;
    var identity;
 
    function<var(const var&, const var&)> combine;
 
    SegTree(int n, var identity, function<var(const var&, const var&)> combine) : n(n), identity(identity), combine(combine) {
        tree.resize(4 * n, identity);
    }
 
    void build (vector<var> &arr, int idx, int l, int r){
        if (l == r) { tree[idx] = arr[l]; return; }
        int mid = (l + r)/2;
        build(arr, idx * 2, l, mid);
        build(arr, idx * 2 + 1, mid + 1, r);
        tree[idx] = combine(tree[idx*2], tree[idx*2 + 1]);
    }
 
    void build (vector<var> &arr) { build(arr, 1, 0, n - 1); }
 
    var query(int idx, int l, int r, int ql, int qr){
        if (qr < l or ql > r) return identity;
        if (ql <= l and r <= qr) return tree[idx];
        int mid = (l + r)/2;
        var leftRes = query(idx*2, l, mid, ql, qr);
        var rightRes = query(idx*2 + 1, mid + 1, r, ql, qr);
        return combine(leftRes, rightRes);
    }
 
    var query(int l, int r) { return query(1, 0, n-1, l, r); }
 
    void update(int idx, int l, int r, int pos, var val){
        if (l == r) { tree[idx] = val; return; }
        int mid = (l + r)/2;
        if (pos <= mid) update(idx*2, l, mid, pos, val);
        else update(idx*2 + 1, mid + 1, r, pos, val);
        tree[idx] = combine(tree[idx*2], tree[idx*2 + 1]);
    }
 
    void update (int pos, var val) { update(1, 0, n - 1, pos, val); }
};

int64 modPow(int64 base, int64 exponent){
    int64 power = 1; base %= mod;
    while (exponent > 0) { if (exponent % 2) power = power*base % mod; exponent /= 2, base = base*base % mod; }
    return power;
}
 
int64 gcd(int64 n1, int64 n2){
    if (n1 > n2) swap(n1, n2);
    while (n1 > 0) n2 %= n1, swap(n1, n2); 
    return n2;
}
 
void extendedEuclid(int64 a, int64 b, int64 &x, int64 &y) {
    if (b == 0) { x = 1; y = 0; return; }
    int64 x1, y1; extendedEuclid(b, a % b, x1, y1);
    x = y1; y = x1 - (a / b) * y1;
}
 
int64 EEA_modInverse(int64 num) {
    if (gcd(num, mod) != 1) return -1;
    int64 x, y; extendedEuclid(num, mod, x, y);
    return (x % mod + mod) % mod;
}
 
int64 modInv(int64 num) { return modPow(num, mod - 2); }
 
vector<int64> spf {1ll};
void factorsPrecompute(int64 lim){
    spf.clear(); ++lim;
    for (int i = 0; i < lim; i++) spf.push_back(1ll);
    for (int64 i = 2; i < lim; i++) if (spf[i] == 1ll)
        for (int64 j = i; j < lim; j += i) if (spf[j] == 1ll) spf[j] = i;
}

vector<pair<int64, int64>> primeFactorize(int64 n){
    vector<pair<int64, int64>> facts;
    while (n > 1){
        if (facts.size() < 1 or facts[facts.size() - 1].first < spf[n]) facts.push_back( pair<int64, int64>{spf[n], 1ll} );
        else facts[facts.size() - 1].second++;    n /= spf[n];
    } return facts;
}

void dfs(int s, vector<bool> &visited, vector<vector<int>> &adj){
    if (visited[s]) return;
    else visited[s] = true;
    for (auto u : adj[s]) dfs(u, visited, adj);
}

const vector<pii> nearby{{1, 0}, {0, 1}, {0, -1}, {-1, 0}}; // diagonal exclusive
const vector<pii> nearbies{{1, 0}, {0, 1}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}}; // diagonal inclusive
 
#define int long long
const int inf = 2e9; 
 
int msb (int64 num){
    return 63 - __builtin_clzll(num);
}

void solve(){
    // Observation [...]
    /* [here] */
 
    // Solution Here [...]
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> cntb(32, 0); // count of numbers with the particular bit active (1)
    for (int i = 0; i < n; i++){
        for (int j = 0; j < cntb.size(); j++){
            if (a[i] & (1 << j)) cntb[j]++;
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++){
        int curans = 0;
        for (int j = 0; j < cntb.size(); j++){
            if (a[i] & (1 << j)) curans += (n - cntb[j]) * (1 << j);
            else curans += cntb[j] * (1 << j);
        }
        ans = max(ans, curans);
    }

    cout << ans << endl;
}

//  *  Testcase-2: the notorious trial.
//  *  WA today, maybe AC tomorrow—if the debugging gods smile on me.
//  *  Onward, O coder!

int32_t main(){
    // freopen("input.in", "r", stdin);
    // freopen("output.out", "w", stdout);
 
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
 
    // mod = value;
 
    int tt = 1; 
    cin >> tt;
    while(tt--) solve();
    return 0;
}