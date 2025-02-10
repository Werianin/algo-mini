import subprocess
import argparse

def run_cmd(cmd, cwd):
    result = subprocess.run(cmd, shell=True, cwd=cwd, stdout=subprocess.DEVNULL,
                            stderr=subprocess.DEVNULL)
    return result.returncode

def get_commit_list(path, good, bad):
    cmd = f'git rev-list {good}..{bad}'
    result = subprocess.run(cmd, shell=True, cwd=path,
                            capture_output=True, text=True)
    commits = result.stdout.strip().split('\n')
    return commits[::-1]

def git_bisect(path, good, bad, test_cmd):
    main_commit = subprocess.run(f'git rev-parse HEAD', shell=True, cwd=path,
                                 capture_output=True, text=True).stdout
    
    commits = get_commit_list(path, good, bad)

    l, r = 0, len(commits) - 1
    while l <= r:
        mid = (l + r) // 2
        commit = commits[mid]

        subprocess.run(f'git checkout {commit}', shell=True, cwd=path,
                       stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

        exit_code = run_cmd(test_cmd, path)
        if exit_code == 0:
            l = mid + 1
        else:
            r = mid - 1

    print(f'Bad commit: {commits[l]}')
    subprocess.run(f'git checkout {main_commit}', shell=True, cwd=path,
                   stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("path")
    parser.add_argument("good")
    parser.add_argument("bad")
    parser.add_argument("test_cmd")
    
    args = parser.parse_args()
    git_bisect(args.path, args.good, args.bad, args.test_cmd)

