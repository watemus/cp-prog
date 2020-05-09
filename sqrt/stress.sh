#!/bin/bash

for i in `seq 1 10000`; do
  echo "Test $i"
  ./gen $i > tst
  ./sm < tst > osm
  ./st < tst > ost
  diff ost osm || break
done