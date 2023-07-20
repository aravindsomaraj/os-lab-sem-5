#!/bin/bash
sed '1d' responses.csv | while IFS="," read time1 email rn1 rn2
do
    a=$(echo $rn1 | cut -d "\"" -f 2)
    b=$(echo $rn2 | cut -d "\"" -f 2)
    
    count1=$(grep -c $a sorted.txt)
    count2=$(grep -c $b sorted.txt)
    
    echo $a >> sorted.txt
    echo $b >> sorted.txt

    if [[ $count1 == 0 ]] && [[ $count2 == 0 ]];
    then

        if [[ $b == "" ]]
        then
            name="${a}"
        elif [[ $a > $b ]]
        then
            name="${b}_${a}"
        else
            name="${a}_${b}"
        fi
    fi
    echo $name >> file.txt

    c1=$(grep -c $a students_list.csv)
    c2=$(grep -c $b students_list.csv)
    
    if [[ $c1 == 0  ]] ||  [[ $c2 == 0 ]];
    then
        echo $name >> invalid.txt
    fi
done

echo $(sort sorted.txt) > sorted.txt
echo "invalid rollnumbers are"
uniq -d sorted.txt | uniq >&2

while read $roll
do
    count=$(grep -c $roll sorted.txt)

    if [ count == 0 ]
    then
        echo $roll
    fi
done < students_list.csv
