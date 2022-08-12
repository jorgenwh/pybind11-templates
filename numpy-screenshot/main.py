import cv2
import numpy as np

import build.foo as foo
print(dir(foo))

print(foo.__doc__)

fooshot = foo.screenshot()
print(fooshot.shape)

cv2.imshow("fooshot", fooshot)
cv2.waitKey()
cv2.destroyAllWindows()
