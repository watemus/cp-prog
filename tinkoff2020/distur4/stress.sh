g++ C.cpp -o sm -O2 -std=c++17
echo "smc"
g++ Cst.cpp -o st -O2 -std=c++17
echo "stc"
g++ gen.cpp -o gen -O2 -std=c++17
echo "gc"
for i in `seq 1 1000000`; do
	echo "tst $i"
	./gen $i > tst
	./sm < tst > osm
	./st < tst > ost
	diff osm ost || break
done
