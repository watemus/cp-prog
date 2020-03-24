#!/bin/bash
for i in `seq 1 100000`; do
  echo "Test $i"
  ./gen $i > tst
  ./sm < tst > osm
  ./st < tst > ost
  diff osm ost || break
  echo "Completed"
done