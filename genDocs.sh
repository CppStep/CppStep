#!/bin/sh

set -e

# Get the current gh-pages branch
git clone -b gh-pages https://git@$GH_REPO_REF docs

##### Configure git.
# Set the push default to simple i.e. push only the current branch.
git config --global push.default simple
# Pretend to be an user called Travis CI.
git config user.name "Travis CI"
git config user.email "travis@travis-ci.org"

doxygen

cd docs/html

touch .nojekyll

git commit -m "Deploy code docs to GitHub Pages Travis build: ${TRAVIS_BUILD_NUMBER}" -m "Commit: ${TRAVIS_COMMIT}"
git push --force "https://${GH_REPO_TOKEN}@${GH_REPO_REF}"
