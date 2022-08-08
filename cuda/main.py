#!venv/bin/python3

import build.foo as foo
print(dir(foo))

from build.foo import FooArray

arr = FooArray(10)
arr.print()
arr.to_device()
arr.print()
arr.increment()
arr.print()
arr.to_host()
arr.print()
