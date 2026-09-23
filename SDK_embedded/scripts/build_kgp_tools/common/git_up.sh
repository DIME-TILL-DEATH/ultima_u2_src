#! /bin/sh

git stash         2>&1
git pull          2>&1
git stash apply   2>&1

