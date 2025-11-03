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
// LeetCode 42. Trapping Rain Water
// Algorithm: Two Pointer Approach (O(n) time, O(1) space)

class Solution {
    public int trap(int[] height) {
        int n = height.length;
        if (n == 0) return 0;

        // Two pointers
        int left = 0, right = n - 1;

        // Variables to store the maximum height seen so far from both ends
        int leftMax = height[left], rightMax = height[right];

        int trappedWater = 0;

        // Traverse from both ends toward the center
        while (left < right) {
            // Always process the smaller height side first
            if (height[left] <= height[right]) {
                // If current bar is lower than the left maximum, water can be trapped
                if (height[left] < leftMax) {
                    trappedWater += leftMax - height[left];
                } else {
                    // Update left maximum if current bar is taller
                    leftMax = height[left];
                }
                left++;
            } else {
                // If current bar is lower than the right maximum, water can be trapped
                if (height[right] < rightMax) {
                    trappedWater += rightMax - height[right];
                } else {
                    // Update right maximum if current bar is taller
                    rightMax = height[right];
                }
                right--;
            }
        }

        return trappedWater;
    }
}
