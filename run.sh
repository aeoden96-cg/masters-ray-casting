#!/bin/bash

if [ "$1" = "build" ] ; then
  cd build
  cmake ..
  make clean
  make
  cd ..

elif [ -n "$1" ] ; then
  # print usage
  echo "Usage:     ./run.sh       - to run   the project"
  echo "           ./run.sh build - to build the project"

fi

# run the project
cd build
./PROJECT > image.ppm
pnmtopng image.ppm > ../result.png
rm image.ppm
cd ..



