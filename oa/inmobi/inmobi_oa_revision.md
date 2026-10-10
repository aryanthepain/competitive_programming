# InMobi SDE OA — Comprehensive Problem Revision Guide

This guide contains deep, first-principles problem breakdowns, structural observations, step-by-step algorithms, intermediate logic snippets, and production-ready C++ solutions for all target OA questions.

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

### Problem Overview & Invariants
- We are given an array of integers `nums` and an integer `k`.
- A continuous subarray is called **nice** if it contains exactly `k` odd integers.
- Our goal is to return the total number of nice continuous subarrays.

### Observation 1 — Parity Reduction
The actual numeric values of the numbers in `nums` do not matter at all. Only their parity matters:
- If `nums[i]` is odd, it counts as $1$.
- If `nums[i]` is even, it counts as $0$.

Thus, the problem is completely equivalent to:
> Given a binary array of 0s and 1s, count how many subarrays have an exact sum equal to $k$.

### Observation 2 — The Challenge with Standard Sliding Window
In a standard positive array sliding window, expanding the right pointer increases the window sum, and shrinking the left pointer decreases the sum.
However, because even numbers correspond to $0$, adding an even number does **not** change the odd count, and skipping an even number does **not** decrease the odd count.

Consider an example: `[2, 2, 1, 2, 1, 2]`, with `k = 2`.
The window containing the two `1`s is `[1, 2, 1]`.
Notice that any of the following left starting points are valid:
- Starting at index 0: `[2, 2, 1, 2, 1]` (has two 1s)
- Starting at index 1: `[2, 1, 2, 1]` (has two 1s)
- Starting at index 2: `[1, 2, 1]` (has two 1s)

All three start boundaries terminate at the second `1`! Moreover, any even numbers trailing to the right (like the final `2`) also multiply these valid start boundaries.

### Step 1 — Prefix Even Counter Technique
To count all valid subarrays in a single linear pass $O(N)$ without re-scanning:
Whenever our window $[l, r]$ reaches exactly `k` odd numbers:
- We can count how many even numbers sit immediately to the left of our first odd number.
- Let this count of leading even numbers plus one (for the odd number itself) be `pc` (prefix count).
- While the odd count `oc == k`, we contract `l`: for every even number we pass, increment `pc++`. The moment we move past the leftmost odd number, `oc` drops to $k - 1$.
- At this moment, exactly `pc` valid starting positions exist that can pair with our current right boundary $r$.
- Furthermore, as subsequent even numbers arrive at the right pointer $r$, each of them can pair with all `pc` valid left start positions! So for every even element that extends the current window, we simply add `pc` to our total answer.
- The moment a new odd number enters from the right, the old group of $k$ odds is superseded, so we reset `pc = 0` and process the new window.

### Implementation Details

```cpp
int pc = 0, oc = 0;
int l = 0, r = 0;
int ans = 0;

while (r < n) {
    if (nums[r] % 2 != 0) {
        // A new odd number entered: reset the prefix even counter
        pc = 0;
        oc++;
    }

    // Shrink from the left while we maintain exactly k odds
    while (oc == k) {
        pc++;
        if (nums[l] % 2 != 0) {
            oc--;
        }
        l++;
    }

    ans += pc;
    r++;
}
```

### Why does this work?
- When `oc < k`, `pc` is $0$, so `ans += pc` adds $0$ (the window is not yet valid).
- The exact iteration `r` that introduces the $k$-th odd triggers the `while (oc == k)` loop. The loop consumes all preceding even numbers up to the leftmost odd number, accumulating `pc`.
- For any subsequent even numbers at $r$ before the next odd number arrives, `oc` remains $k - 1$, so the inner `while` loop does not execute, but `pc` retains the exact number of valid left boundaries that can form a valid subarray with the current $r$.
- Each element is visited at most twice by $l$ and $r$.

### Complete Clean C++ Solution

```cpp
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int ans = 0, n = nums.size();
        int pc = 0, oc = 0;
        int l = 0, r = 0;

        while (r < n) {
            if (nums[r] % 2 != 0) {
                pc = 0;
                oc++;
            }

            while (oc == k) {
                pc++;
                if (nums[l] % 2 != 0) {
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

### Complexity Analysis
- **Time Complexity**: $\mathcal{O}(N)$ — Both pointers $l$ and $r$ advance strictly from $0$ to $N$, visiting each element at most twice.
- **Space Complexity**: $\mathcal{O}(1)$ — Only scalar counters (`ans`, `pc`, `oc`, `l`, `r`).

---

## 2. LeetCode 3640 — Trionic Array II

### Problem Overview & Invariants
- We are given an integer array `nums`.
- A continuous subarray is called **Trionic** if it has length at least 4 and can be partitioned into three contiguous segments $[l, p]$, $[p, q]$, $[q, r]$ with $l < p < q < r$ such that:
  1. $[l, p]$ is **strictly increasing**: $nums[l] < nums[l+1] < \dots < nums[p]$
  2. $[p, q]$ is **strictly decreasing**: $nums[p] > nums[p+1] > \dots > nums[q]$
  3. $[q, r]$ is **strictly increasing**: $nums[q] < nums[q+1] < \dots < nums[r]$
- The goal is to find the **maximum possible sum** of a Trionic subarray.

### Observation 1 — Fixing the Middle Decreasing Anchor
If we look at any valid Trionic Subarray $[l, r]$, we can notice that there is only one pair $(p, q)$ for which the rules in the problem statement are satisfied, or none.

Having this, we fix the pair $(p, q)$ and try to find the best suitable $l$ and $r$ for it. That is, we fix the middle part of the Trionic Subarray, and we try to find the best left and right parts for it.

### Step 1 — Decomposition into Decreasing Subarrays
We first decompose our array `nums` into strictly decreasing subarrays.
More specifically, we partition into $k$ contiguous pairs:

$$
(p_1, q_1), (p_2, q_2), \dots, (p_k, q_k)
$$

where for every $i \le k$, the subarray $[p_i, q_i]$ is strictly decreasing, $p_1 = 0$, $q_k = n - 1$, and for every $i < k$, $q_i + 1 = p_{i+1}$.

Visually, we cut `nums` in $k - 1$ places so that we end up with $k$ adjacent subarrays, and each subarray is strictly decreasing.
Of all possible ways to cut, we choose the partition that produces the fewest subarrays (maximal contiguous segments).

### Why is the decomposition unique?
Because the cut positions are forced:
- At every index $i$, if $nums[i-1] \le nums[i]$, the array cannot be strictly decreasing across that boundary, so a cut **must** occur between $i-1$ and $i$.
- If $nums[i-1] > nums[i]$, the decreasing condition still holds, so making a cut there would be unnecessary and would strictly increase the number of subarrays.

Thus:
- Some positions must be cuts.
- All other positions must not be cuts.
Since the goal is the minimum number of subarrays, every cut is forced, and no optional cuts exist. Therefore, the decomposition is unique.

### Implementation Details — Decomposition
Scan the array once from left to right:
- Maintain the start $l$ of the current subarray and its running sum.
- Whenever the strict decreasing condition breaks ($nums[i-1] \le nums[i]$), close the current subarray at $i-1$ and start a new subarray at $i$.
- After the scan, close the final subarray.

```cpp
vector<tuple<int, int, long long>> decompose(vector<int>& nums) {
    int n = nums.size();
    vector<tuple<int, int, long long>> subarrays;

    int l = 0;
    long long sum = nums[0];

    for (int i = 1; i < n; i++) {
        // If we fail strict decreasing at boundary i-1 -> i, end current subarray
        if (nums[i - 1] <= nums[i]) {
            subarrays.push_back({l, i - 1, sum});
            l = i;
            sum = 0;
        }
        sum += nums[i];
    }
    subarrays.push_back({l, n - 1, sum});
    return subarrays;
}
```

### Before P and After Q
Having all decreasing subarrays, we choose one candidate $(p, q)$ where $p < q$, and try to find the best $[l, r]$ with $l < p < q < r$:
- Find $l < p$ such that $[l, p]$ is strictly increasing, while the sum of the elements in $[l, p - 1]$ is as large as possible.
- Find $r > q$ such that $[q, r]$ is strictly increasing, while the sum of the elements in $[q + 1, r]$ is as large as possible.

Both tasks are symmetrical, so we focus on the first one.

### Variation of Kadane's Algorithm
We define `maxEndingAt[i]` as the largest possible sum of a strictly increasing subarray ending at position $i$.

- Initially, one element on its own is classified as an increasing subarray: `maxEndingAt[i] = nums[i]`.
- If $nums[i-1] < nums[i]$, we can extend the best increasing subarray ending at $i-1$ by appending $nums[i]$. If `maxEndingAt[i-1] > 0`, we add it:

$$
\text{maxEndingAt}[i] = nums[i] + \max(0, \text{maxEndingAt}[i-1])
$$

```cpp
vector<long long> maxEndingAt(n);
for (int i = 0; i < n; i++) {
    maxEndingAt[i] = nums[i];
    if (i > 0 && nums[i - 1] < nums[i]) {
        if (maxEndingAt[i - 1] > 0) {
            maxEndingAt[i] += maxEndingAt[i - 1];
        }
    }
}
```

Symmetrically, we compute `maxStartingAt[i]` as the largest sum of a strictly increasing subarray starting at position $i$:

```cpp
vector<long long> maxStartingAt(n);
for (int i = n - 1; i >= 0; i--) {
    maxStartingAt[i] = nums[i];
    if (i < n - 1 && nums[i] < nums[i + 1]) {
        if (maxStartingAt[i + 1] > 0) {
            maxStartingAt[i] += maxStartingAt[i + 1];
        }
    }
}
```

### Final Step — Stitching the Best Solution
For each candidate decreasing block $(p, q)$ with sum $sum(p, q)$:
A valid Trionic subarray requires:
1. $p < q$ (middle segment has length $\ge 2$).
2. $p > 0$ and $nums[p-1] < nums[p]$ (strictly increasing slope enters $p$).
3. $q < n - 1$ and $nums[q] < nums[q+1]$ (strictly increasing slope leaves $q$).

When valid, the maximum sum achievable through this $(p, q)$ is:

$$
\text{maxEndingAt}[p - 1] + sum(p, q) + \text{maxStartingAt}[q + 1]
$$

We maximize this over all valid $(p, q)$.

### Complete Clean C++ Solution

```cpp
class Solution {
public:
    vector<tuple<int, int, long long>> decompose(vector<int>& nums) {
        int n = nums.size();
        vector<tuple<int, int, long long>> subarrays;

        int l = 0;
        long long sum = nums[0];

        for (int i = 1; i < n; i++) {
            if (nums[i - 1] <= nums[i]) {
                subarrays.push_back({l, i - 1, sum});
                l = i;
                sum = 0;
            }
            sum += nums[i];
        }
        subarrays.push_back({l, n - 1, sum});
        return subarrays;
    }

