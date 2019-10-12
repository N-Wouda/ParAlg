#!/usr/bin/env bash

# Gets and installs OCLint 0.13 in the home directory.
curl -OL https://github.com/oclint/oclint/releases/download/v0.13/oclint-0.13-x86_64-linux-3.13.0-125-generic.tar.gz

mkdir "${TRAVIS_BUILD_DIR}"/oclint

tar xf oclint-0.13-x86_64-linux-3.13.0-125-generic.tar.gz -C ~/oclint --strip-components=1

# Just so we have a log entry for this.
"${TRAVIS_BUILD_DIR}"/oclint/bin/oclint -version
