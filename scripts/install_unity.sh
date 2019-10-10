#!/usr/bin/env bash

# Installs Unity, our testing framework.
git clone "https://github.com/ThrowTheSwitch/Unity.git"
git pull

mv "Unity/src/*.h" "/usr/local/include"