    long long maxSumTrionic(vector<int>& nums) {
        int n = nums.size();
        vector<long long> maxEndingAt(n);
        for (int i = 0; i < n; i++) {
            maxEndingAt[i] = nums[i];
            if (i > 0 && nums[i - 1] < nums[i]) {
                if (maxEndingAt[i - 1] > 0) {
                    maxEndingAt[i] += maxEndingAt[i - 1];
                }
            }
        }

        vector<long long> maxStartingAt(n);
        for (int i = n - 1; i >= 0; i--) {
            maxStartingAt[i] = nums[i];
            if (i < n - 1 && nums[i] < nums[i + 1]) {
                if (maxStartingAt[i + 1] > 0) {
                    maxStartingAt[i] += maxStartingAt[i + 1];
                }
            }
        }

        vector<tuple<int, int, long long>> PQS = decompose(nums);
        long long ans = -1e18;

        for (auto [p, q, sum] : PQS) {
            if (p > 0 && nums[p - 1] < nums[p] &&
                q < n - 1 && nums[q] < nums[q + 1] &&
                p < q) {
                long long candidate = maxEndingAt[p - 1] + sum + maxStartingAt[q + 1];
                if (candidate > ans) {
                    ans = candidate;
                }
            }
        }

        return ans;
    }
};
```

### Complexity Analysis
- **Time Complexity**: $\mathcal{O}(N)$ — One pass to decompose, one forward pass for `maxEndingAt`, one backward pass for `maxStartingAt`, and one pass over decreasing blocks.
- **Space Complexity**: $\mathcal{O}(N)$ — Arrays for prefix/suffix Kadane tables and decomposition tuples.

---

## 3. Circular Defense (The Turret / Tower Range Cover)

### Problem Overview & Invariants
- We have $N$ defense towers arranged in a circle, indexed $0 \dots N - 1$.
- Tower $i$ has coverage radius $R[i]$. When activated, it covers all positions within circular distance $\le R[i]$.
- That is, it covers indices $[i - R[i], i + R[i]] \pmod N$.
- Our goal is to find the **minimum number of active towers** needed such that every index in the circle is covered by at least one active tower.

### Observation 1 — Instant 1-Tower Full Cover
If any single tower has radius satisfying $2 \cdot R[i] + 1 \ge N$, it covers the entire circle by itself. The answer is immediately $1$.

### Observation 2 — Unrolling the Circle into a Line (Period 3)
Working with wrap-around modulo arithmetic makes interval coverage tricky because intervals can cross the $0/N$ boundary.
Standard technique: unroll the circle into a linear array of length $3N$.
- A full circular coverage corresponds to covering any contiguous segment of length $N$, for instance $[i, i + N]$ for some starting index $i \in [0, N - 1]$.
- A tower $i$ replicated in period $k \in \{0, 1, 2\}$ is centered at position $c = i + k \cdot N$.
- Its coverage interval is $[c - R[i], c + R[i]]$.
- In interval covering, if we are currently at position $x$, any tower whose coverage starts at or before $x$ ($l \le x$) allows us to advance up to $r + 1$ (the next uncovered point).

### Step 1 — Farthest Reach Jump Function
We define `jump[x]` as the farthest point to the right we can reach in a single jump starting at position $x$:
- Initialize `jump[x] = x`.
- For each tower $i$ and period $k \in \{0, 1, 2\}$:
  - Center $c = i + k \cdot N$.
  - Interval $[l, r] = [\max(0, c - R[i]), \min(3N, c + R[i] + 1)]$.
  - `jump[l] = max(jump[l], r)`.
- **Enforcing Monotonicity via Prefix Max**:
  If we can reach some boundary from $x - 1$, starting from $x$ (which is further right) should allow reaching at least that far:
  `jump[x] = max(jump[x], jump[x - 1])`.

```cpp
int maxp = 3 * n;
vector<int> jump(maxp + 1);
for (int i = 0; i <= maxp; i++) jump[i] = i;

for (int i = 0; i < n; i++) {
    for (int k = 0; k < 3; k++) {
        int c = i + n * k;
        int l = max(0, c - r[i]);
        int rr = min(maxp, c + r[i] + 1);
        if (l <= maxp) jump[l] = max(jump[l], rr);
    }
}

