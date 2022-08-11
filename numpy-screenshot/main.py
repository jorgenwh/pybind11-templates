import cv2

import build.foo as foo
print(dir(foo))

img = foo.screenshot()
print(img.shape)


cv2.imshow("img", img)
cv2.waitKey()
