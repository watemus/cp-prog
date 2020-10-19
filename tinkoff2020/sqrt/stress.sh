g++ genb.cpp -o gen -O2 -std=c++17
echo "gc"
g++ B.cpp -o sm -O2 -std=c++17
echo "smc"
g++ Bst.cpp -o st -O2 -std=c++17
echo "stc"
for i in `seq 1 100000`; do
    echo "test $i"
    ./gen $i > tst
    ./sm < tst > osm
    ./st < tst > ost
    diff osm ost || break
done
