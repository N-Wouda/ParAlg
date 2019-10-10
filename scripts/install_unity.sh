#!/usr/bin/env bash

# Installs Unity, our testing framework.
cd ~/
git clone "https://github.com/ThrowTheSwitch/Unity.git"

cmake Unity

echo "ls Current"
ls

echo "ls Unity"
ls Unity

sudo cp bin/*.h /usr/include
sudo cp lib/*.a /usr/lib
