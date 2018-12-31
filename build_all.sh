#! /bin/bash
for dir in `find . -type d -name 'Ex*'`; do
    cd ${dir}
    make
    cd ..
done