#!/bin/bash

if [ -a bin/parser ]; then
    echo "parser exists"
else
    echo "parser not found"
    exit -1;
fi


for f in test_input/test*; do
    in=${f##*/}
    out="_out"
    echo bin/parser  test_output/$in$out
    bin/parser  test_output/$in$out
done
