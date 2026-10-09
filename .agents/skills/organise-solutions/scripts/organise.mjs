import fs from 'node:fs';
import path from 'node:path';
import { execSync } from 'node:child_process';

const ROOT_DIR = process.cwd();
const SUBAGENT_SCRIPT = path.join(
  process.env.USERPROFILE || '',
  '.gemini',
  'config',
  'scripts',
  'subagent.js'
);

// Known target directories in this repository
const KNOWN_DIRECTORIES = ['leetcode', 'codeforces', 'atcoder', 'oa', 'strivers', 'misc_problems'];
const IGNORED_ROOT_FILES = new Set([
  '.gitignore',
  'makefile',
  'Makefile',
  'README.md',
  '.clang-format',
  'LICENSE',
]);

const IGNORED_DIRS = new Set([
  '.git',
  '.agents',
  '.cph',
  '.vscode',
  'algo',
  'node_modules',
  '.gemini',
  '.idea'
]);

const CODE_EXTENSIONS = new Set(['.cpp', '.cc', '.cxx', '.py', '.java', '.c', '.rs']);

const COMPANY_KEYWORDS = [
  'adobe', 'zomato', 'squarepoint', 'google', 'amazon', 'microsoft',
  'meta', 'uber', 'goldman', 'sprinklr', 'atlassian', 'tower_research',
  'tower', 'deshaw', 'de_shaw', 'cisco', 'salesforce', 'oracle', 'apple',
  'flipkart', 'swiggy', 'morgan_stanley', 'jp_morgan', 'optiver', 'jane_street'
];

function getUncommittedFiles() {
  try {
    const output = execSync('git status --porcelain', { cwd: ROOT_DIR, encoding: 'utf8' });
    const lines = output.split('\n').filter(Boolean);
    const candidateFiles = [];

    for (const line of lines) {
      // porcelain format: XY <path> or XY <orig> -> <path>
      const status = line.slice(0, 2);
      if (status.includes('D')) continue; // Skip deleted files

      let filePath = line.slice(3).trim();
      if (filePath.includes(' -> ')) {
        filePath = filePath.split(' -> ')[1].trim();
      }
      // Remove quotes if present
      if (filePath.startsWith('"') && filePath.endsWith('"')) {
        filePath = filePath.slice(1, -1);
      }

      // Normalize path separators to forward slash
      filePath = filePath.replace(/\\/g, '/');

      // Check if file is in an ignored directory
      const parts = filePath.split('/');
      if (parts.some(p => p.startsWith('.') && p !== '.' && p !== '..')) {
        continue;
      }
      if (parts.length > 1 && IGNORED_DIRS.has(parts[0])) {
        continue;
      }

      const fileName = path.basename(filePath);
      if (IGNORED_ROOT_FILES.has(fileName)) continue;

      const ext = path.extname(fileName).toLowerCase();
      if (!CODE_EXTENSIONS.has(ext)) continue;

      const isRoot = parts.length === 1 || parts[0] === '.';
      candidateFiles.push({
        filePath,
        fileName,
        isRoot,
        currentDir: isRoot ? '.' : parts[0],
      });
    }

    return candidateFiles;
  } catch (err) {
    console.error('Error running git status:', err.message);
    return [];
  }
}

