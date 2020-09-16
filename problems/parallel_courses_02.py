#https://leetcode.com/problems/parallel-courses-ii/discuss/713978/Python-intuitive-Bit-mask-DP-Explained-BEST
#
# DAG Scheduling, NP O(2^N * NCK)
# https://leetcode.com/submissions/detail/395362076/
#

import itertools

def minNumberofSemesters(n, dep, k):
	'''
	n  : number of courses
	dep: dependency list
	k  : max courses per semester
	'''
	
	#create adjacency list
	adj = {}
	for i in range(n):
		adj[i] = 0

	for e in dep:
		[u, v] = e
		adj[v - 1] = adj[v - 1] | 1 << (u - 1)

	#store optimal semester count for reaching a course state
	dp = [n] * (1 << n)

	for c_mask in range(1 << n):
		avail = []
		for c in range(n):
			#current course seen before and is satisfied by current mask
			if (((c_mask & (1 << c)) == 0) and (adj[c] & c_mask) == adj[c]):
				avail.append(c) 
				
		for choice in itertools.combinations(avail, min(k, len(avail))):
			next_mask = c_mask
			for c in choice:
				next_mask = next_mask | (1 << c)
			dp[next_mask] = min(dp[next_mask], dp[c_mask] + 1)
	return dp[-1]

n = 4
dependencies = [[2,1],[3,1],[1,4]]
k = 2
print minNumberofSemesters(n, dependencies, k)
