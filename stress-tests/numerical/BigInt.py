"""Run with Python 3 and g++ installed; no third-party libraries required."""
from pathlib import Path
import os
import random
import subprocess
import tempfile

random.seed(814)
edge = [0, 1, -1, 10**9 - 1, 10**9, 10**18, -2**63, 2**63 - 1]
cases = [(a, b) for a in edge for b in edge if b]
for _ in range(1000):
    a = random.randrange(-10**random.randint(1, 300), 10**random.randint(1, 300))
    b = 0
    while not b:
        b = random.randrange(-10**random.randint(1, 200), 10**random.randint(1, 200))
    cases.append((a, b))
for d in [1, 9, 18, 100, 500, 1500]:
    cases.extend([(10**d - 1, 10**(d//2) + 1), (-10**d + 1, 10**(d//2) + 1)])
with tempfile.TemporaryDirectory() as tmp:
    exe = str(Path(tmp) / ("bigint.exe" if os.name == "nt" else "bigint"))
    subprocess.run(["g++", "-std=c++17", "-O2", str(Path(__file__).with_suffix(".cpp")), "-o", exe], check=True)
    result = subprocess.run([exe, "--driver"], input="".join(f"{a} {b}\n" for a, b in cases),
                            text=True, capture_output=True, check=True)
lines = result.stdout.splitlines()
assert len(lines) == len(cases)
for (a, b), line in zip(cases, lines):
    q = abs(a) // abs(b)
    if (a < 0) != (b < 0):
        q = -q
    assert list(map(int, line.split())) == [a+b, a-b, a*b, q, a-q*b], (a, b, line)
print(f"{len(cases)} cases passed against Python integers")
