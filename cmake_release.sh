#!/bin/bash

# configure for debug and for static linked libraries
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -GNinja ..

  
