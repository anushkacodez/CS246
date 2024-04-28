#include <bits/stdc++.h>
#define endl '\n'
#define int long long
#define YES cout << "YES\n"
#define NO cout << "NO\n"
#define pb push_back
#define rep(i, l, n) for (int i = l; i < n; i++)
#define F first
#define S second
#define all(v) v.begin(), v.end()
#define vi vector<int>
#define vpi vector<pair<int, int>>
#define pp pair<int, int>
#define mod 1000000007
#define tk1(a) \
    int a;     \
    cin >> a;
#define tk2(a, b) \
    int a, b;     \
    cin >> a >> b;
#define tk3(a, b, c) \
    int a, b, c;     \
    cin >> a >> b >> c;
#define tk4(a, b, c, d) \
    int a, b, c, d;     \
    cin >> a >> b >> c >> d;
using namespace std;
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// template <typename T>
// using ordered_set=tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
// bool comp(pair<pair<int,int>,int> a,pair<pair<int,int>,int> b ){
//     if(a.F.F != b.F.F){
//         return a.F.F < b.F.F;
//     }
//     else{
//         return a.F.S > b.F.S;
//     }
// }
// #define MAXN 1000001
// int spf[MAXN];
// void sieve()
// {
//     spf[1] = 1;
//     for (int i = 2; i < MAXN; i++)
//         spf[i] = i;
//     for (int i = 4; i < MAXN; i += 2)
//         spf[i] = 2;
//     for (int i = 3; i * i < MAXN; i++)
//     {
//         if (spf[i] == i)
//         {
//             for (int j = i * i; j < MAXN; j += i)
//                 if (spf[j] == j)
//                     spf[j] = i;
//         }
//     }
// }
// map<int,int> m;
// void getFactorization(int x)
// {
//     // vector<int> ret;
//     while (x != 1)
//     {
//         // ret.push_back(spf[x]);
//         m[spf[x]]++;
//         x = x / spf[x];
//     }
// }
// int isPrime(int x){
//     if(x%2 == 0)return 2;
//     for (int i = 3; i * i <= x; i+= 2)
//     {
//         if(x%i == 0) return i;
//     }
//     return -1;
// }
void tkv(vector<int> &v, int n)
{
    rep(i, 0, n) cin >> v[i];
}
void debug(vector<int> &v)
{
    rep(i, 0, v.size())
    {
        cout << v[i] << ' ';
    }
    cout << endl;
}
bool comp(pair<int, int> a, pair<int, int> b)
{
    if (a.F == b.F)
    {
        return a.S > b.S;
    }
    else
        return a.F < b.F;
}
int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}
int min(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}
bool check(int k, int n, vpi &v)
{
    int lv = 0, rv = 0;
    rep(i, 0, n)
    {
        lv = max(v[i].F, lv - k);
        rv = min(v[i].S, rv + k);
        if (lv > rv)
            return false;
    }
    return true;
}
void solve()
{
    tk1(n);
    string s; cin>>s;
    int ans = 1;
    vi pre(n + 1);
    vi inv(n);
    rep(i,1,n+1){
        pre[i] = pre[i - 1] + (s[i -  1] - '0');
    }
    debug(pre);
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int numberofthetestcases = 1;
    cin >> numberofthetestcases;
    // sieve();
    while (numberofthetestcases--)
    {
        // cout<<numberofthetestcases<<endl;
        solve();
    }
    return 0;
}