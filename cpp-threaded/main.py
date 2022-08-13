import time

from py_collatz import get_longest_sequence
import build.foo as foo

n = 100000

print(f"PY SOLUTION:")
t1 = time.time()
py_seq = get_longest_sequence(n)
py_len = len(py_seq)
t2 = time.time()
elapsed = t2 - t1
print(f"length={len(py_seq)}, elapsed_secs={round(elapsed, 3)}")

print(f"\nCPP SOLUTION:")
t1 = time.time()
cpp_seq = foo.get_longest_sequence(n)
cpp_len = len(cpp_seq)
t2 = time.time()
elapsed = t2 - t1
print(f"length={len(cpp_seq)}, elapsed_secs={round(elapsed, 3)}")

print(f"\nTHREADED CPP SOLUTION:")
t1 = time.time()
threaded_cpp_seq = foo.get_longest_sequence_threaded(n, 12)
threaded_cpp_len = len(threaded_cpp_seq)
t2 = time.time()
elapsed = t2 - t1
print(f"length={len(threaded_cpp_seq)}, elapsed_secs={round(elapsed, 3)}")

assert py_len == cpp_len == threaded_cpp_len
for p, c, t in zip(py_seq, cpp_seq, threaded_cpp_seq):
    assert p == c == t

print("\nAll asserts passed")
