#
# Minimum Spanning Tree using Prim's Algorithm
#
# https://bradfieldcs.com/algos/graphs/prims-spanning-tree-algorithm/
# Prim's Algorithm
# Complexity : O((E + V)logV)
#

import time
import heapq

class Edge(object):
	def __init__(self, cost, p, q):
		self.cost = cost
		self.p = p
		self.q = q

	def __str__(self):
		return 'cost={} p={} q={}'.format(self.cost, self.p, self.q)

def compute_mst(num_vertices, num_edges, edge_list):
	mst = []
	graph = {}
	edges = []
	visited = set()

	#create the adjacency list
	for i in range(num_edges):
		e = Edge(edge_list[i][2], edge_list[i][0], edge_list[i][1])
		if e.p not in graph:
			graph[e.p] = []
		graph[e.p].append(e)

		if e.q not in graph:
			graph[e.q] = []
		graph[e.q].append(e)

	v = 0
	while len(visited) < num_vertices:
		#print v
		for e in graph[v]:
			if e.p not in visited and e.q not in visited:
				heapq.heappush(edges, (e.cost, e.p, e.q))
		visited.add(v)

		if len(edges) > 0:
			#print [ str(e) for e in edges ]
			(cost, p, q) = heapq.heappop(edges)
			mst.append((cost, p, q))
			v = q 
		else:
			break
		print 'visited :{}'.format(visited)
		print 'mst :{}'.format([ str(e) for e in mst ])
		time.sleep(1)
	return mst

if __name__ == "__main__":
	num_vertices = 4
	num_edges = 5
	edges = [ [0,1,7], [0,3,6], [3,1,9], [3,2,8], [1,2,6] ] 
	result = compute_mst(num_vertices, num_edges, edges)
	print [ str(e) for e in result ]
