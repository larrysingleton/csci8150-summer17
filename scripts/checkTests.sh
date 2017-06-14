#!/bin/bash

# run as follows:
# bash scripts/checkTests.sh

cd output
for test in `ls test?_results.txt`
do

    echo -n "Checking $test..."
    result=`diff $test benchmark/$test`
    if [ ${#result} -eq 0 ]
    then
        echo "passed"
    else
        echo "failed"
    fi

done
