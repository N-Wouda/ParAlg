#!/usr/bin/env bash

# Installs Multicore BSP for C in the home directory. This is also where
# CMake looks for it, so it should all work out nicely.
cd ~/
wget "http://www.multicorebsp.com/downloads/c/2.0.4/MulticoreBSP-for-C.tar.xz"
tar xvfJ "MulticoreBSP-for-C.tar.xz"
cd "MulticoreBSP-for-C"
make