function getUnpushedCommits() {
  try {
    // 1. Try upstream tracking branch
    const upstream = execSync('git rev-parse --abbrev-ref --symbolic-full-name @{u}', {
      cwd: ROOT_DIR,
      encoding: 'utf8',
      stdio: ['pipe', 'pipe', 'ignore'],
    }).trim();

    if (upstream) {
      const output = execSync(`git log ${upstream}..HEAD --oneline`, {
        cwd: ROOT_DIR,
        encoding: 'utf8',
        stdio: ['pipe', 'pipe', 'ignore'],
      }).trim();
      return output ? output.split('\n').filter(Boolean) : [];
    }
  } catch {
    // Upstream not configured or error
  }

  try {
    // 2. Try current branch against origin/<branch>
    const currentBranch = execSync('git branch --show-current', {
      cwd: ROOT_DIR,
      encoding: 'utf8',
      stdio: ['pipe', 'pipe', 'ignore'],
    }).trim();

    if (currentBranch) {
      const output = execSync(`git log origin/${currentBranch}..HEAD --oneline`, {
        cwd: ROOT_DIR,
        encoding: 'utf8',
        stdio: ['pipe', 'pipe', 'ignore'],
      }).trim();
      return output ? output.split('\n').filter(Boolean) : [];
    }
  } catch {
    // Remote branch doesn't exist yet or no remote
  }

  return [];
}

