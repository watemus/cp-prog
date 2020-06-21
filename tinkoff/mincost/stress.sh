g++ B.cpp -o sm -std=c++17
echo "sm ready"
g++ Bst.cpp -o st -std=c++17
echo "st ready"
g++ gen.cpp -o gen -std=c++17
echo "gen ready"

for i in `seq 1 100000`; do
  echo "Test $i"
  ./gen $i > tst
  ./sm < tst > osm
  ./st < tst > ost
  diff osm ost || break
done