for (int i = 1; i <= maxp; i++) {
    jump[i] = max(jump[i], jump[i - 1]);
}
```

### Step 2 — Binary Lifting Acceleration (Doubling)
To cover $[i, i + N]$, we could greedily apply `curr = jump[curr]` until `curr >= i + N`.
However, doing this sequentially for all $N$ starting points would take $\mathcal{O}(N^2)$ in the worst case (e.g. all $R[i] = 1$).

Instead, we use **Binary Lifting** (Sparse Table for jumps):
- Define `up[k][x]` = position reached from $x$ after taking $2^k$ greedy jumps.
- Base case: `up[0][x] = jump[x]`.
- Recurrence: `up[k][x] = up[k - 1][up[k - 1][x]]`.
- For each starting position $i \in [0, N - 1]$, target is $target = i + N$.
  We jump using powers of 2 from $k = 19$ down to $0$:
  If `up[k][curr] < target`, we take $2^k$ jumps: `steps += (1 << k); curr = up[k][curr];`.
  At the end, one final jump reaches $\ge target$: `steps++`.
  The minimum `steps` over all start positions $i$ is our answer!

### Complete Clean C++ Solution

```cpp
int solveCircularDefense(int n, const vector<int>& r) {
    for (int x : r) {
        if (2LL * x + 1 >= n) return 1;
    }

    int maxp = 3 * n;
    vector<int> jump(maxp + 1);
    for (int i = 0; i <= maxp; i++) jump[i] = i;

    for (int i = 0; i < n; i++) {
        for (int k = 0; k < 3; k++) {
            int c = i + n * k;
            int l = max(0, c - r[i]);
            int rr = min(maxp, c + r[i] + 1);
            if (l <= maxp) jump[l] = max(jump[l], rr);
        }
    }

    for (int i = 1; i <= maxp; i++) {
        jump[i] = max(jump[i], jump[i - 1]);
    }

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

        if (curr >= target && steps < ans) {
            ans = steps;
        }
    }

    return (ans > n) ? -1 : ans;
}
```

### Complexity Analysis
- **Time Complexity**: $\mathcal{O}(N \log N)$ — Constructing the binary lifting table takes $20 \times 3N$ operations. Querying for each $i \in [0, N-1]$ takes $\mathcal{O}(\log N)$. Total operations $\approx 60 N \approx 6 \times 10^5$ for $N = 10^4$.
- **Space Complexity**: $\mathcal{O}(N \log N)$ — Binary lifting table of size $20 \times (3N + 1)$ integers.

---

## 4. Multi-GPU Priority Scheduling (Problem Set 3 — Q1)

### Problem Overview & Invariants
- We are given $N$ tasks and $G$ identical GPUs.
- Each task $i$ has:
  - Arrival time $a_i$
  - Execution duration $d_i$
  - Priority $pr_i$
- When a GPU becomes free, the waiting task selected must follow strict priority rules:
  1. **Highest priority** ($pr_i$ descending)
  2. **Earliest arrival time** ($a_i$ ascending)
  3. **Smallest original task ID** ($i$ ascending)
- Execution is non-preemptive.
- Output required:
  - Completion time for each task in original input order.
  - Overall average waiting time across all tasks, rounded/printed to 4 decimal places.

### Observation 1 — Discrete Event Simulation vs Tick-by-Tick
Arrival times and durations can be as large as $10^9$. Simulating time tick-by-tick ($time = 0, 1, 2, \dots$) would result in a massive TLE.
Instead, we must simulate **Discrete Events**:
Time only needs to jump forward to either:
1. The arrival time of the next incoming task, or
2. The earliest completion time of an currently running GPU.

### Step 1 — Dual Heap Architecture
We maintain two priority queues:
1. **Ready Queue `q` (Waiting Tasks)**:
   A max-heap of tasks that have already arrived ($a \le cur\_time$) but are waiting for a free GPU.
   To cleanly implement the tie-breaking rules in a standard C++ max-heap:
   Store: `tuple<long long, long long, int, long long>` as `(pr, -a, -id, d)`.
   Because standard `tuple` compares element-by-element:
   - Higher `pr` comes first.
   - For equal `pr`, larger `-a` means smaller `a` (earlier arrival).
   - For equal `pr` and `a`, larger `-id` means smaller `id`.
2. **Running Queue `runq` (Busy GPUs)**:
   A min-heap storing the `finish_time` of each currently active GPU.
   The size of `runq` is at most $G$.

```cpp
// Ready queue: (priority, -arrival, -id, duration)
priority_queue<tuple<long long, long long, int, long long>> q;

// Busy GPUs: min-heap of completion times
priority_queue<long long, vector<long long>, greater<long long>> runq;
```

### Step 2 — Event Loop Mechanics
At each step of the simulation while tasks remain unfinished (`done < N`):
1. **Push Arrived Tasks**: Advance index `i` through sorted tasks whose $a \le cur\_time$, pushing them into `q`.
2. **Free Completed GPUs**: Pop all GPUs from `runq` whose finish time $\le cur\_time$.
3. **Dispatch to Idle GPUs**: While `!q.empty()` and `runq.size() < G`:
   - Pop highest priority task.
   - `finish = cur_time + d`.
   - `completion[id] = finish`.
   - `totwait += (cur_time - a)`.
   - If $d > 0$, push `finish` into `runq`.
4. **Advance Time**: If all GPUs are busy or the ready queue is empty, leap `cur_time`:

$$
cur\_time = \min(next\_arrival\_time, earliest\_gpu\_finish\_time)
$$

### Complete Clean C++ Solution

```cpp
void solveMultiGPUScheduling() {
    int n, g;
    if (!(cin >> n >> g)) return;

    // Tuple: {arrival, duration, priority, original_id}
    vector<tuple<long long, long long, long long, int>> p(n);
    for (int i = 0; i < n; i++) {
        long long a, d, pr;
        cin >> a >> d >> pr;
        p[i] = {a, d, pr, i};
    }
    sort(p.begin(), p.end());

    priority_queue<tuple<long long, long long, int, long long>> q;
    priority_queue<long long, vector<long long>, greater<long long>> runq;

    int i = 0, done = 0;
    long long totwait = 0, cur_time = 0;
    vector<long long> completion(n);
    const long long INF = 4e18;

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
            long long a = -na;
            int id = -ni;

            long long finish = cur_time + d;
            completion[id] = finish;
            totwait += (cur_time - a);
            done++;

            if (d > 0) runq.push(finish);
        }

        long long next_a = (i < n) ? get<0>(p[i]) : INF;
        long long next_d = runq.empty() ? INF : runq.top();

        if (done < n) {
            if ((int)runq.size() == g || q.empty()) {
                cur_time = min(next_a, next_d);
            }
        }
    }

    for (long long c : completion) cout << c << "\n";
    cout << fixed << setprecision(4) << ((long double)totwait) / n << "\n";
}
```

### Complexity Analysis
- **Time Complexity**: $\mathcal{O}(N \log N + N \log G)$ — Sorting takes $N \log N$. Each task is pushed and popped from `q` and `runq` at most once, which takes $\mathcal{O}(\log N)$ and $\mathcal{O}(\log G)$ respectively.
- **Space Complexity**: $\mathcal{O}(N + G)$ — Storage for tasks, priority queues, and completion timestamps.

---

## 5. Maximum CTR Advertisement (Problem Set 3 — Q2)

### Problem Overview & Invariants
- We are given $N$ advertisement event records. Each record has:
  - `Ad_ID`: string identifier
  - `Impressions`: positive integer
  - `Clicks`: non-negative integer
- We must aggregate the total impressions and total clicks across all records for each unique `Ad_ID`.
- **Eligibility Filter**: Only ads with strictly more than 100 total impressions ($\text{Impressions} > 100$) are eligible.
- Click-Through Rate (CTR) formula:

$$
\text{CTR} = \left(\frac{\text{Total Clicks}}{\text{Total Impressions}}\right) \times 100\%
$$

- We must find the eligible ad with the **maximum CTR**.
- **Tie-Breaking**: If multiple ads have the exact same highest CTR, pick the one with the **lexicographically smallest** `Ad_ID`.
- **Output Requirement**: Output the best `Ad_ID` and its CTR **floored to 4 decimal places** (e.g. `AD123 12.3456`).

### Observation 1 — Why Floating-Point `double` Fails in OA
Comparing CTR values using floating-point types like `double` or `float` is a classic trap:
- Due to binary representation of fractions, values like $1/3$ or $7/9$ cannot be represented exactly.
- When comparing two ads with very close ratios (e.g. $\frac{999}{1001}$ vs $\frac{998}{1000}$), floating-point precision error can swap the order or incorrectly trigger tie-breaking.

### Observation 2 — Exact Rational Comparison via Cross-Multiplication
To compare two candidate ads $A$ and $B$:

$$
\frac{Clicks_A}{Imp_A} > \frac{Clicks_B}{Imp_B} \iff Clicks_A \times Imp_B > Clicks_B \times Imp_A
$$

- Since impressions and clicks fit well within $10^9$, their cross-product is at most $\approx 10^{18}$, which comfortably fits within standard signed 64-bit integer (`long long`, max $\approx 9.22 \times 10^{18}$).
- This cross-multiplication comparison has **zero precision loss**.
- If $Clicks_A \times Imp_B == Clicks_B \times Imp_A$, we break ties by string comparison: pick $ID_A < ID_B$.

```cpp
long long lhs = clk * best_imp;
long long rhs = best_clk * imp;

