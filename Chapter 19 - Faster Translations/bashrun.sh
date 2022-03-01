#!/bin/bash
echo "Pages, Access 16384 times"

i=1

while [ $i -le 14 ]
do
    echo "$i, $(./tlb $i)"
    i=$(( $i * 2 ));
done
