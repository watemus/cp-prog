//
// Created by watemus on 26.06.2020.
//

constexpr long double EPS = 1e-10;

template<typename T>
struct FloatEps {
    T val;
    FloatEps(T val) : val(val) {}
    operator T() const {
        return val;
    }
    inline FloatEps& operator+=(FloatEps oth) {
        val += oth.val;
        return *this;
    }
    inline FloatEps& operator-=(FloatEps oth) {
        val -= oth.val;
        return *this;
    }
    inline FloatEps& operator*=(FloatEps oth) {
        val *= oth.val;
        return *this;
    }
    inline FloatEps &operator/=(FloatEps oth) {
        val /= oth.val;
        return *this;
    }
};

template<typename T>
inline FloatEps<T> operator+(FloatEps<T> a, FloatEps<T> b) {
    return a += b;
}

template<typename T>
inline FloatEps<T> operator-(FloatEps<T> a, FloatEps<T> b) {
    return a -= b;
}

template<typename T>
inline FloatEps<T> operator*(FloatEps<T> a, FloatEps<T> b) {
    return a *= b;
}

template<typename T>
inline FloatEps<T> operator/(FloatEps<T> a, FloatEps<T> b) {
    return a /= b;
}

template<typename T>
inline bool operator==(FloatEps<T> a, FloatEps<T> b) {
    return fabs(a.val - b.val) <= EPS;
}

template<typename T>
inline bool operator!=(FloatEps<T> a, FloatEps<T> b) {
    return fabs(a.val - b.val) > EPS;
}

template<typename T>
inline bool operator<(FloatEps<T> a, FloatEps<T> b) {
    return b.val - a.val > EPS;
}

template<typename T>
inline bool operator>(FloatEps<T> a, FloatEps<T> b) {
    return a.val - b.val > EPS;
}

template<typename T>
inline bool operator<=(FloatEps<T> a, FloatEps<T> b) {
    return a < b || a == b;
}

template<typename T>
inline bool operator>=(FloatEps<T> a, FloatEps<T> b) {
    return a > b || a == b;
}

using ldp = FloatEps<long double>;



