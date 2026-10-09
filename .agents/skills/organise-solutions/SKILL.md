---
name: organise-solutions
description: "Scans uncommitted competitive programming solution files across the workspace (both in root and platform subdirectories) and checks for unpushed local commits. Uses an ultra-lean sub-orchestrator to evaluate solution completeness and categorize files by platform (LeetCode, Codeforces, AtCoder, OA, Strivers, Misc), moves completed solutions from root to their target platform directories with standardized filenames, verifies and renames solutions already in platform subdirectories, preserves incomplete or WIP solutions in their current locations untouched, and commits + pushes all verified solutions along with any unpushed local commits. Use when organizing, sorting, moving, or cleaning up uncommitted contest or practice problem solutions, including files in root or platform subdirectories, and syncing uncommitted or unpushed solutions. Trigger on mentions of: 'organise solutions', 'organize solutions', 'sort solutions', 'clean up root solutions', 'move completed problems', 'tidy solutions', 'sort cp problems', 'include non committed or non pushed files'. Do NOT use when: modifying problem algorithmic logic, solving new problems from scratch, or when no solution files or unpushed commits exist."
---

# Organise CP Solutions

This skill is a **workspace-specific workflow** for this competitive programming repository. It inspects all uncommitted solution files residing anywhere in the workspace (both root directory and platform subdirectories) as well as unpushed local commits, determines whether each solution is complete or incomplete, moves complete solutions into their target platform directories with standardized naming, verifies in-place solutions already in platform folders, leaves incomplete solutions in their current locations untouched, and stages, commits, and pushes all verified solutions alongside any unpushed local commits.

---

## Architectural Invariant: Ultra-Lean Orchestrator & Sub-Orchestrator Heavy Lifting

> [!IMPORTANT]
> **Minimal Main-Orchestrator Tokens**: The Root/Main Antigravity Agent MUST NOT read multi-file code dumps into its context window. All scanning, code inspection, AST/heuristic evaluation, and platform classification are offloaded to the local sub-orchestrator runner script:
> ```powershell
> node .agents/skills/organise-solutions/scripts/organise.mjs
> ```
> For ambiguous or nuanced cases, the runner delegates inspection to the zero-cost fast-tier subagent (`subagent.js` / Groq LPU / OpenRouter) so primary context remains clean (<600 tokens active state).

---

## Scope & Target Platform Mapping

The organizer inspects:
1. **Uncommitted files in workspace root**: Analyzed for completeness. If complete, moved to destination platform folder. If incomplete, retained untouched in root.
2. **Uncommitted files in subdirectories**: Analyzed for completeness and standardized naming. If complete, verified in place (or renamed if necessary) and queued for commit. If incomplete, preserved untouched in their directory and excluded from staging.
3. **Unpushed local commits**: Checked against remote upstream (`@{u}..HEAD`). Any pending local commits are surfaced and pushed during the push phase.

The workspace categorizes solutions into distinct platform directories:

| Directory | Target Platform & Signatures | Filename Convention |
| :--- | :--- | :--- |
| `leetcode/` | LeetCode (`@lc app=leetcode`, `class Solution`, `leetcode.com`, or problem numbers) | `<number>.<kebab-title>.cpp` / `.py` (e.g. `1248.count-number-of-nice-subarrays.cpp`) |
| `codeforces/` | Codeforces (Round numbers like `2119A`, CF URLs, `#include "./algo/debug.h"`, `lessgo()`) | `<round><letter>_<Title>.cpp` (e.g. `2119A_Add_or_XOR.cpp`) |
| `atcoder/` | AtCoder (`atcoder.jp`, `abc<round><letter>`, `arc...`) | `abc<round><letter>_<Title>.cpp` (e.g. `abc414A_Streamer_Takahashi.cpp`) |
| `oa/` | Online Assessments & Company Contests (`adobe`, `zomato`, `squarepoint`, `google`, `oa`) | `<company>_<problem>.cpp` or `<company>.cpp` (e.g. `zomato_q1.cpp`) |
| `strivers/` | Striver A2Z / SDE Sheet Topic implementations (`...Graph.cpp`, `...DP.cpp`, `striver`) | `<topic><Category>.cpp` (e.g. `cycleInUDGraphBFSDFS.cpp`) |
| `misc_problems/` | Miscellaneous platforms (PrepBit, CodeChef, HackerRank, general practice) | `<Contest/Letter>_<Title>.cpp` (e.g. `A_A_Fun_Contest.cpp`) |

