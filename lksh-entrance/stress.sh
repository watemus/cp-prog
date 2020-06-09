graph_govna++ B.cc -o sm -O2 -std=c++17 -Wall -Wextra -DLOCAL
graph_govna++ Bst.cc -o st -O2 -std=c++17 -Wall -Wextra -DLOCAL
graph_govna++ gen.cc -o gen -O2
for i in `seq 1 10000`; do
  echo "Test $i"
  ./gen $i > input.txt
  ./sm > osm
  ./st > ost
  diff osm ost || break
done