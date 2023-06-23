#!/bin/bash
make;
echo "----------step 1----------"
./step1 src1.dat dst1.dat
./step1 src2.dat dst2.dat
echo "----------End step 1----------"
echo

echo "----------step 2----------"
./step2 src1.dat dst1.dat
./step2 src2.dat dst2.dat
echo "----------End step 2----------"
echo

echo "----------step 3----------"
./step3 src1.dat dst1.dat
./step3 src2.dat dst2.dat
echo "----------End step 3----------"
echo

echo "----------step 4----------"
./step4 10
echo "----------End step 4----------"
echo

echo "----------step 5,6----------"
./step56 200 20 .10 19
echo "----------End step 5,6----------"
echo