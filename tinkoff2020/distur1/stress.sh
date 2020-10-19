g++ gen.cpp -o gen -O2
echo "gc"
g++ Bsm.cpp -o sm -O2
echo "smc"
g++ B.cpp -o st -O2
echo "stc"
for i in `seq 1 1000000`; do
    echo "Test $i"
    ./gen $i > tst
    ./sm < tst > osm
    ./st < tst > ost
    diff osm ost || break
done
