g++ DF.cpp -o sm
g++ D.cpp -o st
g++ gen.cpp -o gen
for i in `seq 1 10000`; do
  echo "Test $i"
  ./gen $i > tst
  ./sm < tst > osm
  ./st < tst > ost
  diff osm ost || break
done
