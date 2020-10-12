#!/bin/sh

echo "resetting project..."

rm -rf build
rm -f src/*.cpp
rm -f src/*.h

cp ./init_src/*.* src/
