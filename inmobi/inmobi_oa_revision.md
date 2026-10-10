# InMobi SDE OA — Comprehensive Problem Revision Guide

This guide contains structured problem breakdowns, quick mental anchors, edge cases, step-by-step algorithms, and production-grade C++ solutions for all target OA questions.

---

## Table of Contents
1. [LeetCode 1248 — Count Number of Nice Subarrays](#1-leetcode-1248--count-number-of-nice-subarrays)
2. [LeetCode 3640 — Trionic Array II](#2-leetcode-3640--trionic-array-ii)
3. [Circular Defense (The Turret / Tower Range Cover)](#3-circular-defense-the-turret--tower-range-cover)
4. [Multi-GPU Priority Scheduling (Problem Set 3 — Q1)](#4-multi-gpu-priority-scheduling-problem-set-3--q1)
5. [Maximum CTR Advertisement (Problem Set 3 — Q2)](#5-maximum-ctr-advertisement-problem-set-3--q2)
6. [Sum of Maximums of All Subarrays (Problem Set 3 — Q3)](#6-sum-of-maximums-of-all-subarrays-problem-set-3--q3)
7. [K-th Cheapest Pairing on a Generated Cost Grid (PDF Q1)](#7-k-th-cheapest-pairing-on-a-generated-cost-grid-pdf-q1)
8. [Consensus Median of Three Gel Reports (PDF Q2)](#8-consensus-median-of-three-gel-reports-pdf-q2)
9. [Stamped Code Mold Families (PDF Q3)](#9-stamped-code-mold-families-pdf-q3)
10. [Course Schedule III (PDF Q4)](#10-course-schedule-iii-pdf-q4)
11. [JoJo The Perfectionist (PDF Q5)](#11-jojo-the-perfectionist-pdf-q5)
12. [Minimum Time to Transport All Individuals (PDF Q6)](#12-minimum-time-to-transport-all-individuals-pdf-q6)
13. [Dynamic Tree Path Sum (PDF Q7)](#13-dynamic-tree-path-sum-pdf-q7)
14. [City Skyline — Zoning Laws, Construction Decrees & Audits (PDF Q8)](#14-city-skyline--zoning-laws-construction-decrees--audits-pdf-q8)
15. [Array Reduction via MEX — Lexicographically Largest Result (PDF Q9)](#15-array-reduction-via-mex--lexicographically-largest-result-pdf-q9)
16. [Delivery Service — Count Impossible City Pairs (PDF Q10)](#16-delivery-service--count-impossible-city-pairs-pdf-q10)

---

## 1. LeetCode 1248 — Count Number of Nice Subarrays

### Problem Essence & Key Invariants
- An array `nums` and integer `k`. A subarray is "nice" if it contains exactly `k` odd integers.
- All numbers can be mapped to parity: `nums[i] % 2` (1 if odd, 0 if even).
- The goal is counting subarrays with sum equal to `k` in binary array.

### OA Mental Model & Intuition (How to Remember Fast)
- **1-Pass Sliding Window with Prefix Even Counter (`pc`)**:
  - Right pointer expands. Whenever we encounter an odd number, reset prefix counter `pc = 0` and increment odd count `oc`.
  - Whenever `oc == k`, shrink from left: each even number skipped is an extra valid start position. Increment `pc++`, and once we pop the leftmost odd number, `oc` drops to $k-1$.
  - At every step where a window with $k$ odds was formed, add `pc` to the total answer.
- **Alternative**: `atMost(k) - atMost(k - 1)` sliding window.

### Step-by-Step Algorithm
1. Initialize `ans = 0`, `pc = 0` (even prefix count), `oc = 0` (odd count), `l = 0`.
2. Iterate `r` from `0` to `n - 1`:
   - If `nums[r] % 2 != 0`, reset `pc = 0`, increment `oc++`.
   - While `oc == k`:
     - Increment `pc++`.
     - If `nums[l] % 2 != 0`, decrement `oc--`.
     - Increment `l++`.
   - Add `pc` to `ans`.
3. Return `ans`.

### Optimal C++ Solution
```cpp
#include <vector>
using namespace std;

class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int ans = 0, n = nums.size();
        int pc = 0, oc = 0;
        int l = 0, r = 0;

        while (r < n) {
            if (nums[r] % 2) {
                pc = 0;
                oc++;
            }

            while (oc == k) {
                pc++;
                if (nums[l] % 2) {
                    oc--;
                }
                l++;
            }

            ans += pc;
            r++;
        }

        return ans;
    }
};
```

### Complexity
- **Time Complexity**: $\mathcal{O}(N)$ — Each element is visited at most twice.
- **Space Complexity**: $\mathcal{O}(1)$ — In-place two-pointer variables only.

---

## 2. LeetCode 3640 — Trionic Array II

### Problem Essence & Key Invariants
- Find the maximum sum of a **Trionic subarray** of length $\ge 4$.
- A Trionic subarray strictly alternates directions across three contiguous segments:
  1. Strictly increasing: $A[i] < A[i+1] < \dots < A[p]$
  2. Strictly decreasing: $A[p] > A[p+1] > \dots > A[q]$
  3. Strictly increasing: $A[q] < A[q+1] < \dots < A[r]$

### OA Mental Model & Intuition (How to Remember Fast)
- **3-State DP Machine on Slopes**:
  - At each adjacent step $i$ comparing $x = nums[i]$ and $prev = nums[i-1]$:
    - **`up` (Phase 1)**: Can either start fresh from $(prev + x)$ or extend prior `up` $(up + x)$ if $x > prev$.
    - **`down` (Phase 2)**: Can transition from Phase 1 $(up + x)$ or extend existing `down` $(down + x)$ if $x < prev$.
    - **`tri` (Phase 3)**: Can transition from Phase 2 $(down + x)$ or extend prior `tri` $(tri + x)$ if $x > prev$.
  - Any invalid slope resets the state to $-\infty$.
  - Running answer is $\max(ans, tri)$.

### Step-by-Step Algorithm
1. Set large negative constant `NEG = -1e16`.
2. Initialize `up = NEG`, `down = NEG`, `tri = NEG`, `ans = NEG`.
3. Loop $i$ from 1 to $n-1$:
   - Save previous states `oup = up`, `odown = down`, `otri = tri`.
   - If $x > prev$:
     - `up = max(oup + x, prev + x)`
     - `tri = max(otri + x, odown + x)`
     - `down = NEG`
   - Else if $x < prev$:
     - `down = max(oup + x, odown + x)`
     - `up = tri = NEG`
   - Else ($x == prev$):
     - `up = down = tri = NEG`
   - Update `ans = max(ans, tri)`.
4. Return `ans`.

### Optimal C++ Solution
```cpp
#include <vector>
#include <algorithm>
using namespace std;

using ll = long long;

class Solution {
public:
    long long maxSumTrionic(vector<int>& nums) {
        const ll NEG = -1e16;
        ll ans = NEG;
        ll up = NEG, down = NEG, tri = NEG;
        int n = nums.size();

        for (int i = 1; i < n; i++) {
            ll x = nums[i], prev = nums[i - 1];
            ll oup = up, odown = down, otri = tri;

            if (x > prev) {
                // Phase 1 (start new or extend)
                up = max(oup + x, prev + x);
                // Phase 3 (transition from Phase 2 or extend Phase 3)
                tri = max(otri + x, odown + x);
                down = NEG;
            } else if (x < prev) {
                // Phase 2 (transition from Phase 1 or extend Phase 2)
                down = max(oup + x, odown + x);
                up = tri = NEG;
            } else {
                up = down = tri = NEG;
            }

            ans = max(ans, tri);
        }

        return ans;
    }
};
```

### Complexity
- **Time Complexity**: $\mathcal{O}(N)$ — Single pass over `nums`.
- **Space Complexity**: $\mathcal{O}(1)$ — Constant scalar state variables.

---

## 3. Circular Defense (The Turret / Tower Range Cover)

### Problem Essence & Key Invariants
- $N$ defense towers arranged in a circle $0 \dots N-1$. Tower $i$ has range $R[i]$.
- Active tower $i$ covers all towers at distance $\le R[i]$ clockwise and counter-clockwise.
- Find the **minimum number of active towers** to neutralize all $N$ towers.
- Note: Power $P[i]$ is ignored (coverage count is what is minimized).

### OA Mental Model & Intuition (How to Remember Fast)
- **Fast Exit**: If any tower has $2 \cdot R[i] + 1 \ge N$, output `1`.
- **Circular Interval Covering $\to$ Doubling / Binary Lifting**:
  - Linearize the circle by duplicating it 3 times (length $3N$).
  - For each tower $i$ in period $k \in \{0, 1, 2\}$, center is $c = i + k \cdot N$. It covers interval $[c - R[i], c + R[i]]$.
  - Record the farthest reach: `jump[max(0, c - R[i])] = max(..., c + R[i] + 1)`.
  - Prefix max: `jump[x] = max(jump[x], jump[x - 1])`.
  - Precompute 2D jump table `up[k][x]` (position after $2^k$ jumps).
  - For each starting position $i \in [0, N-1]$, use binary lifting to count minimum jumps to reach $\ge i + N$. Take the minimum across all $i$.

### Step-by-Step Algorithm
1. Read $N$ and ranges $R[0 \dots N-1]$. Check if any $2 R[i] + 1 \ge N$; if so, return 1.
2. Initialize array `jump[0 ... 3N]` with `jump[x] = x`.
3. For each $i \in [0, N-1]$ and repetition $k \in \{0, 1, 2\}$:
   - $c = i + k \cdot N$, left $= \max(0, c - R[i])$, right $= \min(3N, c + R[i] + 1)$.
   - `jump[left] = max(jump[left], right)`.
4. Prefix-max scan: `jump[x] = max(jump[x], jump[x - 1])`.
5. Build binary lifting table `up[log][3N + 1]` with `log = 20`.
6. For each start $i \in [0, N-1]$:
   - Target is $i + N$. Lift using powers of 2 while `up[k][curr] < target`.
   - Take 1 final jump: `curr = jump[curr]`. If `curr >= target`, minimize `ans`.
7. Return `ans`.

### Optimal C++ Solution
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solveCircularDefense(int n, const vector<int>& r) {
    // 1-tower full coverage check
    for (int x : r) {
        if (2LL * x + 1 >= n) return 1;
    }

    int maxp = 3 * n;
    vector<int> jump(maxp + 1);
    for (int i = 0; i <= maxp; i++) jump[i] = i;

    // Farthest coverage per starting boundary
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < 3; k++) {
            int c = i + n * k;
            int l = max(0, c - r[i]);
            int rr = min(maxp, c + r[i] + 1);
            if (l <= maxp) jump[l] = max(jump[l], rr);
        }
    }

    // Prefix max to ensure monotonicity
    for (int i = 1; i <= maxp; i++) {
        jump[i] = max(jump[i], jump[i - 1]);
    }

    // Binary lifting table
    const int LOG = 20;
    vector<vector<int>> up(LOG, vector<int>(maxp + 1));
    up[0] = jump;
    for (int k = 1; k < LOG; k++) {
        for (int i = 0; i <= maxp; i++) {
            up[k][i] = up[k - 1][up[k - 1][i]];
        }
    }

    int ans = 1e9;
    for (int i = 0; i < n; i++) {
        int curr = i;
        int target = curr + n;
        int steps = 0;

        if (up[LOG - 1][curr] < target) continue;

        for (int k = LOG - 1; k >= 0; k--) {
            if (up[k][curr] < target) {
                steps += (1 << k);
                curr = up[k][curr];
            }
        }
        curr = jump[curr];
        steps++;

        if (curr >= target) ans = min(ans, steps);
    }

    return (ans > n) ? -1 : ans;
}
```

### Complexity
- **Time Complexity**: $\mathcal{O}(N \log N)$ — Binary lifting table construction and query.
- **Space Complexity**: $\mathcal{O}(N \log N)$ — $\approx 20 \times 3N$ integers.

---

## 4. Multi-GPU Priority Scheduling (Problem Set 3 — Q1)

### Problem Essence & Key Invariants
- $N$ processes on $G$ identical GPUs.
- Each process has: arrival time $a$, duration $d$, priority $pr$.
- Selection order when a GPU is free:
  1. Highest priority (`priority` descending)
  2. Smallest arrival time (`arrival_time` ascending)
  3. Smallest process ID (`id` ascending)
- Non-preemptive. Output: completion time for each process, and overall average waiting time to 4 decimal places.

### OA Mental Model & Intuition (How to Remember Fast)
- **Two Priority Queues + Discrete Event Simulation**:
  - `q` (Ready Queue): Max-heap storing arrived processes: `tuple<pr, -a, -id, d>`.
  - `runq` (Running GPUs): Min-heap storing finish times of executing tasks (size $\le G$).
  - Advance `time` directly to $\min(\text{next\_arrival}, \text{earliest\_finish})$.
  - Start jobs on free GPUs: finish $= time + d$, waiting time $= time - a$.

### Step-by-Step Algorithm
1. Sort processes by arrival time $a$.
2. Maintain `time = 0`, `done = 0`, `totwait = 0`.
3. While `done < N`:
   - Push all processes with $a \le time$ into ready queue `q`.
   - Free GPUs by popping tasks from `runq` whose finish time $\le time$.
   - While `!q.empty()` and `runq.size() < G`:
     - Pop top process, assign to GPU: finish $= time + d$.
     - Record completion time, add $(time - a)$ to `totwait`.
     - Push finish time into `runq` (if $d > 0$).
   - Advance `time`: if GPUs are full, jump to `runq.top()`; if ready queue is empty, jump to next arriving process.
4. Output each completion time, then `totwait / N` with 4 decimal places.

### Optimal C++ Solution
```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <iomanip>
#include <algorithm>
#include <climits>
using namespace std;

using ll = long long;

void solveMultiGPUScheduling() {
    int n, g;
    if (!(cin >> n >> g)) return;

    // {arrival, duration, priority, original_id}
    vector<tuple<ll, ll, ll, int>> p(n);
    for (int i = 0; i < n; i++) {
        ll a, d, pr;
        cin >> a >> d >> pr;
        p[i] = {a, d, pr, i};
    }
    sort(p.begin(), p.end());

    // Ready queue: max-heap on (priority, -arrival, -id)
    priority_queue<tuple<ll, ll, int, ll>> q;
    // GPU busy queue: min-heap of completion times
    priority_queue<ll, vector<ll>, greater<ll>> runq;

    int i = 0, done = 0;
    ll totwait = 0, cur_time = 0;
    vector<ll> completion(n);
    const ll INF = LLONG_MAX - 1;

    while (done < n) {
        while (i < n && get<0>(p[i]) <= cur_time) {
            auto [a, d, pr, id] = p[i];
            q.push({pr, -a, -id, d});
            i++;
        }

        while (!runq.empty() && runq.top() <= cur_time) {
            runq.pop();
        }

        while (!q.empty() && (int)runq.size() < g) {
            auto [pr, na, ni, d] = q.top();
            q.pop();
            ll a = -na;
            int id = -ni;

            ll finish = cur_time + d;
            completion[id] = finish;
            totwait += (cur_time - a);
            done++;

            if (d > 0) runq.push(finish);
        }

        ll next_a = (i < n) ? get<0>(p[i]) : INF;
        ll next_d = runq.empty() ? INF : runq.top();

        if (done < n) {
            if ((int)runq.size() == g || q.empty()) {
                cur_time = min(next_a, next_d);
            }
        }
    }

    for (ll c : completion) cout << c << "\n";
    cout << fixed << setprecision(4) << ((long double)totwait) / n << "\n";
}
```

### Complexity
- **Time Complexity**: $\mathcal{O}(N \log N + N \log G)$ — Sorting and heap push/pops.
- **Space Complexity**: $\mathcal{O}(N)$ — Queues and result storage.

---

## 5. Maximum CTR Advertisement (Problem Set 3 — Q2)

### Problem Essence & Key Invariants
- $N$ records: `(Ad_ID, Impressions, Clicks)`.
- Aggregate total impressions and clicks per `Ad_ID`.
- Filter: **Only eligible if total impressions $> 100$**.
- $CTR = (\text{Total Clicks} / \text{Total Impressions}) \times 100$, floored to 4 decimal places.
- Maximize CTR; break ties with **lexicographically smallest** `Ad_ID`.

### OA Mental Model & Intuition (How to Remember Fast)
- **Zero Floating-Point Precision Error**:
  - Compare two candidates $A$ and $B$ via exact 128-bit cross-multiplication:
    $C_A \cdot I_B > C_B \cdot I_A$.
  - Tie-breaker: If cross products are equal, pick $ID_A < ID_B$.
- **Exact Floored Formatting**:
  - $CTR \times 10^4 = \lfloor \frac{C \cdot 10^6}{I} \rfloor$.
  - Integer arithmetic: `val = (C * 1000000LL) / I`.
  - Print integer part `val / 10000` + `.` + 4-digit zero-padded `val % 10000`.

### Step-by-Step Algorithm
1. Aggregate inputs into `unordered_map<string, pair<ll, ll>>`.
2. Filter entries with `impressions > 100`.
3. Pick the best candidate using cross-product comparison:
   $C_1 \cdot I_2 > C_2 \cdot I_1$, with string comparison as fallback.
4. Output `best_id` and floored CTR via integer formatting.

### Optimal C++ Solution
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iomanip>
using namespace std;

using ll = long long;

void solveMaxCTR() {
    int n;
    if (!(cin >> n)) return;

    unordered_map<string, pair<ll, ll>> stats; // id -> {impressions, clicks}
    for (int i = 0; i < n; i++) {
        string id;
        ll imp, clk;
        cin >> id >> imp >> clk;
        stats[id].first += imp;
        stats[id].second += clk;
    }

    string best_id = "";
    ll best_imp = 1, best_clk = -1;

    for (const auto& [id, data] : stats) {
        ll imp = data.first;
        ll clk = data.second;
        if (imp <= 100) continue;

        if (best_id == "") {
            best_id = id;
            best_imp = imp;
            best_clk = clk;
            continue;
        }

        // Compare clk / imp vs best_clk / best_imp using cross multiplication
        __int128 lhs = (__int128)clk * best_imp;
        __int128 rhs = (__int128)best_clk * imp;

        if (lhs > rhs || (lhs == rhs && id < best_id)) {
            best_id = id;
            best_imp = imp;
            best_clk = clk;
        }
    }

    // Floored to 4 decimal places
    ll scaled = (best_clk * 1000000LL) / best_imp;
    ll int_part = scaled / 10000;
    ll frac_part = scaled % 10000;

    cout << best_id << " " << int_part << "." 
         << setw(4) << setfill('0') << frac_part << "\n";
}
```

### Complexity
- **Time Complexity**: $\mathcal{O}(N \cdot L)$ where $L$ is string length.
- **Space Complexity**: $\mathcal{O}(U \cdot L)$ for $U$ unique IDs.

---

## 6. Sum of Maximums of All Subarrays (Problem Set 3 — Q3)

### Problem Essence & Key Invariants
- Given array $A$ of size $N$ ($N \le 10^5, A[i] \le 10^9$).
- Window cost $= \max(A[L \dots R])$.
- Find $\sum_{L \le R} \max(A[L \dots R])$.

### OA Mental Model & Intuition (How to Remember Fast)
- **Monotonic Stack Contribution Technique**:
  - Instead of computing subarrays directly, calculate each element $A[i]$'s contribution.
  - Find `left[i]`: index of previous **strictly greater** element.
  - Find `right[i]`: index of next **greater or equal** element (asymmetry handles duplicates cleanly!).
  - Number of subarrays where $A[i]$ is the maximum $= (i - \text{left}[i]) \times (\text{right}[i] - i)$.
  - Total sum $= \sum A[i] \times (i - \text{left}[i]) \times (\text{right}[i] - i)$.

### Step-by-Step Algorithm
1. Maintain vector `left(n)` and `right(n)`.
2. Single-pass monotonic decreasing stack to compute `left[i]`.
3. Single-pass monotonic decreasing stack to compute `right[i]`.
4. Accumulate `A[i] * (i - left[i]) * (right[i] - i)` using `long long` (or `__int128` if sum $> 2^{63}-1$).

### Optimal C++ Solution
```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

using ll = long long;

ll sumOfSubarrayMaximums(const vector<ll>& a) {
    int n = a.size();
    vector<int> left(n), right(n);
    stack<int> st;

    // Previous strictly greater element
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] <= a[i]) st.pop();
        left[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }

    while (!st.empty()) st.pop();

    // Next greater or equal element
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && a[st.top()] < a[i]) st.pop();
        right[i] = st.empty() ? n : st.top();
        st.push(i);
    }

    __int128 total = 0;
    for (int i = 0; i < n; i++) {
        ll count = (ll)(i - left[i]) * (right[i] - i);
        total += (__int128)a[i] * count;
    }

    return (ll)total;
}
```

### Complexity
- **Time Complexity**: $\mathcal{O}(N)$ — Each index enters and leaves stack once.
- **Space Complexity**: $\mathcal{O}(N)$ — Left/right boundary arrays.

---

## 7. K-th Cheapest Pairing on a Generated Cost Grid (PDF Q1)

### Problem Essence & Key Invariants
- $N$ producers, $M$ consumers ($N, M \le 20000$).
- Strictly increasing sequences $X[0 \dots N-1]$ and $Y[0 \dots M-1]$ generated via LCG recurrence:
  $X[i] = X[i-1] + ((i \cdot A_x + B_x) \bmod C_x) + 1$
  $Y[j] = Y[j-1] + ((j \cdot A_y + B_y) \bmod C_y) + 1$
- Implicit grid $A[i][j] = X[i] + Y[j]$. Find $K$-th smallest pairing cost ($1 \le K \le N \cdot M$).

### OA Mental Model & Intuition (How to Remember Fast)
- **Binary Search on Value + 2-Pointer Count**:
  - The answer lies in $[X[0] + Y[0], X[N-1] + Y[M-1]]$.
  - For candidate value $V$, count pairs with $X[i] + Y[j] \le V$.
  - Since $X$ and $Y$ are sorted, start $j = M - 1$. As $i$ increases from $0 \dots N-1$, $j$ only moves left.
  - Count is evaluated in $\mathcal{O}(N + M)$ time per binary search iteration!

### Step-by-Step Algorithm
1. Generate arrays $X$ and $Y$ using 64-bit integers.
2. Binary search range: `low = X[0] + Y[0]`, `high = X[N-1] + Y[M-1]`.
3. Inside `check(V)`:
   - $j = M - 1$, `count = 0`.
   - For $i = 0 \dots N-1$:
     - While $j \ge 0$ and $X[i] + Y[j] > V$, $j--$.
     - `count += (j + 1)`.
   - Return `count >= K`.
4. If `check(mid)` is true: `ans = mid`, `high = mid - 1`. Else `low = mid + 1`.

### Optimal C++ Solution
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ll = long long;

ll solveKthCheapestPairing(int n, int m, ll k,
                          ll x0, ll ax, ll bx, ll cx,
                          ll y0, ll ay, ll by, ll cy) {
    vector<ll> x(n), y(m);
    x[0] = x0;
    for (int i = 1; i < n; i++) {
        x[i] = x[i - 1] + ((1LL * i * ax + bx) % cx) + 1;
    }
    y[0] = y0;
    for (int j = 1; j < m; j++) {
        y[j] = y[j - 1] + ((1LL * j * ay + by) % cy) + 1;
    }

    ll low = x[0] + y[0];
    ll high = x[n - 1] + y[m - 1];
    ll ans = high;

    auto countLessEqual = [&](ll target) -> ll {
        ll cnt = 0;
        int j = m - 1;
        for (int i = 0; i < n; i++) {
            while (j >= 0 && x[i] + y[j] > target) {
                j--;
            }
            cnt += (j + 1);
        }
        return cnt;
    };

    while (low <= high) {
        ll mid = low + (high - low) / 2;
        if (countLessEqual(mid) >= k) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return ans;
}
```

### Complexity
- **Time Complexity**: $\mathcal{O}((N + M) \log(\text{Range}))$ — $\approx 40,000 \times 60 \approx 2.4 \times 10^6$ ops (runs in $\approx 15$ ms).
- **Space Complexity**: $\mathcal{O}(N + M)$ — For generated $X$ and $Y$ arrays.

---

## 8. Consensus Median of Three Gel Reports (PDF Q2)

### Problem Essence & Key Invariants
- 3 pre-sorted arrays of lengths $n_1, n_2, n_3$ ($n_1 + n_2 + n_3 \le 20000$).
- Find median of combined multiset. Format with exactly 1 decimal digit (`5.0`, `35.0`).

### OA Mental Model & Intuition (How to Remember Fast)
- **3-Way Two-Pointer Merge Scan**:
  - Total length $T = n_1 + n_2 + n_3$.
  - Median elements are at index $T/2$ (and $T/2 - 1$ if $T$ is even).
  - Walk 3 pointers to step $T/2$, tracking current and previous element.
  - Absolutely zero external sorting or floating point overhead.

### Step-by-Step Algorithm
1. Pointers $p_1 = 0, p_2 = 0, p_3 = 0$.
2. Loop $step$ from 0 to $T/2$:
   - `prev = curr`.
   - Pick minimum among available headers: $v_1[p_1], v_2[p_2], v_3[p_3]$. Advance that pointer.
3. If $T$ is odd: return `curr`.
4. If $T$ is even: return `(prev + curr) / 2.0`.

### Optimal C++ Solution
```cpp
#include <iostream>
#include <vector>
#include <iomanip>
#include <climits>
using namespace std;

double findConsensusMedian(const vector<int>& a, const vector<int>& b, const vector<int>& c) {
    int n1 = a.size(), n2 = b.size(), n3 = c.size();
    int total = n1 + n2 + n3;
    int p1 = 0, p2 = 0, p3 = 0;
    int prev_val = 0, curr_val = 0;

    for (int step = 0; step <= total / 2; step++) {
        prev_val = curr_val;
        int val1 = (p1 < n1) ? a[p1] : INT_MAX;
        int val2 = (p2 < n2) ? b[p2] : INT_MAX;
        int val3 = (p3 < n3) ? c[p3] : INT_MAX;

        if (val1 <= val2 && val1 <= val3) {
            curr_val = val1;
            p1++;
        } else if (val2 <= val1 && val2 <= val3) {
            curr_val = val2;
            p2++;
        } else {
            curr_val = val3;
            p3++;
        }
    }

    if (total % 2 == 1) {
        return (double)curr_val;
    } else {
        return (prev_val + curr_val) / 2.0;
    }
}
```

### Complexity
- **Time Complexity**: $\mathcal{O}(n_1 + n_2 + n_3)$ — $\le 10,000$ iterations.
- **Space Complexity**: $\mathcal{O}(1)$ — Three pointer variables.

---

## 9. Stamped Code Mold Families (PDF Q3)

### Problem Essence & Key Invariants
- $n$ strings ($n \le 1000$, length $\le 12$).
- Two codes $X$ and $Y$ are compatible if deleting at most 1 char from one (or none) makes them anagrams:
  - $|X| == |Y|$: must be exact anagrams (no deletion permitted).
  - $|X| == |Y| + 1$: deleting 1 char from $X$ yields anagram of $Y$.
  - $|X| + 1 == |Y|$: deleting 1 char from $Y$ yields anagram of $X$.
- Group into connected components (families). Preserve input order.

### OA Mental Model & Intuition (How to Remember Fast)
- **Letter Frequency Vector + Graph Connected Components**:
  - Count frequencies of all 26 uppercase letters for each string.
  - To check compatibility in $\mathcal{O}(26)$:
    - If $|X| == |Y|$: frequency vectors must be identical.
    - If $|X| == |Y| + 1$: $X$ count $\ge Y$ count for all letters, with exactly one difference $+1$.
  - Build adjacency list and extract components using BFS in input order.

### Optimal C++ Solution
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

bool isCompatible(const string& a, const vector<int>& cntA,
                  const string& b, const vector<int>& cntB) {
    int la = a.size(), lb = b.size();
    if (abs(la - lb) > 1) return false;

    if (la == lb) {
        return cntA == cntB;
    }
    // Assume la == lb + 1
    const auto& big = (la > lb) ? cntA : cntB;
    const auto& small = (la > lb) ? cntB : cntA;
    int diff = 0;
    for (int i = 0; i < 26; i++) {
        if (big[i] < small[i]) return false;
        diff += (big[i] - small[i]);
    }
    return diff == 1;
}

void solveMoldFamilies() {
    int n;
    if (!(cin >> n)) return;

    vector<string> codes(n);
    vector<vector<int>> cnt(n, vector<int>(26, 0));
    for (int i = 0; i < n; i++) {
        cin >> codes[i];
        for (char c : codes[i]) cnt[i][c - 'A']++;
    }

    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (isCompatible(codes[i], cnt[i], codes[j], cnt[j])) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    vector<bool> visited(n, false);
    vector<vector<string>> families;

    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;
        vector<int> comp;
        queue<int> q;
        q.push(i);
        visited[i] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            comp.push_back(u);

            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }

        // Sort by original input index to preserve appearance order
        sort(comp.begin(), comp.end());
        vector<string> fam;
        for (int idx : comp) fam.push_back(codes[idx]);
        families.push_back(fam);
    }

    cout << families.size() << "\n";
    for (const auto& fam : families) {
        for (size_t k = 0; k < fam.size(); k++) {
            cout << fam[k] << (k + 1 == fam.size() ? "" : " ");
        }
        cout << "\n";
    }
}
```

### Complexity
- **Time Complexity**: $\mathcal{O}(n^2 \cdot 26)$ — For $n = 1000$, $\approx 1.3 \times 10^7$ ops ($< 25$ ms).
- **Space Complexity**: $\mathcal{O}(n^2)$ — Graph adjacency list.

---

## 10. Course Schedule III (PDF Q4)

### Problem Essence & Key Invariants
- $n$ courses, each $[duration_i, lastDay_i]$.
- Take one course at a time without overlap. Finished on or before $lastDay_i$.
- Maximize total courses scheduled.

### OA Mental Model & Intuition (How to Remember Fast)
- **Greedy Deadline Sort + Max-Heap Duration Swap**:
  - Sort courses by deadline $lastDay$ ascending.
  - Maintain `time` and a max-heap of durations of accepted courses.
  - If `time + duration <= lastDay`: accept course (`time += duration`, push `duration`).
  - Else if `duration < heap.top()`: replace the previously accepted longest course with this one (`time += duration - heap.top()`, pop, push `duration`).
  - Size of max-heap is the answer!

### Optimal C++ Solution
```cpp
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        // Sort by deadline ascending
        sort(courses.begin(), courses.end(), [](const auto& a, const auto& b) {
            return a[1] < b[1];
        });

        priority_queue<int> max_heap; // durations of chosen courses
        int total_time = 0;

        for (const auto& c : courses) {
            int dur = c[0];
            int last = c[1];

            if (total_time + dur <= last) {
                total_time += dur;
                max_heap.push(dur);
            } else if (!max_heap.empty() && max_heap.top() > dur) {
                total_time += dur - max_heap.top();
                max_heap.pop();
                max_heap.push(dur);
            }
        }

        return max_heap.size();
    }
};
```

### Complexity
- **Time Complexity**: $\mathcal{O}(n \log n)$ — Deadline sort and heap operations.
- **Space Complexity**: $\mathcal{O}(n)$ — Priority queue.

---

## 11. JoJo The Perfectionist (PDF Q5)

### Problem Essence & Key Invariants
- Queue $A$ of $X$ boys, Queue $B$ of $Y$ girls ($X \ge Y$).
- Pad $B$ with $X - Y$ zero-height girls anywhere.
- Maximize $\sum_{i=0}^{X-1} A[i] \times B'[i]$. Relative order of real girls is fixed.
- Equivalent to selecting an increasing subsequence of $Y$ indices from $A$ to match with $B$.

### OA Mental Model & Intuition (How to Remember Fast)
- **Subsequence Alignment DP**:
  - $dp[j]$ = max unity matching first $j$ girls.
  - For each boy $i \in [1 \dots X]$:
    - Girl $j \in [\min(i, Y) \dots 1]$:
      `dp[j] = max(dp[j], dp[j - 1] + 1LL * A[i - 1] * B[j - 1])`
  - Answer is $dp[Y]$.

### Optimal C++ Solution
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ll = long long;

ll solveJoJoPerfectionist(int x, int y, const vector<ll>& a, const vector<ll>& b) {
    // dp[j]: max unity using j girls
    vector<ll> dp(y + 1, 0);

    for (int i = 1; i <= x; i++) {
        for (int j = min(i, y); j >= 1; j--) {
            dp[j] = max(dp[j], dp[j - 1] + a[i - 1] * b[j - 1]);
        }
    }

    return dp[y];
}
```

### Complexity
- **Time Complexity**: $\mathcal{O}(X \cdot Y)$ — $\le 500 \times 500 = 2.5 \times 10^5$ operations per test case.
- **Space Complexity**: $\mathcal{O}(Y)$ — 1D DP table.

---

## 12. Minimum Time to Transport All Individuals (PDF Q6)

### Problem Essence & Key Invariants
- $n$ individuals ($n \le 12$), boat capacity $k$, cyclic stages $m \le 5$, multipliers $mul[0 \dots m-1]$.
- Outbound group takes $\max(time[S]) \times mul[stage]$, stage advances by $\lfloor d \rfloor \bmod m$.
- Return trip requires 1 person from destination, taking $time[r] \times mul[stage]$.
- Find minimum total time to transport everyone to destination.

### OA Mental Model & Intuition (How to Remember Fast)
- **Dijkstra on Small State Space**:
  - State: `(mask, stage, boat)`:
    - `mask`: bitmask of people at base camp ($0 \dots 2^n - 1$).
    - `stage`: current environment cycle ($0 \dots m - 1$).
    - `boat`: $0$ (at base) or $1$ (at destination).
  - Total states: $2^{12} \times 5 \times 2 = 40,960$.
  - Run Dijkstra using `priority_queue<pair<double, State>>`.
  - On return trip: always pick the fastest available person at destination.

### Optimal C++ Solution
```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <iomanip>
using namespace std;

struct State {
    int mask;
    int stage;
    int boat; // 0: base, 1: dest
};

double minTimeToTransport(int n, int k, int m,
                          const vector<int>& time,
                          const vector<double>& mul) {
    int total_masks = (1 << n);
    // dist[mask][stage][boat]
    vector<vector<vector<double>>> dist(total_masks,
        vector<vector<double>>(m, vector<double>(2, 1e18)));

    using Node = pair<double, int>; // {time, encoded_state}
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    int start_state = ((total_masks - 1) << 4) | (0 << 1) | 0;
    dist[total_masks - 1][0][0] = 0.0;
    pq.push({0.0, start_state});

    while (!pq.empty()) {
        auto [d, state] = pq.top();
        pq.pop();

        int boat = state & 1;
        int stage = (state >> 1) & 7;
        int mask = state >> 4;

        if (d > dist[mask][stage][boat]) continue;
        if (mask == 0 && boat == 1) return d;

        if (boat == 0) {
            // Pick subset S of size 1..k from mask
            for (int sub = mask; sub > 0; sub = (sub - 1) & mask) {
                int sz = __builtin_popcount(sub);
                if (sz < 1 || sz > k) continue;

                int max_t = 0;
                for (int i = 0; i < n; i++) {
                    if ((sub >> i) & 1) max_t = max(max_t, time[i]);
                }

                double trip_t = max_t * mul[stage];
                int next_stage = (stage + (int)floor(trip_t)) % m;
                int next_mask = mask ^ sub;

                if (next_mask == 0) {
                    // Everyone delivered!
                    if (d + trip_t < dist[0][next_stage][1]) {
                        dist[0][next_stage][1] = d + trip_t;
                        pq.push({d + trip_t, (0 << 4) | (next_stage << 1) | 1});
                    }
                } else {
                    if (d + trip_t < dist[next_mask][next_stage][1]) {
                        dist[next_mask][next_stage][1] = d + trip_t;
                        pq.push({d + trip_t, (next_mask << 4) | (next_stage << 1) | 1});
                    }
                }
            }
        } else {
            // Exactly 1 person from destination returns boat
            int dest_mask = ((total_masks - 1) ^ mask);
            for (int r = 0; r < n; r++) {
                if ((dest_mask >> r) & 1) {
                    double ret_t = time[r] * mul[stage];
                    int next_stage = (stage + (int)floor(ret_t)) % m;
                    int next_mask = mask | (1 << r);

                    if (d + ret_t < dist[next_mask][next_stage][0]) {
                        dist[next_mask][next_stage][0] = d + ret_t;
                        pq.push({d + ret_t, (next_mask << 4) | (next_stage << 1) | 0});
                    }
                }
            }
        }
    }

    return -1.0;
}
```

### Complexity
- **Time Complexity**: $\mathcal{O}(2^n \cdot \binom{n}{k} \cdot m \log(\text{States}))$ — Milliseconds for $n \le 12$.
- **Space Complexity**: $\mathcal{O}(2^n \cdot m)$ — $40,960$ states.

---

## 13. Dynamic Tree Path Sum (PDF Q7)

### Problem Essence & Key Invariants
- Rooted tree at node 1 with $n$ nodes, $q$ queries ($n, q \le 2 \times 10^5$).
- Node $i$ holds value $v_i$.
- Queries:
  - `1 s x`: Update value of node $s$ to $x$.
  - `2 s`: Query path sum from root to node $s$.

### OA Mental Model & Intuition (How to Remember Fast)
- **Euler Tour Subtree Flattening + Range Add Point Query Fenwick**:
  - When node $s$ updates by $\Delta = x - v_s$, every node in $s$'s subtree has its root-to-node path sum increased by $\Delta$.
  - Subtree of $s$ corresponds to contiguous interval $[in[s], out[s]]$ in DFS entry-exit order.
  - Fenwick tree:
    - Range update $[in[s], out[s]]$ with $+\Delta$.
    - Point query at $in[s]$ gives the root path sum!
  - **Critical Stack Overflow Avoidance**: Iterative DFS for tree traversal up to $2 \times 10^5$ nodes.

### Optimal C++ Solution
```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

using ll = long long;

struct Fenwick {
    int n;
    vector<ll> tree;
    Fenwick(int n) : n(n), tree(n + 2, 0) {}

    void add(int i, ll delta) {
        for (; i <= n; i += i & -i) tree[i] += delta;
    }
    void rangeAdd(int l, int r, ll delta) {
        add(l, delta);
        add(r + 1, -delta);
    }
    ll pointQuery(int i) {
        ll sum = 0;
        for (; i > 0; i -= i & -i) sum += tree[i];
        return sum;
    }
};

void solveDynamicTreePathSum() {
    int n, q;
    if (!(cin >> n >> q)) return;

    vector<ll> val(n + 1);
    for (int i = 1; i <= n; i++) cin >> val[i];

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Iterative DFS to prevent stack overflow
    vector<int> in_time(n + 1), out_time(n + 1);
    vector<int> edge_idx(n + 1, 0);
    vector<int> parent(n + 1, 0);
    int timer = 0;

    stack<int> st;
    st.push(1);
    in_time[1] = ++timer;

    while (!st.empty()) {
        int u = st.top();
        if (edge_idx[u] < (int)adj[u].size()) {
            int v = adj[u][edge_idx[u]++];
            if (v != parent[u]) {
                parent[v] = u;
                in_time[v] = ++timer;
                st.push(v);
            }
        } else {
            out_time[u] = timer;
            st.pop();
        }
    }

    Fenwick bit(n);
    for (int i = 1; i <= n; i++) {
        bit.rangeAdd(in_time[i], out_time[i], val[i]);
    }

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int s;
            ll x;
            cin >> s >> x;
            ll delta = x - val[s];
            val[s] = x;
            bit.rangeAdd(in_time[s], out_time[s], delta);
        } else {
            int s;
            cin >> s;
            cout << bit.pointQuery(in_time[s]) << "\n";
        }
    }
}
```

### Complexity
- **Time Complexity**: $\mathcal{O}((n + q) \log n)$ — Fast bitwise updates and queries.
- **Space Complexity**: $\mathcal{O}(n)$ — Flattening tables and Fenwick tree.

---

## 14. City Skyline — Zoning Laws, Construction Decrees & Audits (PDF Q8)

### Problem Essence & Key Invariants
- $N$ skyscrapers, $Q$ operations ($N, Q \le 5000$).
- Event 1: `1 L R X` $\implies A[i] = \min(A[i], X)$ for $i \in [L, R]$.
- Event 2: `2 L R Y` $\implies A[i] = A[i] + Y$ for $i \in [L, R]$.
- Event 3: `3 L R` $\implies$ Query $\sum_{i=L}^R A[i]$.
- Max height can reach $5 \times 10^{11}$, total sum up to $2.5 \times 10^{15}$.

### OA Mental Model & Intuition (How to Remember Fast)
- **Constraints are $N, Q \le 5000$**:
  - A direct 64-bit array loop has at most $5000 \times 5000 = 2.5 \times 10^7$ iterations.
  - In C++, $2.5 \times 10^7$ simple operations takes $< 0.05$ seconds.
  - Writing complex Segment Tree Beats in an OA is a high-risk trap; straightforward array simulation is 100% bug-free and comfortably passes.

### Optimal C++ Solution
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ll = long long;

void solveCitySkyline() {
    int n, q;
    if (!(cin >> n >> q)) return;

    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    while (q--) {
        int type, l, r;
        cin >> type >> l >> r;
        if (type == 1) {
            ll x;
            cin >> x;
            for (int i = l; i <= r; i++) {
                if (a[i] > x) a[i] = x;
            }
        } else if (type == 2) {
            ll y;
            cin >> y;
            for (int i = l; i <= r; i++) {
                a[i] += y;
            }
        } else {
            ll sum = 0;
            for (int i = l; i <= r; i++) {
                sum += a[i];
            }
            cout << sum << "\n";
        }
    }
}
```

### Complexity
- **Time Complexity**: $\mathcal{O}(N \cdot Q) \approx 2.5 \times 10^7$ ops — $< 50$ ms.
- **Space Complexity**: $\mathcal{O}(N)$ — Array of heights.

---

## 15. Array Reduction via MEX — Lexicographically Largest Result (PDF Q9)

### Problem Essence & Key Invariants
- Repeatedly take prefix of length $k$, append its MEX to `result`, remove prefix.
- Goal: Make `result` **lexicographically largest**.
- (Codeforces 1628A — Meximum Array).

### OA Mental Model & Intuition (How to Remember Fast)
- **Greedy Suffix MEX**:
  - The first element of `result` can never exceed the MEX of the entire remaining array.
  - To maximize subsequent elements, consume the **shortest prefix** that achieves this target MEX.
  - Track remaining frequencies of all numbers. Target $M$ is the first number with remaining count 0.
  - Scan prefix from left, marking numbers $< M$ seen. The moment all $0 \dots M-1$ have appeared, terminate prefix!

### Optimal C++ Solution
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> meximumArray(const vector<int>& arr) {
    int n = arr.size();
    vector<int> count(n + 2, 0);
    for (int x : arr) {
        if (x <= n + 1) count[x]++;
    }

    int mex = 0;
    while (count[mex] > 0) mex++;

    vector<int> result;
    vector<bool> seen(mex + 1, false);
    int seen_count = 0;
    int cur_mex = mex;

    int l = 0;
    while (l < n) {
        if (cur_mex == 0) {
            result.push_back(0);
            if (arr[l] <= n + 1) count[arr[l]]--;
            l++;
            continue;
        }

        fill(seen.begin(), seen.begin() + cur_mex, false);
        seen_count = 0;
        int r = l;

        while (r < n && seen_count < cur_mex) {
            int val = arr[r];
            if (val <= n + 1) count[val]--;
            if (val < cur_mex && !seen[val]) {
                seen[val] = true;
                seen_count++;
            }
            r++;
        }

        result.push_back(cur_mex);
        l = r;

        // Recalculate remaining MEX
        while (cur_mex > 0 && count[cur_mex - 1] == 0) {
            cur_mex--;
        }
        while (count[cur_mex] > 0) cur_mex++;
    }

    return result;
}
```

### Complexity
- **Time Complexity**: $\mathcal{O}(N)$ — Each element is scanned once and frequency amortized.
- **Space Complexity**: $\mathcal{O}(N)$ — Frequency and seen tracking.

---

## 16. Delivery Service — Count Impossible City Pairs (PDF Q10)

### Problem Essence & Key Invariants
- $N$ cities, $2N$ shift-nodes (Morning: $1 \dots N$, Afternoon: $N+1 \dots 2N$).
- Free move: Morning $i \implies$ Afternoon $i + N$ for every city.
- $M$ directed courier routes.
- Delivery $(u, v)$ is possible $\iff$ Morning $u$ can reach Afternoon $v + N$.
- Count pairs $(u, v)$ whose delivery is **impossible** $= N^2 - \text{Total Possible Pairs}$.

### OA Mental Model & Intuition (How to Remember Fast)
- **Reachability from Morning to Afternoon Nodes**:
  - Reaching either shift of city $v$ allows delivery, and Morning $v$ always reaches Afternoon $v+N$.
  - Thus, city $v$ is reachable from $u \iff$ Morning $u$ can reach Afternoon $v+N$.
  - With $N \le 20000$ and $M \le 15000$, standard individual BFS is $\mathcal{O}(N(V + E))$.
  - We optimize with **Chunked BFS using `std::bitset`** (batching 2048 cities at a time).
  - Bit-parallel operations accelerate reachability calculations by $64\times$!

### Optimal C++ Solution
```cpp
#include <iostream>
#include <vector>
#include <bitset>
#include <queue>
using namespace std;

using ll = long long;

const int CHUNK = 2048;

ll countImpossibleCityPairs() {
    int n, m;
    if (!(cin >> n >> m)) return 0;

    int total_nodes = 2 * n;
    vector<vector<int>> adj(total_nodes + 1);

    // Free Morning -> Afternoon transitions
    for (int i = 1; i <= n; i++) {
        adj[i].push_back(i + n);
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    ll possible_pairs = 0;

    // Process Morning cities in chunks of size CHUNK
    for (int chunk_start = 1; chunk_start <= n; chunk_start += CHUNK) {
        int chunk_end = min(n, chunk_start + CHUNK - 1);
        int cur_chunk_size = chunk_end - chunk_start + 1;

        vector<bitset<CHUNK>> reachable(total_nodes + 1);
        vector<bool> in_queue(total_nodes + 1, false);
        queue<int> q;

        for (int i = chunk_start; i <= chunk_end; i++) {
            reachable[i].set(i - chunk_start);
            q.push(i);
            in_queue[i] = true;
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            in_queue[u] = false;

            for (int v : adj[u]) {
                if ((reachable[u] & ~reachable[v]).any()) {
                    reachable[v] |= reachable[u];
                    if (!in_queue[v]) {
                        q.push(v);
                        in_queue[v] = true;
                    }
                }
            }
        }

        // Count reachable afternoon nodes (j + n)
        for (int j = 1; j <= n; j++) {
            possible_pairs += reachable[j + n].count();
        }
    }

    ll total_pairs = 1LL * n * n;
    return total_pairs - possible_pairs;
}
```

### Complexity
- **Time Complexity**: $\mathcal{O}(\lceil N / \text{CHUNK} \rceil \cdot (V + E) \cdot \frac{\text{CHUNK}}{64})$ — Well within the 2.0s limit.
- **Space Complexity**: $\mathcal{O}(V \cdot \frac{\text{CHUNK}}{8})$ — $\approx 40,000 \times 256 \text{ bytes} \approx 10\text{ MB}$.
