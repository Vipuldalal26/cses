#include<bits/stdc++.h>
using namespace std ;
using  vint= vector<int> ;
#define  mod 1000000007 ;
#define  Pi 3.1415926535897932384626433832795 ;
#define all(v) v.begin(), v.end()
#define forr(a, b, c) for (int(a) = (b); (a) < (c); ++(a))
#define ford(a, b, c) for (int(a) = (b); (a) >= (c); --(a))
using  vll =vector<long long> ;
using  ll =long long int ;
using  vc =vector<char>;
using  vs =vector<string> ;
#define  ff first ;
#define  ss second ;
using  pii= pair<int,int> ;
using  vvint= vector<vector<int>> ;
using  vvl =vector<vector<long long>> ;
using  ulli =unsigned long long int ;
using umii= unordered_map<int,int> ;
using umcc = unordered_map<char,char> ;
using umci=unordered_map<char,int> ;
using mii= map<int,int> ;
using mcc=map<char,char> ;
using mci=map<char,int> ;
using usint=unordered_set<int> ;
using sint= set<int> ;
using uscar=unordered_set<char> ;
using scar=set<char> ;

void fastio()
{
 ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}
void solve()
{
    ll n ;cin>>n ;
    ll a=5 ;ll ans=0 ;
    while(n/a)
    {
        ans+=n/a ;
        a*=5 ;
    }
    cout<<ans<<endl ;
}

int main()
{
    fastio() ;
    int t=1;
   // cin>>t ;
    while(t--)
    {
        solve() ;
    }
}
