#!/usr/bin/env bash

# Gets and installs a more recent version of CMake.
wget "https://github.com/Kitware/CMake/releases/download/v3.15.4/cmake-3.15.4-Linux-x86_64.tar.gz"
tar -xf "cmake-3.15.4-Linux-x86_64.tar.gz"

# Shorthand links for the new CMake version.
sudo ln -s "${TRAVIS_BUILD_DIR}"/cmake-3.15.4-Linux-x86_64/bin/cmake /home/travis/bin/cmake
sudo ln -s "${TRAVIS_BUILD_DIR}"/cmake-3.15.4-Linux-x86_64/bin/ctest /home/travis/bin/ctest