function analyzeCompleteness(content, ext) {
  // 1. Incomplete / WIP comment flags
  const incompleteCommentRegex = /(\/\/|#|\/\*)\s*(TODO|todo|WIP|wip|INCOMPLETE|incomplete|UNFINISHED|unfinished|NOT WORKING|not working|WA|Wrong Answer)\b/i;
  if (incompleteCommentRegex.test(content)) {
    return { isComplete: false, reason: 'Contains explicit TODO/WIP/INCOMPLETE marker' };
  }

  // 2. For C++ with lessgo()
  const lessgoMatch = content.match(/(?:ll|long\s+long|int|void)\s+lessgo\s*\(\s*\)\s*\{([^}]*)\}/s);
  if (lessgoMatch) {
    const body = lessgoMatch[1].replace(/\/\/[^\n]*/g, '').replace(/\/\*.*?\*\//gs, '').trim();
    const nonTrivial = body.replace(/return\s*0\s*;/g, '').replace(/return\s*;/g, '').trim();
    if (nonTrivial.length === 0) {
      return { isComplete: false, reason: 'lessgo() function body is empty or returns 0 with no logic' };
    }
  }

  // 3. For main() function emptiness
  const mainMatch = content.match(/int\s+main\s*\(\s*\)\s*\{([^}]*)\}/s);
  if (mainMatch) {
    const mainBody = mainMatch[1].replace(/\/\/[^\n]*/g, '').replace(/\/\*.*?\*\//gs, '').trim();
    // Strip standard template calls
    const strippedMain = mainBody
      .replace(/You_are_the_best\s*;/g, '')
      .replace(/ios::sync_with_stdio\([^)]*\)\s*;/g, '')
      .replace(/cin\.tie\([^)]*\)\s*;/g, '')
      .replace(/cout\.tie\([^)]*\)\s*;/g, '')
      .replace(/size_t\s+t\s*=\s*\d+\s*;/g, '')
      .replace(/int\s+t\s*=\s*\d+\s*;/g, '')
      .replace(/cin\s*>>\s*t\s*;/g, '')
      .replace(/while\s*\(\s*t--\s*\)\s*lessgo\(\)\s*;/g, '')
      .replace(/while\s*\(\s*t--\s*\)\s*solve\(\)\s*;/g, '')
      .replace(/lessgo\(\)\s*;/g, '')
      .replace(/solve\(\)\s*;/g, '')
      .replace(/return\s*0\s*;/g, '')
      .replace(/return\s*;/g, '')
      .trim();

    // If main has no substantive logic and lessgo is not present or empty
    if (strippedMain.length === 0 && !lessgoMatch) {
      return { isComplete: false, reason: 'main() function is empty boilerplate with no logic' };
    }
  }

  // 4. For LeetCode class Solution
  if (content.includes('class Solution')) {
    if (content.includes('// @lc code=start') && content.includes('// @lc code=end')) {
      const lcPart = content.split('// @lc code=start')[1]?.split('// @lc code=end')[0] || '';
      const cleaned = lcPart
        .replace(/\/\/[^\n]*/g, '')
        .replace(/\/\*.*?\*\//gs, '')
        .replace(/class Solution\s*\{/g, '')
        .replace(/public:/g, '')
        .replace(/return\s*\{\}\s*;/g, '')
        .replace(/return\s*-1\s*;/g, '')
        .replace(/return\s*0\s*;/g, '')
        .replace(/return\s*(?:true|false)\s*;/g, '')
        .replace(/[{};]/g, '')
        .trim();
      if (cleaned.length < 15) {
        return { isComplete: false, reason: 'LeetCode Solution class lacks implementation' };
      }
    }
  }

  // 5. Check substantive code lines (ignore comments, includes, defines, typedefs, blank lines, braces)
  const lines = content.split('\n');
  let substantiveLines = 0;
  for (const rawLine of lines) {
    const line = rawLine.trim();
    if (!line) continue;
    if (line.startsWith('//') || line.startsWith('#') || line.startsWith('/*') || line.startsWith('*')) {
      if (line.startsWith('#include') || line.startsWith('#define') || line.startsWith('#ifndef') || line.startsWith('#else') || line.startsWith('#endif')) {
        continue;
      }
    }
    if (line.startsWith('using namespace') || line.startsWith('typedef') || line === '{' || line === '}' || line === '};') {
      continue;
    }
    substantiveLines++;
  }

  if (substantiveLines < 3) {
    return { isComplete: false, reason: 'File only contains template definitions (<3 substantive lines)' };
  }

  return { isComplete: true, reason: 'Contains functional problem-solving implementation and no WIP markers' };
}

function classifyPlatformAndFilename(fileName, content, currentDir = '.') {
  const lowerName = fileName.toLowerCase();
  const ext = path.extname(fileName);
  const baseNoExt = path.basename(fileName, ext);

  // 1. LeetCode detection
  if (content.includes('@lc app=leetcode') || content.includes('leetcode.com') || content.includes('class Solution') || /^\d+\./.test(fileName) || currentDir === 'leetcode') {
    let standardizedName = fileName;
    const lcIdMatch = content.match(/@lc app=leetcode id=(\d+)/);
    const lcTitleMatch = content.match(/\[\d+\]\s*([^\n\r*]+)/);
    if (lcIdMatch && lcTitleMatch) {
      const id = lcIdMatch[1];
      const titleSlug = lcTitleMatch[1].trim().toLowerCase().replace(/[^a-z0-9]+/g, '-').replace(/^-|-$/g, '');
      standardizedName = `${id}.${titleSlug}${ext}`;
    }
    return { platform: 'leetcode', folder: 'leetcode', filename: standardizedName };
  }

  // 2. AtCoder detection
  const isAtcoderUrl = content.includes('atcoder.jp');
  const abcMatch = baseNoExt.match(/^abc(\d+)([a-zA-Z])(?:_(.*))?$/i) || content.match(/atcoder\.jp\/contests\/abc(\d+)\/tasks\/abc\d+_([a-zA-Z])/i);
  if (isAtcoderUrl || abcMatch || lowerName.startsWith('abc') || lowerName.startsWith('arc') || lowerName.startsWith('agc') || currentDir === 'atcoder') {
    let standardizedName = fileName;
    if (abcMatch) {
      const round = abcMatch[1];
      const letter = abcMatch[2].toUpperCase();
      const existingTitle = abcMatch[3];
      if (existingTitle) {
        standardizedName = `abc${round}${letter}_${existingTitle}${ext}`;
      } else {
        standardizedName = `abc${round}${letter}${ext}`;
      }
    }
    return { platform: 'atcoder', folder: 'atcoder', filename: standardizedName };
  }

  // 3. OA detection
  for (const company of COMPANY_KEYWORDS) {
    if (lowerName.includes(company) || content.toLowerCase().includes(company)) {
      let standardizedName = fileName;
      if (!lowerName.includes(company)) {
        standardizedName = `${company}_${fileName}`;
      }
      return { platform: 'oa', folder: 'oa', filename: standardizedName };
    }
  }
  if (lowerName.startsWith('oa') || lowerName.includes('_oa') || currentDir === 'oa') {
    return { platform: 'oa', folder: 'oa', filename: fileName };
  }

  // 4. Strivers detection
  if (lowerName.includes('striver') || content.toLowerCase().includes('striver') ||
      /(?:Graph|DP|Tree|BinaryTree|BST|Recursion|LinkedList)\.(?:cpp|py)$/i.test(fileName) || currentDir === 'strivers') {
    return { platform: 'strivers', folder: 'strivers', filename: fileName };
  }

  // 5. Codeforces detection
  const cfMatch = baseNoExt.match(/^(\d{3,4})([a-zA-Z]\d*)(?:_(.*))?$/);
  const isCfUrl = content.includes('codeforces.com');
  const isCfPattern = Boolean(cfMatch) || isCfUrl || currentDir === 'codeforces';
  if (isCfPattern) {
    let standardizedName = fileName;
    if (cfMatch) {
      const round = cfMatch[1];
      const letter = cfMatch[2].toUpperCase();
      const title = cfMatch[3];
      standardizedName = title ? `${round}${letter}_${title}${ext}` : `${round}${letter}${ext}`;
    }
    return { platform: 'codeforces', folder: 'codeforces', filename: standardizedName };
  }

  // If typical contest template with debug.h and lessgo(), and single letter problem like A.cpp, B.cpp
  if (/^[A-Z]\d?\.cpp$/i.test(fileName) && content.includes('algo/debug.h')) {
    return { platform: 'codeforces', folder: 'codeforces', filename: fileName, needsSubagent: true };
  }

  // 6. If currently residing in a known directory, retain that directory
  if (KNOWN_DIRECTORIES.includes(currentDir)) {
    return { platform: currentDir, folder: currentDir, filename: fileName };
  }

  // 7. Misc problems default
  return { platform: 'misc_problems', folder: 'misc_problems', filename: fileName };
}

function runSubagentInspection(filePath, fileName, content) {
  if (!fs.existsSync(SUBAGENT_SCRIPT)) {
    return null;
  }
  try {
    const prompt = `Analyze this competitive programming solution file named "${fileName}".
Determine:
1. isComplete: boolean (true if it contains full working logic for a problem, false if empty boilerplate, TODOs, or WIP)
2. platform: string ('codeforces' | 'leetcode' | 'atcoder' | 'oa' | 'strivers' | 'misc_problems')
3. standardizedFilename: string (e.g. 2119A_Problem_Name.cpp, abc414A_Problem_Name.cpp, 1.two-sum.cpp, company_q1.cpp)
4. reason: string (<15 words explanation)

Respond ONLY with valid JSON:
{"isComplete": true/false, "platform": "...", "standardizedFilename": "...", "reason": "..."}`;

    const cmd = `node "${SUBAGENT_SCRIPT}" --task research --query "${prompt.replace(/"/g, '\\"')}" --file "${path.join(ROOT_DIR, filePath)}" --tier fast`;
    const result = execSync(cmd, { cwd: ROOT_DIR, encoding: 'utf8', timeout: 25000 });

    const jsonMatch = result.match(/\{[\s\S]*\}/);
    if (jsonMatch) {
      return JSON.parse(jsonMatch[0]);
    }
  } catch (err) {
    // Subagent failure is non-fatal; fallback to heuristic
  }
  return null;
}

function generateCommitMessage(platform, files) {
  const fileNames = files.map(f => f.filename || path.basename(f.path));
  switch (platform) {
    case 'leetcode': {
      const ids = fileNames.map(f => f.split('.')[0]).filter(id => /^\d+$/.test(id));
      if (ids.length > 0 && ids.length <= 4) {
        return `leetcode solutions (${ids.join(', ')})`;
      }
      return 'leetcode solutions';
    }
    case 'codeforces': {
      const rounds = fileNames.map(f => f.match(/^(\d{3,4}[a-zA-Z]\d*)/)?.[1]).filter(Boolean);
      if (rounds.length > 0 && rounds.length <= 4) {
        return `Codeforces solutions (${rounds.join(', ')})`;
      }
      return 'Codeforces solutions';
    }
    case 'atcoder': {
      const contests = fileNames.map(f => f.match(/^(abc\d+[a-zA-Z])/i)?.[1]?.toUpperCase()).filter(Boolean);
      if (contests.length > 0 && contests.length <= 4) {
        return `AtCoder ABC solutions (${contests.join(', ')})`;
      }
      return 'AtCoder solutions';
    }
    case 'oa': {
      const companies = new Set();
      for (const fn of fileNames) {
        for (const kw of COMPANY_KEYWORDS) {
          if (fn.toLowerCase().includes(kw)) {
            companies.add(kw.charAt(0).toUpperCase() + kw.slice(1));
          }
        }
      }
      if (companies.size > 0) {
        return `Company OA solutions (${Array.from(companies).join(', ')})`;
      }
      return 'Company OA solutions';
    }
    case 'strivers': {
      return 'Strivers topic solutions';
    }
    case 'misc_problems':
    default: {
      return 'Miscellaneous problem solutions';
    }
  }
}

export function organizeFiles({ dryRun = false, forceSubagent = false, commit = false, push = false } = {}) {
  const uncommittedFiles = getUncommittedFiles();
  const unpushedCommits = getUnpushedCommits();

  const summary = {
    totalScanned: uncommittedFiles.length,
    moved: [],
    renamed: [],
    verifiedInPlace: [],
    incomplete: [],
    toCommit: [], // All verified complete solutions ready for commit
    unpushedCommits: unpushedCommits,
    committed: [],
    pushed: false,
    errors: [],
  };

  console.log(`Found ${uncommittedFiles.length} uncommitted file(s) across repository.`);
  if (unpushedCommits.length > 0) {
    console.log(`Found ${unpushedCommits.length} unpushed local commit(s) ahead of remote.`);
  }
  console.log('');

  for (const item of uncommittedFiles) {
    const fullSourcePath = path.join(ROOT_DIR, item.filePath);
    let content = '';
    try {
      content = fs.readFileSync(fullSourcePath, 'utf8');
    } catch (e) {
      summary.errors.push({ file: item.filePath, error: e.message });
      continue;
    }

    const completeness = analyzeCompleteness(content, path.extname(item.fileName));
    let classification = classifyPlatformAndFilename(item.fileName, content, item.currentDir);

    // If ambiguous or explicitly requested, delegate to subagent
    if (forceSubagent || classification.needsSubagent) {
      console.log(`Delegating ambiguous file "${item.filePath}" to Subagent Groq LPU...`);
      const subResult = runSubagentInspection(item.filePath, item.fileName, content);
      if (subResult) {
        if (typeof subResult.isComplete === 'boolean') {
          completeness.isComplete = subResult.isComplete;
          completeness.reason = subResult.reason || completeness.reason;
        }
        if (subResult.platform && KNOWN_DIRECTORIES.includes(subResult.platform)) {
          classification.platform = subResult.platform;
          classification.folder = subResult.platform;
        }
        if (subResult.standardizedFilename) {
          classification.filename = subResult.standardizedFilename;
        }
      }
    }

    if (!completeness.isComplete) {
      summary.incomplete.push({
        file: item.filePath,
        reason: completeness.reason,
        location: item.isRoot ? 'root' : item.currentDir,
      });
      continue;
    }

    // Solution is verified complete
    const targetDir = path.join(ROOT_DIR, classification.folder);
    const targetFilePath = path.join(targetDir, classification.filename);
    const targetRelPath = `${classification.folder}/${classification.filename}`;

    const isCurrentInPlace =
      !item.isRoot &&
      item.currentDir === classification.folder &&
      item.fileName === classification.filename;

    const isRenameInSameDir =
      !item.isRoot &&
      item.currentDir === classification.folder &&
      item.fileName !== classification.filename;

    if (isCurrentInPlace) {
      summary.verifiedInPlace.push({
        file: item.filePath,
        platform: classification.platform,
        reason: completeness.reason,
      });
      summary.toCommit.push({
        path: item.filePath,
        platform: classification.platform,
        filename: item.fileName,
        action: 'verified',
      });
    } else if (isRenameInSameDir) {
      summary.renamed.push({
        original: item.filePath,
        destPath: targetRelPath,
        platform: classification.platform,
        reason: completeness.reason,
      });

      if (!dryRun) {
        try {
          fs.renameSync(fullSourcePath, targetFilePath);
        } catch (err) {
          summary.errors.push({ file: item.filePath, error: err.message });
          continue;
        }
      }

      summary.toCommit.push({
        path: targetRelPath,
        platform: classification.platform,
        filename: classification.filename,
        action: 'renamed',
      });
    } else {
      // Moved from root or from different directory
      summary.moved.push({
        original: item.filePath,
        destPath: targetRelPath,
        platform: classification.platform,
        reason: completeness.reason,
      });

      if (!dryRun) {
        try {
          if (!fs.existsSync(targetDir)) {
            fs.mkdirSync(targetDir, { recursive: true });
          }
          let finalPath = targetFilePath;
          if (fs.existsSync(targetFilePath) && path.resolve(targetFilePath) !== path.resolve(fullSourcePath)) {
            const parsed = path.parse(targetFilePath);
            finalPath = path.join(targetDir, `${parsed.name}_${Date.now().toString().slice(-4)}${parsed.ext}`);
          }
          fs.renameSync(fullSourcePath, finalPath);
        } catch (err) {
          summary.errors.push({ file: item.filePath, error: err.message });
          continue;
        }
      }

      summary.toCommit.push({
        path: targetRelPath,
        platform: classification.platform,
        filename: classification.filename,
        action: 'moved',
      });
    }
  }

  // Handle auto-commit if requested and not in dry-run mode
  if (commit && !dryRun && summary.toCommit.length > 0) {
    console.log('\n--- Committing Verified Solutions ---');
    // Group files by platform
    const platformGroups = new Map();
    for (const item of summary.toCommit) {
      if (!platformGroups.has(item.platform)) {
        platformGroups.set(item.platform, []);
      }
      platformGroups.get(item.platform).push(item);
    }

    for (const [platform, files] of platformGroups.entries()) {
      const pathsToStage = files.map(f => `"${f.path}"`).join(' ');
      const commitMsg = generateCommitMessage(platform, files);
      try {
        execSync(`git add ${pathsToStage}`, { cwd: ROOT_DIR, encoding: 'utf8' });
        execSync(`git commit -m "${commitMsg.replace(/"/g, '\\"')}"`, { cwd: ROOT_DIR, encoding: 'utf8' });
        summary.committed.push({ platform, files: files.map(f => f.path), commitMsg });
        console.log(`✔ Committed [${platform}]: "${commitMsg}" (${files.length} file(s))`);
      } catch (err) {
        summary.errors.push({ action: 'commit', platform, error: err.message });
        console.error(`✖ Failed to commit ${platform}:`, err.message);
      }
    }
  }

  // Handle push if requested and not in dry-run mode
  if (push && !dryRun) {
    const hasPendingPush = summary.committed.length > 0 || unpushedCommits.length > 0;
    if (hasPendingPush) {
      console.log('\n--- Pushing to Remote ---');
      try {
        const currentBranch = execSync('git branch --show-current', { cwd: ROOT_DIR, encoding: 'utf8' }).trim();
        try {
          execSync('git push', { cwd: ROOT_DIR, encoding: 'utf8', stdio: 'inherit' });
        } catch {
          execSync(`git push -u origin ${currentBranch}`, { cwd: ROOT_DIR, encoding: 'utf8', stdio: 'inherit' });
        }
        summary.pushed = true;
        console.log('✔ Successfully pushed to remote.');
      } catch (err) {
        summary.errors.push({ action: 'push', error: err.message });
        console.error('✖ Failed to push:', err.message);
      }
    } else {
      console.log('\nBranch is already up to date with remote; nothing to push.');
    }
  }

  return summary;
}

// Backwards compatibility alias
export const organizeRootFiles = organizeFiles;

// CLI Execution entry point
if (process.argv[1] && path.resolve(process.argv[1]) === path.resolve(new URL(import.meta.url).pathname.replace(/^\/([A-Za-z]:)/, '$1'))) {
  const isDryRun = process.argv.includes('--dry-run');
  const isForceSubagent = process.argv.includes('--subagent');
  const isCommit = process.argv.includes('--commit');
  const isPush = process.argv.includes('--push');

  console.log(`=== Organize CP Solutions (${isDryRun ? 'DRY-RUN' : 'LIVE'}) ===\n`);
  const result = organizeFiles({
    dryRun: isDryRun,
    forceSubagent: isForceSubagent,
    commit: isCommit,
    push: isPush,
  });

  console.log('--- Summary ---');
  if (result.moved.length > 0) {
    console.log(`\n✔ Complete Solutions ${isDryRun ? 'Identified for Move' : 'Moved'}: (${result.moved.length})`);
    for (const m of result.moved) {
      console.log(`  - [${m.platform.toUpperCase()}] ${m.original} -> ${m.destPath}`);
    }
  }

  if (result.renamed.length > 0) {
    console.log(`\n✔ Complete Solutions ${isDryRun ? 'Identified for Rename' : 'Renamed in Place'}: (${result.renamed.length})`);
    for (const r of result.renamed) {
      console.log(`  - [${r.platform.toUpperCase()}] ${r.original} -> ${r.destPath}`);
    }
  }

  if (result.verifiedInPlace.length > 0) {
    console.log(`\n✔ Complete Solutions Verified In-Place: (${result.verifiedInPlace.length})`);
    for (const v of result.verifiedInPlace) {
      console.log(`  - [${v.platform.toUpperCase()}] ${v.file}`);
    }
  }

  if (result.incomplete.length > 0) {
    console.log(`\n⏳ Incomplete / WIP Solutions Preserved Untouched: (${result.incomplete.length})`);
    for (const inc of result.incomplete) {
      console.log(`  - ${inc.file} (${inc.location}): ${inc.reason}`);
    }
  }

  if (result.unpushedCommits.length > 0) {
    console.log(`\n⬆ Unpushed Local Commits Detected: (${result.unpushedCommits.length})`);
    for (const c of result.unpushedCommits) {
      console.log(`  - ${c}`);
    }
  }

  if (result.errors.length > 0) {
    console.log(`\n✖ Errors: (${result.errors.length})`);
    for (const err of result.errors) {
      console.log(`  - ${err.file || err.action}: ${err.error}`);
    }
  }

  if (!isCommit && result.toCommit.length > 0 && !isDryRun) {
    console.log('\n🚀 Ready for commit-and-push:');
    // Group files by platform for display
    const groups = new Map();
    for (const f of result.toCommit) {
      if (!groups.has(f.platform)) groups.set(f.platform, []);
      groups.get(f.platform).push(f.path);
    }
    for (const [platform, paths] of groups.entries()) {
      const quoted = paths.map(p => `"${p}"`).join(' ');
      const msg = generateCommitMessage(platform, paths.map(p => ({ filename: path.basename(p) })));
      console.log(`git add ${quoted}`);
      console.log(`git commit -m "${msg}"`);
    }
    console.log('git push');
  } else if (!isPush && result.unpushedCommits.length > 0 && !isDryRun) {
    console.log('\n🚀 Ready to push unpushed commits:');
    console.log('git push');
  }
}
