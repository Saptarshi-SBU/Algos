#
# Minimum path sum in a matrix without negative numbers
#
# https://stackoverflow.com/questions/13159337/why-doesnt-dijkstras-algorithm-work-for-negative-weight-edges
# Complexity : O((E + V)logV)
#

import sys
import time
import numpy as np

class Node(object):
	def __init__(self, i, j, val):
		self.i = i
		self.j = j
		self.val = val

	def __hash__(self):
		return hash(str(self.i) + str(self.j))

	def __eq__(self, other):
		return isinstance(other, self.__class__) and \
			(self.i == other.i) and (self.j == other.j)

	def __str__(self):
		return 'val={} i={} j={}'.format(self.val, self.i, self.j)

def print_nodes_visited(nodes_visited):
	for i in nodes_visited:
		print ('visited:{}'.format(i))

def compute_min_path_sum(matrix):
	rows = len(matrix)
	cols = len(matrix[0])

	dist = [[]] * rows
	print (dist)
	for i in range(rows):
		dist[i] = [0] * cols
		for j in range(cols):
			dist[i][j] = sys.maxsize
	dist[0][0] = matrix[0][0]

	dir = [ \
		[-1, -1], [-1, 0], [-1, 1], \
		[ 0, -1], [ 0, 1], \
		[ 1, -1], [ 1, 0], [ 1, 1]  \
	]

	q = []
	node = Node(0, 0, matrix[0][0])
	q.append(node)
	nodes_visited = set()
	#O(V)
	while len(q) > 0:
		node = q.pop(0)
		min_node = None
		min_dist = sys.maxsize
		print ('visiting node :{}'.format(node))
		for d in dir:
			x = node.i + d[0]
			y = node.j + d[1]
			#boundary nodes
			if x < 0 or y < 0 or x >= rows or y >= cols:
				continue
			if matrix[x][y] < 0:
				raise Exception("cannot handle negative weights")
			neighbour = Node(x, y, matrix[x][y])
			#check neighbour already in closed set
			if neighbour in nodes_visited: O(logV)
				continue

			next_dist = dist[node.i][node.j] + matrix[x][y]
			#relax neighbour edge weight
			if dist[x][y] > next_dist:
				dist[x][y] = next_dist
			#check whether next_dist is minimum, minimum next_dist can be pre-existing without need for relaxation
			if dist[x][y] < min_dist:
				min_dist = dist[x][y]
				min_node = neighbour
		
		nodes_visited.add(node)
		#print_nodes_visited(nodes_visited)
		if min_node is not None:
			q.append(min_node)
			print ('next_neighbour :{}'.format(min_node))
		#print (dist)
		#print (matrix)
		#time.sleep(1)
	return dist[rows - 1][cols - 1]

# 1,2,3
# 4,5,6
# 7,8,9

if __name__ == "__main__":
	#matrix = [[ 1,2,3 ], [4,5,6], [7,8,9]]
	#matrix = [[ 1,2,3 ], [4,500,6], [7,8,9]]
	#matrix = [[ 1,2,3 ], [4,500,6], [7,8,9]]
	#matrix = [[ 10,2,3 ], [4,500,6], [7,8,9]]
	matrix = np.random.randint(10, size=(3, 3))
	for entry in matrix:
		print(entry)
	print(compute_min_path_sum(matrix))
