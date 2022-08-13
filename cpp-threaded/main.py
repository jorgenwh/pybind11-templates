import time

from py_collatz import get_longest_sequence
import build.foo as foo

n = 500000

print(f"PY SOLUTION:")
t1 = time.time_ns()
py_seq = get_longest_sequence(n)
py_len = len(py_seq)
t2 = time.time_ns()
elapsed = t2 - t1
print(f"length={len(py_seq)}, elapsed_ns={elapsed}")

print(f"\nCPP SOLUTION:")
t1 = time.time_ns()
cpp_seq = foo.get_longest_sequence(n)
cpp_len = len(cpp_seq)
t2 = time.time_ns()
elapsed = t2 - t1
print(f"length={len(cpp_seq)}, elapsed_ns={elapsed}")

print(f"\nTHREADED CPP SOLUTION:")
t1 = time.time_ns()
threaded_cpp_seq = foo.get_longest_sequence_threaded(n, 12)
threaded_cpp_len = len(threaded_cpp_seq)
t2 = time.time_ns()
elapsed = t2 - t1
print(f"length={len(threaded_cpp_seq)}, elapsed_ns={elapsed}")

assert py_len == cpp_len == threaded_cpp_len
for p, c, t in zip(py_seq, cpp_seq, threaded_cpp_seq):
    assert p == c == t

print("\nAll asserts passed")
