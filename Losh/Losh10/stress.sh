g++ gen.cpp -o gen
echo "gen compiled"
g++ Ast.cpp -o st
echo "st compiled"
g++ A.cpp -o sm
echo "sm compiled"
for i in `seq 1 100000`; do
  echo "Test $i"
  ./gen $i > tst
  ./st < tst > ost
  ./sm < tst > osm
  diff ost osm || break
done