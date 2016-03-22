#!/bin/bash

if [ -a bin/scanner ]; then
    echo "scanner exists"
else
    exit -1;
fi


for f in test_input/test*; do
    in=${f##*/}
    out="_out"
    echo bin/scanner test_input/$in test_output/$in$out
    bin/scanner test_input/$in test_output/$in$out
done
