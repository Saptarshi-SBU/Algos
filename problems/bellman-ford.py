#
# BellMan-Ford for Directed Graphs
#
# Complexity : O(EV)
#

import sys

class Edge(object):
	def __init__(self, cost, src, dst):
		self.cost = cost
		self.src = src
		self.dst = dst

	def __str__(self):
		return 'cost={} src={} dst={}'.format(self.cost, self.src, self.dst)

def compute_shortest_path(num_vertices, num_edges, edge_list):
	dist = {}
	graph = {}

	#create the adjacency list based on in-degree
	for i in range(num_edges):
		e = Edge(edge_list[i][2], edge_list[i][0], edge_list[i][1])
		if e.dst not in graph:
			graph[e.dst] = []
		graph[e.dst].append(e)

	#initialize distance matrix
	for v in range(num_vertices):
		if v not in graph:
			dist[v] = 0
		else:
			dist[v] = sys.maxsize

	#relax all possible edges with minimum distance
	for v in range(num_vertices):
		for i in range(num_edges):
			e = Edge(edge_list[i][2], edge_list[i][0], edge_list[i][1])
			if dist[e.src] < sys.maxsize:
				dist[e.dst] = min(dist[e.src] + e.cost, dist[e.dst])
	result = dist[v - 1]

	#check for negative cycle
	for i in range(num_edges):
		e = Edge(edge_list[i][2], edge_list[i][0], edge_list[i][1])
		if dist[e.src] < sys.maxsize:
			dist[e.dst] = min(dist[e.src] + e.cost, dist[e.dst])

	if result > dist[v - 1]:
		print 'negative cycle exists'
		return -1;
	else:
		print dist
		return result

if __name__ == "__main__":
	num_vertices = 4
	num_edges = 5
	edges = [ [0,1,7], [0,3,6], [3,1,9], [3,2,8], [1,2,6] ] 
	result = compute_shortest_path(num_vertices, num_edges, edges)
	print result
