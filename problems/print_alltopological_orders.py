# print all topological orders
# approach is to keep reducing the in-degree and accumulating the nodes

def printAllTopologicalOrdersUtils(n, graph, visited, order):
	for i in graph:
		nodes = []
		if i in visited:
			continue
		if len(graph[i]) == 0:
			order.append(i)
			visited.add(i)
			for j in range(n):
				if i in graph[j]:
					graph[j].remove(i)
					nodes.append(j)
			printAllTopologicalOrdersUtils(n, graph, visited, order)
			for j in nodes:
				graph[j].add(i)
			visited.remove(i)
			order.remove(i)

	if len(order) == n:
		print order

def printAllTopologicalOrders(n, deps):
	graph = {}
	order = []
	visited = set()
	for i in range(n):
		graph[i] = set()
	for u,v in deps:
		graph[u].add(v)
	return printAllTopologicalOrdersUtils(n, graph, visited, order) 

deps = [ [5,2], [5,0], [4,0], [4,1], [2,3], [3,1] ]
printAllTopologicalOrders(6, deps)
