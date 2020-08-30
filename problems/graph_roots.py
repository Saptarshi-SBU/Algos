#
# program to find roots with minimum height in an undirected graph
#
# https://leetcode.com/problems/minimum-height-trees/
# https://leetcode.com/submissions/detail/388036466/
#
def findMinHeight(graph, u, p):
        h_max = 0
        for v in graph[u]:
            if v == p:
                continue
            h_max = max(h_max, 1 + findMinHeight(graph, v, u))
        return h_max
        
def findMinHeightTrees(n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: List[int]
        """
        graph = {}
        result = []
        visited = {}
        
        #create adjacency list
        for e in edges:
            [u, v] = e
            if u not in graph:
                graph[u] = []
            if v not in graph:
                graph[v] = []
            graph[u].append(v)
            graph[v].append(u)
            
        #compute heights for each node
        for u in graph.keys():
            h_max = 0
            #print '=>u :{}'.format(u)
            visited[u] = findMinHeight(graph, u, None)
            #print '<=u :{} {}'.format(u, visited[u])
            
        #prepare result        
        #print 'visited :{}'.format(visited)
        h_min = min([ visited[u] for u in visited])
        for u in visited:
            if visited[u] == h_min:
                result.append(u)
        return result

if __name__ == "__main__":
    print findMinHeightTrees(4, [[1,0],[1,2],[1,3]])
    print findMinHeightTrees(6, [[3,0],[3,1],[3,2],[3,4],[5,4]])
    print findMinHeightTrees(11, [[4,10],[10,3],[3,9],[9,1],[9,6],[9,8],[1,7],[6,2],[8,5],[5,0]])
