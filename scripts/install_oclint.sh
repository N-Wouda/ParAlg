#!/usr/bin/env bash

# Gets and installs OCLint 0.13 in the home directory
curl -OL https://github.com/oclint/oclint/releases/download/v0.13/oclint-0.13-x86_64-linux-3.13.0-125-generic.tar.gz

mkdir ~/oclint

tar xf oclint-0.13-x86_64-linux-3.13.0-125-generic.tar.gz -C ~/oclint --strip-components=1
rm oclint-0.13-x86_64-linux-3.13.0-125-generic.tar.gz

export OCLINT_HOME="$HOME/oclint"
export PATH="$OCLINT_HOME/bin:$PATH"
