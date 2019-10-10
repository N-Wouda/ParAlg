#!/usr/bin/env bash

# Installs Unity, our testing framework.
cd ~/
git clone "https://github.com/ThrowTheSwitch/Unity.git"
cp Unity/src/*.h -t /usr/local/include
