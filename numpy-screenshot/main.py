import time
from PIL import ImageGrab
import cv2
import numpy as np

import build.foo as foo
#print(dir(foo))

scale_factor = 0.3
t_secs = 5

print("scale_factor:", scale_factor)
print("t_secs:", t_secs)

count = 0
t1 = time.time()
while time.time() - t1 < t_secs:
    sc = foo.screenshot(scale_factor)
    count += 1
    break
print("\nfoo count:", count)
print("foo FPS:", round(count/t_secs, 1))

count = 0
t1 = time.time()
while time.time() - t1 < t_secs:
    pil_sc = cv2.resize(np.array(ImageGrab.grab(xdisplay="")), (0,0), fx=scale_factor, fy=scale_factor)[:,:,[2,1,0]]
    count += 1
    break
print("\nPIL count:", count)
print("PIL FPS:", round(count/t_secs, 1))

print("foo output shape:", sc.shape)
print("PIL output shape:", pil_sc.shape)

cv2.imshow("foo", sc)
cv2.waitKey()
cv2.destroyAllWindows()

cv2.imshow("PIL", pil_sc)
cv2.waitKey()
cv2.destroyAllWindows()
