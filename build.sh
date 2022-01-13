#! /bin/bash

if [ ! -d build ]
then
    mkdir build
fi

mkdir build
cd build || exit
cmake ..
make -j8
cp "compile_commands.json" ..
