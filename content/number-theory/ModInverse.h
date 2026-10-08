/**
 * Author: Simon Lindholm
 * Date: 2016-07-24
 * License: CC0
 * Source: Russian page
 * Description: Choose prime mod and LIM<=mod, then run the initialization loop inside setup/main. inverse[i]
 * is valid for 1<=i<LIM; zero has no inverse. Costs $O(LIM)$ time and memory.
 * Status: Works
 * Usage: // Define prime mod and LIM, then run the shown setup loop.
 * ll invOfThree=inverse[3]; // requires LIM>3
 */
#pragma once

// const ll mod = 1000000007, LIM = 200000; ///include-line
ll *inverse = new ll[LIM] - 1;
inverse[1] = 1;
for (int i = 2; i < (LIM); ++i) inverse[i] = mod - (mod / i) * inverse[mod % i] % mod;
