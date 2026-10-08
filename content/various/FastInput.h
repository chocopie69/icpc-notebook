/**
 * Author: chilli
 * License: CC0
 * Source: Own work
 * Description: Read an integer from stdin. Usage requires your program to pipe in
 * input from file.
 * Batch integer input with a known number of values, including optional leading minus signs. gc
 * returns 0 at EOF, but readInt does not report EOF and can loop after input ends. Do not mix it
 * with cin/scanf on the same stream because it buffers ahead.
 * Usage: int n=readInt();
 * vector<int> a(n);
 * for (int &value : a) value=readInt();
 * // Run as: ./a.out < input.txt
 * Time: About 5x as fast as cin/scanf.
 * Status: tested on SPOJ INTEST, unit tested
 */
#pragma once
inline char gc() { // like getchar()
  static char buffer[1 << 16];
  static size_t bufferPos, bufferSize;
  if (bufferPos >= bufferSize) {
    buffer[0] = 0, bufferPos = 0;
    bufferSize = fread(buffer, 1, sizeof(buffer), stdin);
  }
  return buffer[bufferPos++]; // returns 0 on EOF
}
int readInt() {
  int value, digit;
  while ((value = gc()) < 40);
  if (value == '-') return -readInt();
  while ((digit = gc()) >= 48) value = value * 10 + digit - 480;
  return value - 48;
}
