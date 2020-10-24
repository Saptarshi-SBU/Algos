#
# Generate Random Point in a Circle
#
# Using Rejection Sampling
# https://leetcode.com/submissions/detail/412414315/
#
import random

class Solution(object):

    def __init__(self, radius, x_center, y_center):
        """
        :type radius: float
        :type x_center: float
        :type y_center: float
        """
        self.radius = radius
        self.x_center = x_center
        self.y_center = y_center

    def randPoint(self):
        """
        :rtype: List[float]
        """
	while True:
        	x, y = random.uniform(-self.radius, self.radius), random.uniform(-self.radius, self.radius)
		if pow(x, 2) + pow(y, 2) <= pow(self.radius, 2):
        		return [x + self.x_center, y + self.y_center]

obj = Solution(1.0, 0, 0)
for i in range(5):
	print obj.randPoint()

obj = Solution(1.0, 2, 2)
for i in range(5):
	print obj.randPoint()