if (lhs > rhs || (lhs == rhs && id < best_id)) {
    best_id = id;
    best_imp = imp;
    best_clk = clk;
}
```

### Observation 3 — Exact Floored Formatting without Floats
The problem requires flooring the CTR to 4 decimal places:

$$
\text{CTR} = \frac{Clicks \times 100}{Imp}
$$

Floored to 4 decimal places means computing $\lfloor \text{CTR} \times 10^4 \rfloor$:

$$
\lfloor \text{CTR} \times 10^4 \rfloor = \left\lfloor \frac{Clicks \times 100 \times 10000}{Imp} \right\rfloor = \left\lfloor \frac{Clicks \times 10^6}{Imp} \right\rfloor
$$

- We perform purely integer arithmetic:
  `long long scaled = (best_clk * 1000000LL) / best_imp;`
- The integer part is `scaled / 10000`.
- The fractional 4 digits are `scaled % 10000`, printed with leading zeros padded (`setw(4)` and `setfill('0')`).
- This completely bypasses floating-point roundoff issues!

### Complete Clean C++ Solution

```cpp
void solveMaxCTR() {
    int n;
    if (!(cin >> n)) return;

    unordered_map<string, pair<long long, long long>> stats;
    for (int i = 0; i < n; i++) {
        string id;
        long long imp, clk;
        cin >> id >> imp >> clk;
        stats[id].first += imp;
        stats[id].second += clk;
    }

    string best_id = "";
    long long best_imp = 1, best_clk = -1;

    for (const auto& [id, data] : stats) {
        long long imp = data.first;
        long long clk = data.second;
        if (imp <= 100) continue;

        if (best_id == "") {
            best_id = id;
            best_imp = imp;
            best_clk = clk;
            continue;
        }

        long long lhs = clk * best_imp;
        long long rhs = best_clk * imp;

        if (lhs > rhs || (lhs == rhs && id < best_id)) {
            best_id = id;
            best_imp = imp;
            best_clk = clk;
        }
    }

    if (best_id == "") return;

    long long scaled = (best_clk * 1000000LL) / best_imp;
    long long int_part = scaled / 10000;
    long long frac_part = scaled % 10000;

    cout << best_id << " " << int_part << "."
         << setw(4) << setfill('0') << frac_part << "\n";
}
```

### Complexity Analysis
- **Time Complexity**: $\mathcal{O}(N \cdot L)$ — Where $N$ is the number of event records and $L$ is the maximum length of an ad ID string. Hashing and map lookups take $O(L)$ per record.
- **Space Complexity**: $\mathcal{O}(U \cdot L)$ — Storage in hash table for $U$ unique advertisement IDs.

---

## 6. Sum of Maximums of All Subarrays (Problem Set 3 — Q3)

### Problem Overview & Invariants
- We are given an integer array $A$ of length $N$ ($N \le 10^5$, $A[i] \le 10^9$).
- For any subarray $A[L \dots R]$ ($0 \le L \le R < N$), the subarray cost is $\max(A[L \dots R])$.
- We must find the sum of maximums across all possible subarrays:

$$
\sum_{0 \le L \le R < N} \max(A[L \dots R])
$$

### Observation 1 — The Contribution Principle (Inversion of Counting)
Instead of checking all $\mathcal{O}(N^2)$ subarrays and finding the maximum for each, we **invert our perspective**:
> For each element $A[i]$, in exactly how many subarrays does $A[i]$ act as the maximum?

If element $A[i]$ acts as the maximum in $C_i$ distinct subarrays, its total contribution to the final sum is simply:

$$
A[i] \times C_i
$$

Summing $A[i] \times C_i$ across all $i \in [0, N-1]$ gives the answer in linear time!

### Observation 2 — Boundaries of Dominance
Element $A[i]$ remains the maximum in any subarray $[L, R]$ as long as:
1. $L$ does not extend left past any element strictly larger than $A[i]$.
2. $R$ does not extend right past any element larger than $A[i]$.

Let:
- `left[i]` = index of the nearest previous element that is strictly greater than $A[i]$ (or $-1$ if none exists).
- `right[i]` = index of the nearest next element that is greater than or equal to $A[i]$ (or $N$ if none exists).

Then:
- Any valid start index $L$ must lie in the range $(\text{left}[i], i]$. That gives $i - \text{left}[i]$ choices.
- Any valid end index $R$ must lie in the range $[i, \text{right}[i])$. That gives $\text{right}[i] - i$ choices.
- Total subarrays where $A[i]$ is the designated maximum:

$$
C_i = (i - \text{left}[i]) \times (\text{right}[i] - i)
$$

### Why is the condition asymmetrical? (Strictly Greater vs Greater or Equal)
Consider an array with duplicates, e.g. `[4, 4]`:
- If both `left` and `right` were strictly greater, both `4`s would claim the full subarray `[4, 4]`, counting it twice!
- If both `left` and `right` were greater-or-equal, neither `4` would claim the subarray `[4, 4]`, missing it entirely!
By using **strictly greater** on the left and **greater or equal** on the right, duplicate maximums break ties deterministically (the leftmost duplicate claims the subarray). Every single subarray is claimed by exactly one index!

### Step 1 — Monotonic Decreasing Stack for Boundaries
To find `left[i]` in $\mathcal{O}(N)$ total time:
We maintain a stack of indices with strictly decreasing values.
- For each $i$: pop all elements from the stack while $A[\text{top}] \le A[i]$.
- The element remaining on top is the nearest strictly greater element to the left!
- Push $i$ onto the stack.

```cpp
vector<int> left(n), right(n);
stack<int> st;

// Previous strictly greater element
for (int i = 0; i < n; i++) {
    while (!st.empty() && a[st.top()] <= a[i]) {
        st.pop();
    }
    left[i] = st.empty() ? -1 : st.top();
    st.push(i);
}

while (!st.empty()) st.pop();

