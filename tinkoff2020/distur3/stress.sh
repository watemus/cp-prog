g++ Bst.cpp -o st
echo "stc"
g++ Br.cpp -o sm
echo "smc"
g++ gen.cpp -o gen
echo "gc"
for i in `seq 1 1000000`; do
    ./gen $i > tst
    echo "test $i"
    ./sm < tst > osm
    ./st < tst > ost
    diff osm ost || break
done
