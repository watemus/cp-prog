

template<class T, long long MOD>
struct Modular {
    T val;
    Modular(T val) : val(val) {}
    Modular& operator=(T oth) {
        val = oth;
        return *this;
    }
    Modular& operator+=(Modular oth) {
        val += oth.val;
        if (val >= MOD)
            val -= MOD;
        return *this;
    }
    Modular& operator-=(Modular oth) {
        val -= oth.val;
        val += MOD;
        if (val >= MOD)
            val -= MOD;
        return *this;
    }
    Modular& operator*=(Modular oth) {
        val *= oth.val;
        val %= MOD;
    }
    bool operator==(Modular oth) {
        return val == oth.val;
    }
};

template<class T, long long MOD>
Modular<T, MOD> operator+(Modular<T, MOD> a, Modular<T, MOD> b) {
    return a += b;
}

template<class T, long long MOD>
Modular<T, MOD> operator-(Modular<T, MOD> a, Modular<T, MOD> b) {
    return a -= b;
}

template<class T, long long MOD>
Modular<T, MOD> operator*(Modular<T, MOD> a, Modular<T, MOD> b) {
    return a *= b;
}

template<typename T, long long MOD1, long long MOD2, long long MOD3>
struct Triplet {
    Modular<T, MOD1> v1;
    Modular<T, MOD2> v2;
    Modular<T, MOD3> v3;
    Triplet(T val) : v1(val), v2(val), v3(val) {}
    Triplet& operator+=(Triplet oth) {
        v1 += oth.v1;
        v2 += oth.v2;
        v3 += oth.v3;
        return *this;
    }
    Triplet& operator-=(Triplet oth) {
        v1 -= oth.v1;
        v2 -= oth.v2;
        v3 -= oth.v3;
        return *this;
    }
    Triplet& operator*=(Triplet oth) {
        v1 *= oth.v1;
        v2 *= oth.v2;
        v3 *= oth.v3;
        return *this;
    }
    bool operator==(Triplet oth) {
        return v1 == oth.v1 && v2 == oth.v2 && v3 == oth.v3;
    }
};

template<class T, long long MOD1, long long MOD2, long long MOD3>
Triplet<T, MOD1, MOD2, MOD3> operator+(Triplet<T, MOD1, MOD2, MOD3> a, Triplet<T, MOD1, MOD2, MOD3> b) {
    return a += b;
}

template<class T, long long MOD1, long long MOD2, long long MOD3>
Triplet<T, MOD1, MOD2, MOD3> operator-(Triplet<T, MOD1, MOD2, MOD3> a, Triplet<T, MOD1, MOD2, MOD3> b) {
    return a -= b;
}

template<class T, long long MOD1, long long MOD2, long long MOD3>
Triplet<T, MOD1, MOD2, MOD3> operator*(Triplet<T, MOD1, MOD2, MOD3> a, Triplet<T, MOD1, MOD2, MOD3> b) {
    return a *= b;
}

template<int MOD>
using mll = Modular<long long, MOD>;

template<int MOD1, int MOD2, int MOD3>
using tmll = Triplet<long long, MOD1, MOD2, MOD3>;