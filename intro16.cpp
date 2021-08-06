#include<bits/stdc++.h>
using namespace std ;
using  vint= vector<int> ;
#define  mod 1000000007 ;
#define  Pi 3.1415926535897932384626433832795 ;
#define all(v) v.begin(), v.end()
#define forr(a, b, c) for (int(a) = (b); (a) < (c); ++(a))
#define ford(a, b, c) for (int(a) = (b); (a) >= (c); --(a))
#define for2(a, b, c) for (int(a) = (b); (a) >= (c); (a)+=2)
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

ll mind=INT_MAX  ;
void gen(vint &a,ll idx,ll s1,ll s2,ll n)
{
    if(idx==n)
    {
        mind=min(mind,abs(s1-s2)) ;
        return ;
    }
    gen(a,idx+1,s1+a[idx],s2,n) ;
    gen(a,idx+1,s1,s2+a[idx],n) ;
    return ;
}

void fastio()
{
 ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}
void solve()
{
ll n ;cin>>n ;
vint a(n,0) ;
forr(i,0,n)cin>>a[i] ;
gen(a,0,0,0,n) ;
cout<<mind<<endl ;
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
