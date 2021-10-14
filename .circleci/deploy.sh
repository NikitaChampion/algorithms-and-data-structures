#!/usr/bin/env bash

set -o errexit
set -o nounset
set -o pipefail

if [[ $# -lt 2 ]]; then
    echo "Error: Not enought arguments! $# out of 2 required..."
    exit 1
fi

TARGET_BRANCH=$1
CIRCLE_SHA1=$2

echo "Commit and push..."
git add -fA
git status
git commit -m "Automated deployment to GitHub Pages: ${CIRCLE_SHA1}" --allow-empty
git push origin ${TARGET_BRANCH} --force

echo "Deployed successfully to ${TARGET_BRANCH}!"
