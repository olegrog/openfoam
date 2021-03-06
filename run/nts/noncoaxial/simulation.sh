#!/bin/bash

for c in $*; do
    mkdir -p ../$c
    cp -r * ../$c/
    (
        echo "Simulate for $c"
        cd ../$c
        sed -i~ "2s/5/$c/" noncoaxial-transfinite.geo
        ./Allrun
    )
done
