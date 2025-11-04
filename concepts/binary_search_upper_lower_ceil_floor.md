# ⚙️ Binary Jump Search (Reverse Galloping Search)

## 🧠 Intuition

Instead of the traditional binary search with `low` and `high` pointers, we use **binary jumps** that start from infinity and keep halving each iteration.  
This approach feels like “zooming in” from a very large stride to the exact answer — it’s the **reverse** of exponential search.

---

## 🔹 Concept

We want to find the **first element ≥ x** (lower bound) or **> x** (upper bound).  
We start with:

```
idx = -1
jump = 2^⌈log₂(n)⌉
```

Then at every step:
```
if arr[idx + jump] < x:
    idx += jump
jump /= 2
```

When `jump == 0`, the next element (`idx + 1`) is the **lower bound**.

---

## ✅ C++ Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

// 🔹 Lower Bound (first element >= x)
int lowerBoundJumpReverse(vector<int>& arr, int x) {
    int n = arr.size();
    int idx = -1;

    int jump = 1;
    while (jump < n) jump <<= 1;  // make jump >= n
    jump >>= 1;                   // largest usable power of 2

    while (jump > 0) {
        if (idx + jump < n && arr[idx + jump] < x)
            idx += jump;
        jump >>= 1;
    }

    return idx + 1; // first index >= x
}

// 🔹 Upper Bound (first element > x)
int upperBoundJumpReverse(vector<int>& arr, int x) {
    int n = arr.size();
    int idx = -1;
    int jump = 1;
    while (jump < n) jump <<= 1;
    jump >>= 1;

    while (jump > 0) {
        if (idx + jump < n && arr[idx + jump] <= x)
            idx += jump;
        jump >>= 1;
    }

    return idx + 1; // first index > x
}

// 🔹 Ceil (smallest value >= x)
int ceilElementJumpReverse(vector<int>& arr, int x) {
    int idx = lowerBoundJumpReverse(arr, x);
    return (idx == arr.size() ? INT_MAX : arr[idx]);
}

// 🔹 Floor (largest value <= x)
int floorElementJumpReverse(vector<int>& arr, int x) {
    int idx = upperBoundJumpReverse(arr, x) - 1;
    return (idx < 0 ? INT_MIN : arr[idx]);
}

int main() {
    vector<int> arr = {1, 3, 5, 7, 9};
    int x = 6;

    cout << "Array: ";
    for (int v : arr) cout << v << " ";
    cout << "\nTarget: " << x << "\n\n";

    int lb = lowerBoundJumpReverse(arr, x);
    int ub = upperBoundJumpReverse(arr, x);
    int ceilVal = ceilElementJumpReverse(arr, x);
    int floorVal = floorElementJumpReverse(arr, x);

    cout << "lower_bound index: " << lb << " (value = "
         << (lb < arr.size() ? to_string(arr[lb]) : "None") << ")\n";
    cout << "upper_bound index: " << ub << " (value = "
         << (ub < arr.size() ? to_string(arr[ub]) : "None") << ")\n";
    cout << "Ceil value: " << (ceilVal == INT_MAX ? string("None") : to_string(ceilVal)) << "\n";
    cout << "Floor value: " << (floorVal == INT_MIN ? string("None") : to_string(floorVal)) << "\n";
}
```

---

## 🧩 Example Walkthrough

For:
```
arr = [1, 3, 5, 7, 9]
x = 6
```

| Step | jump | idx | arr[idx+jump] | Move? | Reason |
|------|-------|------|---------------|--------|---------|
| init | 4 | -1 | arr[3]=7 >6 | no | cannot move |
| jump=2 | 2 | arr[1]=3 <6 | yes | idx=1 |
| jump=1 | 1 | arr[2]=5 <6 | yes | idx=2 |
| jump=0 | stop | — | — | — |

✅ Answer → `idx + 1 = 3` → `arr[3] = 7`  
→ `lower_bound(6) = 7`, `floor = 5`.

---

## ⚡ Complexity

| Step | Cost |
|------|------|
| Jump initialization | O(log n) |
| Halving loop | O(log n) |
| **Total** | **O(log n)** |
| Space | **O(1)** |

---

## 🧠 Conceptual Understanding

This algorithm is effectively **binary search expressed as binary decomposition of index movement**.

- Start large (`∞` stride) → refine (`½`, `¼`, `⅛`, …)
- Each halving step decides whether you can “add” that jump
- Equivalent to setting bits of the answer index one by one

### Analogy:
At each step you decide whether to **flip this bit ON** (`idx += jump`)  
or **leave it OFF** (keep `idx` as is).  
After all bits are tested → you’ve built the binary representation of the target index.

---

## ✅ Summary

| Function | Finds | Movement Rule |
|-----------|--------|----------------|
| `lowerBoundJumpReverse` | first element ≥ x | `< x` |
| `upperBoundJumpReverse` | first element > x | `≤ x` |
| `ceilElementJumpReverse` | smallest ≥ x | same as lower |
| `floorElementJumpReverse` | largest ≤ x | derived from upper |

---

## 💡 Key Insight

- No `low` / `high` pointers needed  
- No overshoot detection  
- Works even in unbounded search space  
- Clean “infinite stride → precise position” mental model  
- Exactly equivalent to binary search — just *viewed from the other side* 🚀
