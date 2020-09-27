g++ genA3.cpp -o gen -std=c++17
g++ A3.cpp -o sm -O2 -std=c++17
g++ stupA3.cpp -o st -O2 -std=c++17
echo "compiled"

for i in `seq 1 100000`; do
  echo "Test $i"
  ./gen $i > tst
  ./sm < tst > osm
  ./st < tst > ost
  diff osm ost || break
  echo "completed"
done