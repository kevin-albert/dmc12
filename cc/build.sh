#!/bin/bash

set -ex

cd $(dirname $0)
if [ ! -f out ]
then
    echo Generating build files
    gyp --generator-output=../ -f ninja src/dmc12.gyp
fi

cd out/Default
ninja
