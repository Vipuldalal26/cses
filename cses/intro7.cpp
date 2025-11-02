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
void fun(ll k)
{
    ll ans=0 ;
    if(k<2){cout<<0<<endl ;return ;}
    if(k==2){cout<<6<<endl ;return ;}
    if(k==3){cout<<28<<endl ;return ;}
    if(k==4){cout<<96<<endl ;return ;}
    //4 edges
    ll ed=4*(k*k-3);
    ll ned=8*(k*k-4 ) ;
    ll red=(4*k-16)*(k*k-7);
    ll pen=(4*k-12)*((k)*(k)-5) ;
    ll rem= (k-4)*(k-4)*(k*k-9) ;
    ans=ed+ned+red+pen+rem;
    ans/=2 ;
    cout<<ans<<endl ;return ;

}
void solve()
{
ll n ;cin>>n ;
forr(i,1,n+1)fun(i) ;

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