---

## Completeness Criteria

Before any file is moved or committed, the sub-orchestrator rigorously checks completeness:

### Complete Solutions (Eligible for Move, Commit & Push):
1. **Real Implementation Logic**: The core solution function (`lessgo()`, `main()`, or `class Solution` methods) contains substantive problem-solving code (loops, conditionals, algorithms, state transitions) beyond bare boilerplate templates.
2. **No Unresolved WIP Markers**: Contains zero active incomplete indicators such as `// TODO`, `// WIP`, `// INCOMPLETE`, `// UNFINISHED`, `// NOT WORKING`, `// WA`, etc.
3. **Substantive Code Lines**: Exceeds standard template boilerplate threshold (>3 non-trivial logic lines).

### Incomplete Solutions (PRESERVED UNTOUCHED):
1. Empty or placeholder bodies (e.g. `lessgo() { return 0; }` or empty method returning default).
2. Explicit `// TODO`, `// WIP`, `// WA` comments.
3. Half-written logic or template-only files.
4. **Action**: The sub-orchestrator explicitly **skips** these files.
   - If in root: preserved in root untouched.
   - If in a platform folder: preserved in that folder untouched.
   - **Never staged or committed**.

---

## Standard Execution Procedure

### Step 1: Pre-Flight Check & Dry Run (Sub-Orchestrator)
The Main Orchestrator runs the dry-run check:
```powershell
node .agents/skills/organise-solutions/scripts/organise.mjs --dry-run
```
- Scans all uncommitted files across root and subdirectories.
- Checks for unpushed commits ahead of upstream.
- Outputs the planned moves, renames, in-place verifications, incomplete files, and unpushed commits.

### Step 2: Execute File Organization
Run the live organizer:
```powershell
node .agents/skills/organise-solutions/scripts/organise.mjs
```
The script will:
- Move complete solutions from root to their destination folders with standardized names.
- Verify and standardize any complete solutions already in platform directories.
- Leave incomplete solutions untouched in their current locations.
- Output the exact list of files ready for commit, along with recommended `git add`, `git commit`, and `git push` commands.

*(Optional: Use `--commit` and `--push` flags on `organise.mjs` to automate staging, grouping, and pushing directly).*

### Step 3: Target Branch & Trigger `commit-and-push`
> [!NOTE]
> **Branch Invariant**: Competitive programming solutions in this repository are committed directly to `main` and pushed to `origin/main` unless the user explicitly specifies another branch. If currently on a feature or temporary branch, either switch to `main` or merge and sync with `main`.

The Main Orchestrator triggers the `commit-and-push` workflow:
1. Stage **ONLY** verified complete solution files:
   ```powershell
   git add "leetcode/<file>" "codeforces/<file>" ...
   ```
   *(Never run `git add .` or `git add -A`, ensuring incomplete files remain uncommitted!)*
2. Formulate clean, platform-scoped commit message(s) adhering to repo history:
   - For LeetCode: `leetcode solutions (<ids or problem-names>)`
   - For Codeforces: `Codeforces <round> solutions`
   - For AtCoder: `AtCoder ABC <round> solutions`
   - For OA: `Company OA solutions (<companies>)`
   - For Strivers: `Strivers topic solutions`
   - For Misc: `Miscellaneous problem solutions`
3. Push to remote:
   ```powershell
   git push
   ```
   This synchronizes all newly committed solutions along with any previously unpushed local commits to `main`.

### Step 4: Audible Audio Completion Alert
Announce the completion status using `agent-alarm.ps1`:
```powershell
pwsh -File "$env:USERPROFILE\.gemini\config\scripts\agent-alarm.ps1" -Type Success -Message "Completed CP solutions sorted, verified, and pushed. Incomplete solutions preserved untouched."
```

---

## When to Use
- When uncommitted `.cpp`, `.py`, or problem files reside in the root directory or platform subdirectories after contest or practice sessions.
- When unpushed local commits or uncommitted solutions need to be organized and pushed.
- When the user asks to clean up, sort, or organise CP problems.

## When NOT to Use
- When writing or debugging problem algorithms.
- When there are no uncommitted files and no unpushed commits in the workspace.
- When attempting to commit incomplete or work-in-progress code.
