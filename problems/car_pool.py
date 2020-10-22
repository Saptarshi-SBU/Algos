#
# Car Pool Capacity Problem 
#
# Complexity : O(NlogN), Space Complexity O(N)
#

import heapq

def carPooling(trips, capacity):
	i = 0
	# to track elapsed intervals based on end-time or drop-offs
	end_heap = []
	# sort based on start time
	trips = sorted(trips, key = lambda x : (x[1],x[2]))
	# scan trips
	curr_cap = capacity
	while i < len(trips):
		print 'trip : {}'.format(trips[i])
		n = trips[i][0]
		if n > capacity:
			return False
		if i > 0:
			# we have a merge look up heap for any lapsed intervals
			while len(end_heap) > 0:
				(end, count) = end_heap[0]
				if end <= trips[i][1]:
					# bump capacity
					curr_cap += count
					heapq.heappop(end_heap)
				else:
					break
			
			if n > curr_cap:
				return False

		curr_cap = curr_cap - n
		curr_beg = trips[i][1]
		curr_end = trips[i][2]
		heapq.heappush(end_heap, (curr_end, n))
		i = i + 1
	return True

def test_case_001():
	trips = [[3,2,7],[3,7,9],[8,3,9]]
	capacity = 11
	assert True == carPooling(trips, capacity)
