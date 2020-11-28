#include <immintrin.h>
#include <bits/stdc++.h>

unsigned SegMinSum(const unsigned *a, const unsigned *b, int n);
unsigned SegMinSum(unsigned *a, const unsigned *b, int n);

unsigned SegMinSum(unsigned *a, unsigned *b, int n) {
  __m256i sm = _mm256_setzero_si256();
  size_t i = 0;
  for (; i + 8 < n; i += 8) {
    __m256i ca = _mm256_lddqu_si256(reinterpret_cast<const __m256i*>(a + i));
    __m256i cb = _mm256_lddqu_si256(reinterpret_cast<const __m256i*>(b + i));
    sm = _mm256_add_epi32(sm, _mm256_min_epi32(ca, cb));
  }
  unsigned ans = 0;
  for (; i < n; i++) {
    ans += std::min(a[i], b[i]);
  }
  unsigned *arr = reinterpret_cast<unsigned*>(&sm);
  for (i = 0; i < 8; i++) {
    ans += arr[i];
  }
  return ans;
}