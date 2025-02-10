import subprocess
import os
import argparse
import shutil

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
    main_commit = subprocess.run(f"git symbolic-ref refs/remotes/origin/HEAD \
    | sed 's@^refs/remotes/origin/@@'",
                                 shell=True, cwd=path, capture_output=True,
                                 text=True).stdout
    
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

def clone_repo(url, path):
    result = run_cmd(f'git clone -q {url} {path}', '.')
    if result != 0:
        raise Exception(f"Failed to clone repository: {url}")
    return path

# input: 
# python3 mini_03.py https://github.com/Werianin/test-repo f92a601b711aecec418d008fc174d9dde08d1a39 f32479a8796d549c3974b4d19b51a8658a9c0643 "python3 main.py"

# output:
# Bad commit: efeac37fa7bddca62ac31c43eb142003ad41958e

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("url")
    parser.add_argument("good")
    parser.add_argument("bad")
    parser.add_argument("test_cmd")
    
    args = parser.parse_args()

    temp_dir = "temp_dir"
    os.mkdir(temp_dir)
    path = clone_repo(args.url, temp_dir)
    git_bisect(path, args.good, args.bad, args.test_cmd)

    shutil.rmtree(path)


