g++ gen.cpp -o gen -std=c++17 -O2
echo "gc"
g++ Dst.cpp -o st -std=c++17 -O2
echo "stc"
g++ D.cpp -o sm -std=c++17 -O2
echo "smc"

for i in `seq 1 1000000`; do
    echo "Test $i"
    ./gen $i > tst
    ./st < tst > ost
    ./sm < tst > osm
    diff ost osm || break
done
