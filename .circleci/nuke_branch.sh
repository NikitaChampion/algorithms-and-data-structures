#!/usr/bin/env bash

set -o errexit
set -o nounset
set -o pipefail

if [[ $# -lt 1 ]]; then
    echo "Error: Not enough arguments! 1 argument was expected..."
    exit 1
fi

TARGET_BRANCH=$1

if git show-ref "refs/heads/${TARGET_BRANCH}"; then
  git branch -D ${TARGET_BRANCH}
fi

git checkout --orphan ${TARGET_BRANCH}
git rm -rf .
git clean -fxd
