#!/usr/bin/env bash

# Installs Unity, our testing framework.
cd ~/
git clone "https://github.com/ThrowTheSwitch/Unity.git"

ls
ls Unity/src

cp "Unity/src/*.h" "/usr/local/include"