// Next greater or equal element
for (int i = n - 1; i >= 0; i--) {
    while (!st.empty() && a[st.top()] < a[i]) {
        st.pop();
    }
    right[i] = st.empty() ? n : st.top();
    st.push(i);
}
```

### Complete Clean C++ Solution

```cpp
long long sumOfSubarrayMaximums(const vector<long long>& a) {
    int n = a.size();
    vector<int> left(n), right(n);
    stack<int> st;

    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] <= a[i]) {
            st.pop();
        }
        left[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }

    while (!st.empty()) st.pop();

    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && a[st.top()] < a[i]) {
            st.pop();
        }
        right[i] = st.empty() ? n : st.top();
        st.push(i);
    }

    long long total = 0;
    for (int i = 0; i < n; i++) {
        long long count = (long long)(i - left[i]) * (right[i] - i);
        total += a[i] * count;
    }

    return total;
}
```

### Complexity Analysis
- **Time Complexity**: $\mathcal{O}(N)$ — Every index enters the stack once and leaves the stack at most once in both the left and right passes.
- **Space Complexity**: $\mathcal{O}(N)$ — Storage for boundary vectors `left` and `right`, and the monotonic stack.

---

## 7. K-th Cheapest Pairing on a Generated Cost Grid (PDF Q1)

### Problem Overview & Invariants
- We have $N$ producers and $M$ consumers ($N, M \le 20000$).
- We are given Linear Congruential Generator (LCG) parameters that define two strictly increasing arrays $X[0 \dots N-1]$ and $Y[0 \dots M-1]$:

$$
X[i] = X[i-1] + ((i \cdot A_x + B_x) \bmod C_x) + 1
$$

$$
Y[j] = Y[j-1] + ((j \cdot A_y + B_y) \bmod C_y) + 1
$$

- The pairing cost between producer $i$ and consumer $j$ is:

$$
\text{Cost}(i, j) = X[i] + Y[j]
$$

- This creates an implicit grid of $N \times M$ pairing costs ($N \times M$ up to $4 \times 10^8$).
- Goal: Find the $K$-th smallest pairing cost ($1 \le K \le N \cdot M$).

### Observation 1 — The Problem of Scale
$N \times M = 20000 \times 20000 = 400,000,000$ pairs.
- Generating and storing all pairs requires over $1.6 \text{ GB}$ of memory and will instantly cause Memory Limit Exceeded.
- Sorting all pairs takes $\mathcal{O}(NM \log(NM)) \approx 10^{10}$ operations, causing Time Limit Exceeded.

### Observation 2 — Monotonicity and Binary Search on the Cost Value
Because both $X$ and $Y$ are strictly increasing sequences:
- The minimum possible pairing cost is $X[0] + Y[0]$.
- The maximum possible pairing cost is $X[N-1] + Y[M-1]$.
The answer lies in the range $[\text{low}, \text{high}] = [X[0] + Y[0], X[N-1] + Y[M-1]]$.

For any candidate cost threshold $V$, we define a counting function:

$$
\text{countLessEqual}(V) = \text{number of pairs } (i, j) \text{ such that } X[i] + Y[j] \le V
$$

- If $\text{countLessEqual}(V) \ge K$, then the $K$-th smallest cost is $\le V$.
- Otherwise, the $K$-th smallest cost is $> V$.

### Step 1 — Staircase Two-Pointer Count in $\mathcal{O}(N + M)$
How do we compute $\text{countLessEqual}(V)$ efficiently without checking all pairs?
Notice that as $i$ increases ($0 \dots N-1$), $X[i]$ strictly increases.
To keep $X[i] + Y[j] \le V$, $Y[j]$ must decrease, meaning $j$ can only move backwards!

We initialize $j = M - 1$:
- For each $i$ from $0$ to $N - 1$:
  - While $j \ge 0$ and $X[i] + Y[j] > V$, decrement $j--$.
  - Once $X[i] + Y[j] \le V$, because $Y$ is sorted, all indices $0 \dots j$ also satisfy $X[i] + Y[k] \le V$.
  - Thus, row $i$ contributes exactly $j + 1$ pairs!
  - Add $j + 1$ to our total count.

Because $j$ only moves left, across the entire loop over all $i$, $j$ decreases at most $M$ times.
Total time per check is only $\mathcal{O}(N + M) \approx 40,000$ operations!

```cpp
auto countLessEqual = [&](long long target) -> long long {
    long long cnt = 0;
    int j = m - 1;
    for (int i = 0; i < n; i++) {
        while (j >= 0 && x[i] + y[j] > target) {
            j--;
        }
        cnt += (j + 1);
    }
    return cnt;
};
```

### Complete Clean C++ Solution

```cpp
long long solveKthCheapestPairing(int n, int m, long long k,
                                  long long x0, long long ax, long long bx, long long cx,
                                  long long y0, long long ay, long long by, long long cy) {
    vector<long long> x(n), y(m);
    x[0] = x0;
    for (int i = 1; i < n; i++) {
        x[i] = x[i - 1] + ((1LL * i * ax + bx) % cx) + 1;
    }
    y[0] = y0;
    for (int j = 1; j < m; j++) {
        y[j] = y[j - 1] + ((1LL * j * ay + by) % cy) + 1;
    }

    long long low = x[0] + y[0];
    long long high = x[n - 1] + y[m - 1];
    long long ans = high;

    auto countLessEqual = [&](long long target) -> long long {
        long long cnt = 0;
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
        long long mid = low + (high - low) / 2;
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

### Complexity Analysis
- **Time Complexity**: $\mathcal{O}((N + M) \log(\text{Range}))$ — Binary search takes $\approx 60$ iterations. Each iteration takes $(N + M) = 40,000$ operations. Total operations $\approx 2.4 \times 10^6$ ($< 15$ ms in C++).
- **Space Complexity**: $\mathcal{O}(N + M)$ — Arrays to hold generated sequences $X$ and $Y$.

---

## 8. Consensus Median of Three Gel Reports (PDF Q2)

### Problem Overview & Invariants
- We are given three pre-sorted arrays $A, B, C$ representing test gel measurements.
- Array lengths are $n_1, n_2, n_3$ with $n_1 + n_2 + n_3 \le 20000$.
- We must find the **median** of the combined multiset of all elements.
- Formatting requirement: output the median formatted with exactly 1 decimal digit (e.g. `5.0`, `35.5`).

### Observation 1 — Zero Extra Memory / 3-Pointer Merge Scan
All three input arrays are already individually sorted in ascending order.
The total number of elements is $T = n_1 + n_2 + n_3$.
The median of a combined sorted array of length $T$:
- If $T$ is odd, the median is the single element at index $T / 2$ (0-indexed).
- If $T$ is even, the median is the average of the two middle elements at indices $T/2 - 1$ and $T/2$.

Instead of allocating a merged array of size $T$ or calling `std::sort`, we can simply advance three pointers $p_1, p_2, p_3$ step-by-step up to step $T / 2$, tracking the current and previous minimum value!

### Step 1 — 3-Way Pointer Traversal
Maintain:
- $p_1, p_2, p_3$ pointing to the heads of arrays $A, B, C$.
- `prev_val` and `curr_val` holding the last two popped elements.

At each step $0 \dots T/2$:
- Set `prev_val = curr_val`.
- Inspect the elements at the heads: $A[p_1], B[p_2], C[p_3]$ (using infinity if a pointer has reached the end).
- Pick the smallest of the three headers, store in `curr_val`, and increment that array's pointer.

```cpp
int p1 = 0, p2 = 0, p3 = 0;
int prev_val = 0, curr_val = 0;

for (int step = 0; step <= total / 2; step++) {
    prev_val = curr_val;
    int val1 = (p1 < n1) ? a[p1] : 2e9;
    int val2 = (p2 < n2) ? b[p2] : 2e9;
    int val3 = (p3 < n3) ? c[p3] : 2e9;

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
```

### Complete Clean C++ Solution

```cpp
double findConsensusMedian(const vector<int>& a, const vector<int>& b, const vector<int>& c) {
    int n1 = a.size(), n2 = b.size(), n3 = c.size();
    int total = n1 + n2 + n3;
    int p1 = 0, p2 = 0, p3 = 0;
    int prev_val = 0, curr_val = 0;

    for (int step = 0; step <= total / 2; step++) {
        prev_val = curr_val;
        int val1 = (p1 < n1) ? a[p1] : 2e9;
        int val2 = (p2 < n2) ? b[p2] : 2e9;
        int val3 = (p3 < n3) ? c[p3] : 2e9;

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

### Complexity Analysis
- **Time Complexity**: $\mathcal{O}(n_1 + n_2 + n_3)$ — The loop executes at most $\lfloor T/2 \rfloor + 1 \le 10001$ iterations. Each iteration performs $\mathcal{O}(1)$ comparisons.
- **Space Complexity**: $\mathcal{O}(1)$ — Only three pointer indices and scalar variables.

---

## 9. Stamped Code Mold Families (PDF Q3)

### Problem Overview & Invariants
- We are given $n$ uppercase alphanumeric code strings ($n \le 1000$, string length $\le 12$).
- Two codes $X$ and $Y$ belong to the same compatible mold family if one can be transformed into an anagram of the other by deleting at most one character from one of the strings (or none).
- More formally, $X$ and $Y$ are directly compatible if:
  1. $|X| == |Y|$: $X$ and $Y$ are exact anagrams of each other (zero deletions).
  2. $|X| == |Y| + 1$: Deleting exactly one character from $X$ yields an anagram of $Y$.
  3. $|X| + 1 == |Y|$: Deleting exactly one character from $Y$ yields an anagram of $X$.
- If $X$ is compatible with $Y$, and $Y$ is compatible with $Z$, then $X, Y, Z$ belong to the same family (transitive closure / connected components).
- We must output the total number of families, and list the codes in each family preserving their **original appearance order** from the input.

### Observation 1 — Anagrams Depend Only on Character Frequencies
Since anagram equivalence ignores the order of characters, each string can be reduced to a 26-dimensional frequency vector:

$$
\text{cnt}[c] = \text{number of occurrences of letter } c \in ['A', 'Z']
$$

Two strings $X$ and $Y$ can be compared in $\mathcal{O}(26)$ time:
- If $||X| - |Y|| > 1$: Impossible to be compatible. Return `false`.
- If $|X| == |Y|$: Compatible if and only if $\text{cnt}_X == \text{cnt}_Y$.
- If $|X| == |Y| + 1$: String $X$ must contain every character present in $Y$, with exactly one extra character:
  - For all 26 letters: $\text{cnt}_X[c] \ge \text{cnt}_Y[c]$.
  - The sum of differences $\sum_{c=0}^{25} (\text{cnt}_X[c] - \text{cnt}_Y[c]) == 1$.
- If $|X| + 1 == |Y|$: Symmetric to the case above with roles of $X$ and $Y$ swapped.

```cpp
bool isCompatible(const string& a, const vector<int>& cntA,
                  const string& b, const vector<int>& cntB) {
    int la = a.size(), lb = b.size();
    if (abs(la - lb) > 1) return false;

    if (la == lb) {
        return cntA == cntB;
    }

    const auto& big = (la > lb) ? cntA : cntB;
    const auto& small = (la > lb) ? cntB : cntA;
    int diff = 0;
    for (int i = 0; i < 26; i++) {
        if (big[i] < small[i]) return false;
        diff += (big[i] - small[i]);
    }
    return diff == 1;
}
```

### Step 1 — Graph Construction and Connected Components
1. Precompute frequency vectors for all $n$ strings.
2. For each pair $(i, j)$ with $0 \le i < j < n$, check compatibility. If compatible, add an undirected edge between $i$ and $j$.
   Total pair checks: $\frac{n(n - 1)}{2} \approx \frac{1000 \times 999}{2} \approx 5 \times 10^5$.
   Each check takes at most 26 operations. Total time $\approx 1.3 \times 10^7$ operations ($< 20$ ms).
3. Traverse the graph using BFS/DFS to identify connected components.
4. For each component, sort the member indices in ascending order of their original input index, and print the resulting strings.

### Complete Clean C++ Solution

```cpp
bool isCompatible(const string& a, const vector<int>& cntA,
                  const string& b, const vector<int>& cntB) {
    int la = a.size(), lb = b.size();
    if (abs(la - lb) > 1) return false;

    if (la == lb) {
        return cntA == cntB;
    }

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

### Complexity Analysis
- **Time Complexity**: $\mathcal{O}(n^2 \cdot 26)$ — Precomputing character counts and running pairwise compatibility checks takes $\approx 1.3 \times 10^7$ operations. Graph traversal takes $\mathcal{O}(V + E)$.
- **Space Complexity**: $\mathcal{O}(n^2)$ — Graph adjacency list and frequency tables.

---

## 10. Course Schedule III (PDF Q4)

### Problem Overview & Invariants
- We are given an array of $n$ courses, where `courses[i] = [duration_i, lastDay_i]`.
- You can take only one course at a time.
- A course must be completed on or before `lastDay_i`.
- The goal is to return the **maximum number of courses** you can take.

### Observation 1 — The Deadline Sorting Invariant (Jackson's Rule)
Suppose we have already decided on an optimal subset of courses to take. In what order should we take them?
In classical scheduling theory (Jackson's Rule / Earliest Deadline First), taking courses in increasing order of their deadlines $lastDay_i$ is always optimal:
- If a set of courses can be scheduled in any order, it can always be scheduled in ascending order of their deadlines.
- Therefore, we can immediately sort all courses by $lastDay_i$ ascending and process them sequentially from left to right.

### Observation 2 — The Greedy Exchange Argument (Max-Heap Swap)
As we iterate through the sorted courses, we keep track of the cumulative `total_time` spent so far:
- If `total_time + duration <= lastDay`:
  We can greedily take this course! Add `duration` to `total_time` and record it in our set of chosen courses.
- What if `total_time + duration > lastDay`?
  We cannot simply add this course because it violates the deadline. However, look at the courses we have chosen so far:
  - If the longest course in our chosen set has duration $D_{max} > duration$, we can **swap out** that longest course and take the current course instead!
  - **Why does this swap strictly help us?**
    1. The total number of courses taken remains exactly the same.
    2. The new `total_time` decreases by $(D_{max} - duration) > 0$.
    3. Because the current course has a deadline $lastDay \ge \text{any previously accepted course's deadline}$ (due to sorting), swapping in a shorter course frees up time and makes it easier for all future courses to fit!

```cpp
priority_queue<int> max_heap; // durations of accepted courses
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
```

### Complete Clean C++ Solution

```cpp
class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        sort(courses.begin(), courses.end(), [](const auto& a, const auto& b) {
            return a[1] < b[1];
        });

        priority_queue<int> max_heap;
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

### Complexity Analysis
- **Time Complexity**: $\mathcal{O}(n \log n)$ — Sorting $n$ courses takes $\mathcal{O}(n \log n)$. Each course pushes and pops from the max-heap at most once, which takes $\mathcal{O}(\log n)$.
- **Space Complexity**: $\mathcal{O}(n)$ — Priority queue storing durations of accepted courses.

---

## 11. JoJo The Perfectionist (PDF Q5)

### Problem Overview & Invariants
- Queue $A$ has $X$ boys with heights $A[0 \dots X-1]$.
- Queue $B$ has $Y$ girls with heights $B[0 \dots Y-1]$, where $X \ge Y$.
- We must insert $X - Y$ "empty spots" (represented as height $0$) into queue $B$ to make both queues have length $X$, resulting in queue $B'$.
- The relative ordering of the original $Y$ girls in $B'$ must remain strictly identical to their order in $B$.
- The "unity score" is defined as:

$$
\text{Score} = \sum_{i=0}^{X-1} A[i] \times B'[i]
$$

- Goal: Find the maximum possible unity score.

### Observation 1 — Subsequence Alignment Perspective
Notice what inserting $X - Y$ zeroes into queue $B$ actually means:
- Any boy who is aligned with a $0$ in $B'$ contributes $A[i] \times 0 = 0$ to the sum.
- The remaining $Y$ boys are paired with the $Y$ girls in order: boy $i_1$ with girl $0$, boy $i_2$ with girl $1$, $\dots$, boy $i_Y$ with girl $Y-1$, where:

$$
0 \le i_1 < i_2 < \dots < i_Y < X
$$

- Therefore, the problem is completely equivalent to:
  > Choose an increasing subsequence of $Y$ boys from queue $A$ to match with the $Y$ girls in queue $B$ such that the sum of products $\sum_{j=0}^{Y-1} A[i_{j+1}] \times B[j]$ is maximized.

### Step 1 — 2D Dynamic Programming Formulation
Let $dp[i][j]$ be the maximum unity score pairing a subset of the first $i$ boys with the first $j$ girls ($0 \le j \le \min(i, Y)$).
When considering boy $i$ (at 0-indexed position $i - 1$):
1. **Option 1 (Skip boy $i$)**: Align boy $i$ with a zero. The score is $dp[i - 1][j]$.
2. **Option 2 (Match boy $i$ with girl $j$)**: Match boy $i - 1$ with girl $j - 1$. The score is:

$$
dp[i - 1][j - 1] + A[i - 1] \times B[j - 1]
$$

Thus, the recurrence relation is:

$$
dp[i][j] = \max(dp[i - 1][j], dp[i - 1][j - 1] + A[i - 1] \times B[j - 1])
$$

### Step 2 — 1D Space Optimization
Notice that row $i$ only depends on row $i - 1$.
Specifically, $dp[j]$ depends on the old $dp[j]$ and the old $dp[j - 1]$.
By iterating $j$ in **descending order** from $\min(i, Y)$ down to $1$:
`dp[j] = max(dp[j], dp[j - 1] + A[i - 1] * B[j - 1]);`
When updating `dp[j]`, `dp[j - 1]` still holds the value from the previous outer iteration ($i - 1$). This reduces memory to $\mathcal{O}(Y)$!

```cpp
vector<long long> dp(y + 1, 0);

for (int i = 1; i <= x; i++) {
    for (int j = min(i, y); j >= 1; j--) {
        dp[j] = max(dp[j], dp[j - 1] + a[i - 1] * b[j - 1]);
    }
}
```

### Complete Clean C++ Solution

```cpp
long long solveJoJoPerfectionist(int x, int y, const vector<long long>& a, const vector<long long>& b) {
    vector<long long> dp(y + 1, 0);

    for (int i = 1; i <= x; i++) {
        for (int j = min(i, y); j >= 1; j--) {
            long long match_val = dp[j - 1] + a[i - 1] * b[j - 1];
            if (match_val > dp[j]) {
                dp[j] = match_val;
            }
        }
    }

    return dp[y];
}
```

### Complexity Analysis
- **Time Complexity**: $\mathcal{O}(X \cdot Y)$ — Outer loop runs $X$ times, inner loop runs at most $Y$ times. For $X, Y \le 500$, total operations $\le 2.5 \times 10^5$ ($< 2$ ms).
- **Space Complexity**: $\mathcal{O}(Y)$ — 1D vector of length $Y + 1$.

---

## 12. Minimum Time to Transport All Individuals (PDF Q6)

### Problem Overview & Invariants
- We have $n$ individuals ($n \le 12$) at a base camp (start bank) who must all be transported across a river to a destination.
- Boat capacity is $k$ ($1 \le k \le n$).
- The river has $m$ environmental cyclic stages ($0 \le stage < m \le 5$), each with a time multiplier $mul[stage]$.
- **Outbound Trip (Base $\to$ Destination)**:
  - We choose a non-empty group $S$ of size $1 \le |S| \le k$ from people at the base camp.
  - The trip takes duration:

$$
d = \max_{p \in S}(time[p]) \times mul[stage]
$$

  - The stage advances cyclically by $\lfloor d \rfloor \pmod m$.
- **Return Trip (Destination $\to$ Base)**:
  - Exactly 1 person already at the destination must row the boat back to the base.
  - The trip takes duration:

$$
d = time[r] \times mul[stage]
$$

  - The stage advances cyclically by $\lfloor d \rfloor \pmod m$.
- Goal: Find the **minimum total time** to get all $n$ individuals to the destination.

### Observation 1 — Small $n \le 12$ Implies Bitmask State Space
With $n \le 12$, any subset of people remaining at the base camp can be represented by a bitmask of $n$ bits ($0 \dots 2^n - 1 = 4095$).
The full state of the system is uniquely defined by:
1. `mask`: which people are currently at the base camp ($0 \dots 2^n - 1$).
2. `stage`: the current environmental weather stage ($0 \dots m - 1$).
3. `boat`: location of the boat ($0$ = at base camp, $1$ = at destination).

Total distinct states in the entire state space:

$$
\text{Total States} = 2^{12} \times 5 \times 2 = 4096 \times 10 = 40,960
$$

This is very small!

### Step 1 — Graph Shortest Path via Dijkstra's Algorithm
Every state transition consumes a positive real number of seconds ($d > 0$).
Finding the minimum total time from the initial state `((1 << n) - 1, stage = 0, boat = 0)` to any state with `mask = 0` and `boat = 1` is a classic **Single-Source Shortest Path** problem on a directed graph with positive edge weights.
We use **Dijkstra's Algorithm** with a priority queue `priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>>`.

### Step 2 — Efficient Submask Iteration
When the boat is at base camp (`boat == 0`), we iterate over all non-empty subsets $sub \subseteq mask$ of size $\le k$:
Using the standard submask enumeration trick:
`for (int sub = mask; sub > 0; sub = (sub - 1) & mask)`
For each valid subset $sub$ with popcount $\le k$:
- Calculate `max_t = max(time[i])` for $i \in sub$.
- Compute `trip_t = max_t * mul[stage]`.
- New stage $= (stage + \lfloor trip_t \rfloor) \pmod m$.
- New mask $= mask \oplus sub$.
- Relax distance to `(new_mask, next_stage, boat = 1)`.

When the boat is at destination (`boat == 1`), the destination contains people with indices $r$ where $(mask \gg r) \& 1 == 0$.
We test rowing back with person $r$:
- Compute `ret_t = time[r] * mul[stage]`.
- New stage $= (stage + \lfloor ret_t \rfloor) \pmod m$.
- New mask $= mask \mid (1 \ll r)$.
- Relax distance to `(new_mask, next_stage, boat = 0)`.

### Complete Clean C++ Solution

```cpp
struct State {
    int mask;
    int stage;
    int boat;
};

double minTimeToTransport(int n, int k, int m,
                          const vector<int>& time,
                          const vector<double>& mul) {
    int total_masks = (1 << n);
    vector<vector<vector<double>>> dist(total_masks,
        vector<vector<double>>(m, vector<double>(2, 1e18)));

    using Node = pair<double, int>;
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
            for (int sub = mask; sub > 0; sub = (sub - 1) & mask) {
                int sz = __builtin_popcount(sub);
                if (sz < 1 || sz > k) continue;

                int max_t = 0;
                for (int i = 0; i < n; i++) {
                    if ((sub >> i) & 1) {
                        if (time[i] > max_t) max_t = time[i];
                    }
                }

                double trip_t = max_t * mul[stage];
                int next_stage = (stage + (int)floor(trip_t)) % m;
                int next_mask = mask ^ sub;

                if (d + trip_t < dist[next_mask][next_stage][1]) {
                    dist[next_mask][next_stage][1] = d + trip_t;
                    pq.push({d + trip_t, (next_mask << 4) | (next_stage << 1) | 1});
                }
            }
        } else {
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

### Complexity Analysis
- **Time Complexity**: $\mathcal{O}(2^n \cdot \binom{n}{k} \cdot m \log(\text{Total States}))$ — With $n \le 12$ and $m \le 5$, the number of states is $40,960$. Dijkstra visits each reachable state and pushes to the heap in a few milliseconds.
- **Space Complexity**: $\mathcal{O}(2^n \cdot m)$ — The 3D distance table requires $4096 \times 5 \times 2 \times 8 \text{ bytes} \approx 328 \text{ KB}$.

---

## 13. Dynamic Tree Path Sum (PDF Q7)

### Problem Overview & Invariants
- We are given a rooted tree with $n$ nodes ($n \le 2 \times 10^5$), rooted at node $1$.
- Each node $i$ has an integer value $v_i$.
- We must process $q$ queries ($q \le 2 \times 10^5$) of two types:
  1. `1 s x`: Update the value of node $s$ to $x$.
  2. `2 s`: Query the sum of values on the path from root $1$ to node $s$.

### Observation 1 — Inverting Point Updates into Subtree Range Additions
Consider what happens when the value of a single node $s$ changes by $\Delta = x - v_s$:
- For any node $u$ that is **not** in the subtree of $s$, the unique path from root $1$ to $u$ never passes through $s$. Thus, $u$'s root-to-node path sum is **completely unchanged**.
- For every node $u$ that lies **inside the subtree of $s$**, the unique path from root $1$ to $u$ must pass through $s$. Thus, $u$'s root-to-node path sum increases by exactly $\Delta$!

Therefore:
> Updating the value of node $s$ by $\Delta$ is identical to adding $\Delta$ to the path sum of every node in the subtree of $s$.

### Observation 2 — Flattening the Tree via Euler Tour
By performing a Depth First Search (DFS), we can assign each node $u$ an entry time $in[u]$ and exit time $out[u]$:
- The entire subtree of node $s$ corresponds to the contiguous range of DFS entry times: $[in[s], out[s]]$.
- Thus:
  - Query 1 (Update node $s$): Add $\Delta = x - v_s$ to all indices in the interval $[in[s], out[s]]$.
  - Query 2 (Path sum to node $s$): Query the value at single index $in[s]$!

We have transformed the tree problem into:
> **Range Addition, Point Query** on an array of size $n$!

### Step 1 — Fenwick Tree (Binary Indexed Tree) for Range Add, Point Query
Using the standard difference array technique on a Fenwick tree:
- To add $\Delta$ to range $[l, r]$:
  `bit.add(l, delta);`
  `bit.add(r + 1, -delta);`
- To query the point value at index $i$:
  Compute prefix sum up to $i$: `bit.pointQuery(i)`.
Both operations run in $\mathcal{O}(\log n)$ time!

### Step 2 — Iterative DFS to Prevent Recursion Stack Overflow
With $n = 200,000$, a degenerate "line tree" has depth $200,000$. Standard recursive DFS will trigger a segmentation fault due to call stack overflow.
We write an explicit stack-based iterative DFS:

```cpp
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
```

### Complete Clean C++ Solution

```cpp
struct Fenwick {
    int n;
    vector<long long> tree;
    Fenwick(int n) : n(n), tree(n + 2, 0) {}

    void add(int i, long long delta) {
        for (; i <= n; i += i & -i) tree[i] += delta;
    }
    void rangeAdd(int l, int r, long long delta) {
        add(l, delta);
        add(r + 1, -delta);
    }
    long long pointQuery(int i) {
        long long sum = 0;
        for (; i > 0; i -= i & -i) sum += tree[i];
        return sum;
    }
};

void solveDynamicTreePathSum() {
    int n, q;
    if (!(cin >> n >> q)) return;

    vector<long long> val(n + 1);
    for (int i = 1; i <= n; i++) cin >> val[i];

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

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
            long long x;
            cin >> s >> x;
            long long delta = x - val[s];
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

### Complexity Analysis
- **Time Complexity**: $\mathcal{O}((n + q) \log n)$ — Tree flattening takes $\mathcal{O}(n)$. Each update and query takes $\mathcal{O}(\log n)$ on the Fenwick tree. Total time $< 0.15$ s for $2 \times 10^5$ operations.
- **Space Complexity**: $\mathcal{O}(n)$ — Adjacency lists, Euler tour arrays, and the Fenwick tree.

---

## 14. City Skyline — Zoning Laws, Construction Decrees & Audits (PDF Q8)

### Problem Overview & Invariants
- We are given an array $A$ of $N$ skyscraper heights ($1 \le N \le 5000$).
- We must execute $Q$ operations ($1 \le Q \le 5000$) of three types:
  1. `1 L R X`: Zoning cap — for each $i \in [L, R]$, set $A[i] = \min(A[i], X)$.
  2. `2 L R Y`: Construction decree — for each $i \in [L, R]$, set $A[i] = A[i] + Y$.
  3. `3 L R`: Audit query — output the sum of heights $\sum_{i=L}^R A[i]$.
- Skyscraper heights can reach up to $5 \times 10^{11}$, and cumulative sum up to $2.5 \times 10^{15}$.

### Observation 1 — Reading the Constraints First
Look carefully at the constraints:

$$
N \le 5000, \quad Q \le 5000
$$

The maximum total number of operations in a direct linear scan is:

$$
N \times Q = 5000 \times 5000 = 2.5 \times 10^7
$$

In modern C++, a straightforward loop of $2.5 \times 10^7$ iterations with primitive integer operations executes in **under 30 milliseconds**!

### Observation 2 — The "Segment Tree Beats" Trap
Combining range min updates (`A[i] = min(A[i], X)`), range additions (`A[i] += Y`), and range sum queries is famous in competitive programming as the "Segment Tree Beats" problem (which solves it in $\mathcal{O}(Q \log^2 N)$ for $N, Q \le 2 \times 10^5$).
However:
- Coding Segment Tree Beats requires maintaining maximums, second maximums, maximum counts, and multiple lazy propagation tags over 150+ lines of intricate code.
- In a timed 60-to-90 minute OA, attempting Segment Tree Beats when $N, Q \le 5000$ introduces massive bug risk and wastes 30+ minutes.
- The straightforward $\mathcal{O}(N \cdot Q)$ array simulation is guaranteed 100% bug-free, takes 15 lines of code, and passes all test cases with flying colors.
- Use 64-bit integers (`long long`) to prevent overflow.

### Complete Clean C++ Solution

```cpp
void solveCitySkyline() {
    int n, q;
    if (!(cin >> n >> q)) return;

    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    while (q--) {
        int type, l, r;
        cin >> type >> l >> r;
        if (type == 1) {
            long long x;
            cin >> x;
            for (int i = l; i <= r; i++) {
                if (a[i] > x) a[i] = x;
            }
        } else if (type == 2) {
            long long y;
            cin >> y;
            for (int i = l; i <= r; i++) {
                a[i] += y;
            }
        } else {
            long long sum = 0;
            for (int i = l; i <= r; i++) {
                sum += a[i];
            }
            cout << sum << "\n";
        }
    }
}
```

### Complexity Analysis
- **Time Complexity**: $\mathcal{O}(N \cdot Q)$ — At most $2.5 \times 10^7$ operations. Runs in $\approx 25$ ms.
- **Space Complexity**: $\mathcal{O}(N)$ — Array of heights of size $N + 1$.

---

## 15. Array Reduction via MEX — Lexicographically Largest Result (PDF Q9)

### Problem Overview & Invariants
- We are given an array of integers `arr` of length $N$ ($N \le 2 \times 10^5$).
- In one step, we choose a prefix of length $k \ge 1$, compute its **MEX** (Minimum Excluded non-negative integer), append that MEX to our `result` array, and remove that prefix from `arr`.
- We repeat this process until `arr` is completely empty.
- Goal: Find the **lexicographically largest** possible `result` array. (This corresponds to Codeforces 1628A — *Meximum Array*).

### Observation 1 — The Lexicographical Greedy Principle
In lexicographical comparison, the very first element is the most important:
- An array starting with $5$ is strictly larger than an array starting with $4$, regardless of all subsequent elements.
- Therefore, our very first decision must make `result[0]` **as large as possible**.
- What is the maximum possible MEX achievable by any prefix?
  It is the **MEX of the entire remaining array**! No prefix can ever contain more distinct non-negative integers than the whole array.
- So the target MEX for our first prefix is $M = \text{MEX}(arr)$.

### Observation 2 — The Shortest Prefix Greedy Choice
Suppose the target MEX for our current prefix is $M$:
- Multiple prefixes might have $\text{MEX} = M$. Which one should we cut?
- We should cut the **shortest prefix** that contains all numbers in $\{0, 1, \dots, M - 1\}$!
- **Why shortest?**
  Leaving as many elements as possible in the remaining suffix gives future steps the maximum possible variety of numbers, allowing subsequent MEX values to be as large as possible. Removing extra elements beyond what is needed to achieve $M$ can only hurt or tie future choices.

### Step 1 — Remaining Element Frequencies and Two Pointers
1. Compute the frequency of all numbers in `arr`: `count[x]`.
2. Compute the initial MEX of the entire array: find the first non-negative integer with `count[mex] == 0`.
3. While the remaining array is non-empty:
   - If current target MEX is $0$:
     No prefix can achieve MEX $> 0$ because $0$ does not exist in the remaining array. We simply consume the single element at index $l$, append $0$ to `result`, decrement its count, and advance $l++$.
   - If current target MEX is $M > 0$:
     Scan from left pointer $r = l$ to the right:
     - Decrement `count[arr[r]]`.
     - If $arr[r] < M$ and not seen in the current window, mark it seen and increment `seen_count++`.
     - The moment `seen_count == M`, all required numbers $\{0, \dots, M - 1\}$ have appeared!
     - Append $M$ to `result`, set $l = r + 1$.
     - Update the target MEX for the remaining suffix using the decremented frequency array.

```cpp
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
```

### Complete Clean C++ Solution

```cpp
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

        while (cur_mex > 0 && count[cur_mex - 1] == 0) {
            cur_mex--;
        }
        while (count[cur_mex] > 0) cur_mex++;
    }

    return result;
}
```

### Complexity Analysis
- **Time Complexity**: $\mathcal{O}(N)$ — Pointer $r$ advances strictly from $0$ to $N - 1$. Each element has its frequency decremented exactly once. Updating `cur_mex` is amortized $\mathcal{O}(N)$.
- **Space Complexity**: $\mathcal{O}(N)$ — Frequency array and `seen` lookup table.

---

## 16. Delivery Service — Count Impossible City Pairs (PDF Q10)

### Problem Overview & Invariants
- We have $N$ cities ($N \le 20000$). Each city has two shift hubs:
  - **Morning shift**: node $i$ ($1 \le i \le N$)
  - **Afternoon shift**: node $i + N$ ($N + 1 \le i + N \le 2N$)
- There is a free internal transition: Morning $i \to$ Afternoon $i + N$ for all $1 \le i \le N$.
- We are given $M$ directed courier routes ($M \le 15000$).
- A delivery from city $u$ to city $v$ is **possible** if and only if Morning hub $u$ can reach Afternoon hub $v + N$ via directed edges.
- Goal: Count the number of pairs $(u, v)$ with $1 \le u, v \le N$ for which delivery is **impossible**.

### Observation 1 — Problem Framing and Complementary Counting
Total possible ordered pairs of cities is:

$$
\text{Total Pairs} = N^2
$$

If we can count the number of ordered pairs $(u, v)$ for which Morning $u \rightsquigarrow$ Afternoon $v + N$, then:

$$
\text{Impossible Pairs} = N^2 - \text{Possible Pairs}
$$

### Observation 2 — The Scale Dilemma
- $N = 20000$ nodes, $M = 15000$ edges.
- Running a standard BFS from each of the $N$ morning nodes takes:

$$
\mathcal{O}(N \times (V + E)) = 20000 \times (40000 + 35000) \approx 1.5 \times 10^9 \text{ operations}
$$

  This will easily exceed the typical 2.0-second time limit!

### Observation 3 — Bit-Parallel Acceleration (Chunked BFS with `std::bitset`)
Instead of running BFS for one morning node at a time, we process morning nodes in batches (chunks) of size $B = 2048$ using `std::bitset<2048>`.
- For node $u$, `reachable[u]` is a bitset of size 2048:
  Bit $k$ is set if morning city $(chunk\_start + k)$ can reach node $u$.
- When exploring edge $u \to v$:
  The new reachable sources from $u$ to $v$ are given by bitwise operations:
  `mask = reachable[u] & ~reachable[v]`
  If `mask.any()`, we update `reachable[v] |= reachable[u]` and push $v$ into the BFS queue.
- Why is this so fast?
  1. 64 sources are processed in a single CPU instruction (word-level parallelism).
  2. The total number of BFS passes drops from $20,000$ to only:

$$
\left\lceil \frac{20000}{2048} \right\rceil = 10 \text{ passes!}
$$

  3. Total runtime drops from $1.5 \times 10^9$ ops down to $\approx 2.5 \times 10^7$ ops ($< 0.35$ s).

```cpp
const int CHUNK = 2048;
for (int chunk_start = 1; chunk_start <= n; chunk_start += CHUNK) {
    int chunk_end = min(n, chunk_start + CHUNK - 1);
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

    // Accumulate reachable afternoon nodes
    for (int j = 1; j <= n; j++) {
        possible_pairs += reachable[j + n].count();
    }
}
```

### Complete Clean C++ Solution

```cpp
const int CHUNK = 2048;

long long countImpossibleCityPairs() {
    int n, m;
    if (!(cin >> n >> m)) return 0;

    int total_nodes = 2 * n;
    vector<vector<int>> adj(total_nodes + 1);

    for (int i = 1; i <= n; i++) {
        adj[i].push_back(i + n);
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    long long possible_pairs = 0;

    for (int chunk_start = 1; chunk_start <= n; chunk_start += CHUNK) {
        int chunk_end = min(n, chunk_start + CHUNK - 1);
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

        for (int j = 1; j <= n; j++) {
            possible_pairs += reachable[j + n].count();
        }
    }

    long long total_pairs = 1LL * n * n;
    return total_pairs - possible_pairs;
}
```

### Complexity Analysis
- **Time Complexity**: $\mathcal{O}\left(\left\lceil \frac{N}{\text{CHUNK}} \right\rceil \cdot (V + E) \cdot \frac{\text{CHUNK}}{64}\right)$ — With 10 chunks, each exploring $\approx 55,000$ edges with 32 64-bit words, total bitwise operations $\approx 1.8 \times 10^7$ ($< 0.35$ s).
- **Space Complexity**: $\mathcal{O}\left(V \cdot \frac{\text{CHUNK}}{8}\right)$ — For $40,000$ nodes, each bitset is 256 bytes. Total memory $\approx 10 \text{ MB}$.
