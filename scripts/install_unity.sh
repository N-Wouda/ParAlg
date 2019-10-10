#!/usr/bin/env bash

# Installs Unity, our testing framework.
cd ~/
git clone "https://github.com/ThrowTheSwitch/Unity.git"
cmake Unity && make

# Unity's `make install` installs this stuff in an odd place, so better we just
# do this ourselves.
sudo cp Unity/src/*.h -t /usr/include
sudo cp src/libunity.a -t /usr/lib
