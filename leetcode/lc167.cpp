#include "bits/stdc++.h"
using namespace std ;
using  vint= vector<int> ;
#define  mod 1000000007 ;
#define  Pi 3.1415926535897932384626433832795 ;
using  vll =vector<long long> ;
using  ll =long long int ;
using  vc =vector<char>;
using  vs =vector<string> ;
#define  ff first ;
#define  ss second ;
using  pint= pair<int,int> ;
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
class Solution {
public:
    vector<int> twoSum(vector<int>& a, int k) {
        int n=a.size() ;
        int i=0,j=n-1 ;
        while(i<j){
            int sum=a[i]+a[j] ;
            if(sum==k)return vector<int>{i+1,j+1};
            if(sum<k)i++;else j-- ;
        }
        //always one solution exists.But returning empty array in case nothing is found.
        return vector<int>{-1,-1} ;
    }
};