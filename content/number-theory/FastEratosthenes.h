/**
 * Author: Jakob Kogler, chilli, pajenegod
 * Date: 2020-04-12
 * License: CC0
 * Description: Prime sieve for generating all primes smaller than LIM.
 * Set LIM before compilation and call eratosthenes once. Returns primes in increasing order and
 * fills the global isPrime bitset below LIM. This segmented version skips even candidates to
 * reduce memory traffic; use when generating a large prime list.
 * Time: LIM=1e9 $\approx$ 1.5s
 * Status: Stress-tested
 * Details: Despite its n log log n complexity, segmented sieve is still faster
 * than other options, including bitset sieves and linear sieves. This is
 * primarily due to its low memory usage, which reduces cache misses. This
 * implementation skips even numbers.
 *
 * Benchmark can be found here: https://ideone.com/e7TbX4
 *
 * The line `for (int i=idx; i<S+L; idx = (i += p))` is done on purpose for performance reasons.
 * Se https://github.com/kth-competitive-programming/kactl/pull/166#discussion_r408354338
 * Usage: auto primes=eratosthenes();
 * bool prime=isPrime[97]; // requires LIM>97
 */
#pragma once

const int LIM = 1e6;
bitset<LIM> isPrime;
vector<int> eratosthenes() {
  const int blockSize = (int)round(sqrt(LIM)), oddCount = LIM / 2;
  vector<int> primes = {2}, sieve(blockSize + 1);
  primes.reserve(int(LIM / log(LIM) * 1.1));
  vector<pii> sievingPrimes;
  for (int i = 3; i <= blockSize; i += 2)
    if (!sieve[i]) {
      sievingPrimes.push_back({i, i * i / 2});
      for (int j = i * i; j <= blockSize; j += 2 * i) sieve[j] = 1;
    }
  for (int blockStart = 1; blockStart <= oddCount; blockStart += blockSize) {
    array<bool, blockSize> block{};
    for (auto &[p, nextMultiple] : sievingPrimes)
      for (int i = nextMultiple; i < blockSize + blockStart; nextMultiple = (i += p))
        block[i - blockStart] = 1;
    for (int i = 0; i < (min(blockSize, oddCount - blockStart)); ++i)
      if (!block[i]) primes.push_back((blockStart + i) * 2 + 1);
  }
  for (int i : primes) isPrime[i] = 1;
  return primes;
}
