# 🧩 3Sum Problem — Full Notes

### 🎯 Goal  
Find all unique triplets `{a[i], a[j], a[k]}` such that:
```
a[i] + a[j] + a[k] == 0
```

---

## ⚙️ Approach 1 — Using `set<vector<int>>`  *(Your Initial Version)*

### **Code**
```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& a) {
        int n = a.size();
        if (n < 3) return vector<vector<int>>{{-1,-1,-1}};
        if (n == 3) {
            int sum = accumulate(a.begin(), a.end(), 0);
            if (sum) return vector<vector<int>>{};
            else return vector<vector<int>>{{a[0], a[1], a[2]}};
        }

        set<vector<int>> res;
        sort(a.begin(), a.end());

        for (int k = 0; k < n; k++) {
            int ak = -a[k];
            int i = 0, j = n - 1;

            while (i < j) {
                if (i == k) { i++; continue; }
                if (j == k) { j--; continue; }
                if (i >= j) break;

                int sum = a[i] + a[j];
                if (sum == ak) {
                    vector<int> triplet = {a[i], a[j], a[k]};
                    sort(triplet.begin(), triplet.end());
                    res.insert(triplet);
                    i++; j--;
                }
                if (sum < ak) i++;
                else if (sum > ak) j--;
            }
        }

        vector<vector<int>> ans(res.begin(), res.end());
        return ans;
    }
};
```

---

### **Working Logic**
1. Sort the array.  
2. For each index `k`, treat `a[k]` as the third element of the triplet.  
3. Use two-pointers `i` (start) and `j` (end) to find pairs such that `a[i] + a[j] = -a[k]`.  
4. Insert all found triplets into a `set<vector<int>>` to automatically remove duplicates.  
5. Convert `set` → `vector` for output.

---

### **Complexity**
| Step | Complexity |
|------|-------------|
| Sorting | O(n log n) |
| Outer Loop | O(n) |
| Two-Pointer per iteration | O(n) |
| `set` insertion | O(log R) per insert (tree balancing) |
| **Total** | **O(n² log n)** |
| **Space** | O(n²) (for result set) |

---

### **Limitations**
- Each insert into `set` adds a `log n` factor.  
- Sorting each triplet is redundant (array already sorted).  
- Using `set` adds memory and pointer overhead.  

---

## ⚡ Approach 2 — Optimized Two-Pointer (O(n²))

### **Code**
```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& a) {
        vector<vector<int>> res;
        sort(a.begin(), a.end());
        int n = a.size();

        for (int k = 0; k < n; k++) {
            if (k > 0 && a[k] == a[k - 1]) continue; // skip duplicate third elements
            if (a[k] > 0) break; // all remaining nums positive

            int target = -a[k];
            int i = k + 1, j = n - 1;

            while (i < j) {
                int sum = a[i] + a[j];
                if (sum == target) {
                    res.push_back({a[k], a[i], a[j]});
                    i++; j--;
                    while (i < j && a[i] == a[i - 1]) i++;  // skip duplicates
                    while (i < j && a[j] == a[j + 1]) j--;  // skip duplicates
                }
                else if (sum < target) i++;
                else j--;
            }
        }
        return res;
    }
};
```

---

### **Optimizations vs. Approach 1**
| Improvement | Explanation |
|--------------|-------------|
| ✅ Removed `set` | No tree overhead → pure O(n²) |
| ✅ No triplet sorting | Array already sorted → triplets naturally ordered |
| ✅ Skip duplicates directly | Manual pointer skips instead of `set` uniqueness |
| ✅ Early break | Stop when `a[k] > 0` (remaining numbers can’t sum to 0) |

---

### **Complexity**
| Step | Complexity |
|------|-------------|
| Sorting | O(n log n) |
| Main two-pointer loop | O(n²) |
| **Total** | **O(n²)** |
| **Space** | O(1) extra (apart from result) |

---

### **Example Trace**
For input:
```
[-1, 0, 1, 2, -1, -4]
```
After sorting → `[-4, -1, -1, 0, 1, 2]`

| k | a[k] | target | Found triplets |
|---|-------|---------|----------------|
| 0 | -4 | +4 | none |
| 1 | -1 | +1 | [-1, 0, 1] and [-1, -1, 2] |
| 2 | -1 | +1 | skipped duplicate |
| 3 | 0 | 0 | none (since 0+1+2=3) |

Final output:
```
[[-1,-1,2], [-1,0,1]]
```

---

## 🧠 Summary Comparison

| Feature | Set-based (Approach 1) | Optimized (Approach 2) |
|----------|------------------------|-------------------------|
| Data structure | `set<vector<int>>` | `vector<vector<int>>` |
| Duplicate handling | via `set` | via pointer skipping |
| Time Complexity | O(n² log n) | O(n²) |
| Space Complexity | O(n²) | O(1) extra |
| Ordered result | Yes | Yes (sorted input) |
| Best use | Simpler for learning/debugging | Production-efficient version |

---

### 💡 Key Takeaways
- Sorting once allows efficient two-pointer O(n²) scanning.  
- Duplicate control through skipping is cleaner and faster than using `set`.  
- Always avoid sorting small triplets when array is already sorted.  
- For large `n`, direct vector storage is better than `set`.  
