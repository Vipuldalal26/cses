#include<bits/stdc++.h>
using namespace std ;
using  vint= vector<int> ;
#define mod 1000000007
#define  Pi 3.1415926535897932384626433832795
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
ll exp(ll a,ll b)
{
    if(b==1)return a ;
    if(b==0)return 1 ;
    if(b%2)
    {
        return (a*( exp(a,b/2)%mod )*( exp(a,b/2)%mod )+mod)%mod ;
    }
    return (( exp(a,b/2)%mod )*( exp(a,b/2)%mod )+mod)%mod ;
}
void solve()
{
ll n ;cin>>n ;
ll ans=exp(2,n) ;
cout<<ans% mod<<endl ;
}

int main()
{
    fastio() ;
    int t=1;
    //cin>>t ;
    while(t--)
    {
        solve() ;
    }
}
