#!/bin/bash

if [ -z "$1" ];
then
    var2=$PWD
else
    cd $1
fi

var=$(ls)
for file1 in $var;
do
    if [[ -f $file1 ]]
    then
        for file2 in $var;
        do
            if [[ -f $file1 ]]
            then
                if [[ "$file2" = "$file1" ]]
                then
                    continue;
                fi
                if [[ "$file2" < "$file1" ]]
                then
                    continue;
                fi
                    
                if cmp --silent "$file1" "$file2"
                then
                    # echo $file2 "-->" $file1
                    rm $file2
                    ln -s $file1 $file2
                    
                fi
            fi
        done
    fi
done