#!/usr/bin/env bash

# Gets and installs OCLint 0.13 in the home directory.
curl -OL https://github.com/oclint/oclint/releases/download/v0.13/oclint-0.13-x86_64-linux-3.13.0-125-generic.tar.gz

# Extract into dedicated folder.
mkdir "${TRAVIS_BUILD_DIR}"/oclint
tar xf oclint-0.13-x86_64-linux-3.13.0-125-generic.tar.gz -C  "${TRAVIS_BUILD_DIR}"/oclint --strip-components=1

# Eases access from other scripts.
sudo ln -s "${TRAVIS_BUILD_DIR}"/oclint/bin/oclint /home/travis/bin/oclint
sudo ln -s "${TRAVIS_BUILD_DIR}"/oclint/bin/oclint-json-compilation-database /home/travis/bin/oclint-json-compilation-database

# Just so we have a log entry for this.
oclint -version
