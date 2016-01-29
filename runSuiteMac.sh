#!/bin/bash

if [ ${#} -ne 2 ]; then
 echo "Please enter 2 arguments." >&2
 exit 1
fi

while read f; do
 if [ ! -r "${f}.in" ]; then
  echo "${f}.in does not exist or is unreadable." >&2
  exit 1
 fi
 if [ ! -r "${f}.out" ]; then # file is missing .in or .out files 
  echo "${f}.out does not exist or is unreadable." >&2 #to stderr
  exit 1
 fi
done<${1}
while read f; do
 tempfoo=`basename $0`
 temp=`mktemp /tmp/${tempfoo}.XXXXX`
 if [ ! -r "${f}.args" ]; then
  ${2} < ${f}.in > ${temp}
 else
   ${2} `cat ${f}.args` < ${f}.in > ${temp}
 fi
 diff ${f}.out ${temp} > /dev/null 2>&1
if [ ${?} -ne 0 ]; then #test does not pass
     echo "Test failed: ${f}"
     echo "Input:"
     cat ${f}.in
     echo "Expected:"
     cat ${f}.out
     echo "Actual:"
     cat ${temp}
 fi
   rm ${temp}
done < ${1}