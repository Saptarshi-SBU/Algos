#
# Find Cheapest Price with at max K stops
#
# - using dfs traversal
# - using dynamic programming approach, similar to Bellman-Ford approach

# https://leetcode.com/submissions/detail/381652437/
#
import sys
import unittest

def dfs(graph, src, dst, visited, left_stops):
    '''
       recursive dfs based solution
    '''
    if left_stops < 0:
        return sys.maxsize
    elif src not in graph:
        return sys.maxsize
    else:
        best_fare = sys.maxsize
        #we do not have negative weights, so re-visiting a visited node, will only increase total cost
        #even if visited edge is not revisited
        visited.add(src)
        for e in graph[src]:
            new_sum = sys.maxsize
            [next_node, cost] = e 
            if next_node == dst:
                new_sum = cost
            elif next_node in visited:
                continue
            else:
                new_sum = dfs(graph, next_node, dst, visited, left_stops - 1)
                if new_sum < sys.maxsize:
                    new_sum = cost + new_sum
            best_fare = min(best_fare, new_sum)
        visited.remove(src)
        return best_fare

def bm(num_vertices, src, dst, flights, max_stops):
    '''
        using dynamic programming, bellman-ford approach
    '''
    # store the distance between current node and the target node
    # and the number of hops required
    graph = {}
    dp = {} # map of distances ordered by hops for every node

    for e in flights:
        [start, next_node, cost] = e 
        if next_node not in graph:
            graph[next_node] = []
        graph[next_node].append([start, cost])

    #for g in graph:
    #    print g, graph[g]

    for i in range(num_vertices):
        dp[i] = {}
        for j in range(max_stops + 1):
            dp[i][j] = sys.maxsize
    # no hop
    dp[src][0] = 0
    for i in range(num_vertices):
        for edge in flights:
            p = edge[0]
            q = edge[1]
            w = edge[2]
            if min(dp[p].values()) < sys.maxsize:
                if q == dst:
                    #print edge, dp[p], dp[q]
                    for key in dp[p]:
                        cost = w + dp[p][key]
                        if cost < dp[q][key]:
                            dp[q][key] = cost
                else:
                    for key in dp[p]:
                        if key + 1 <= max_stops:
                            cost = w + dp[p][key]
                            if cost < dp[q][key + 1]:
                                dp[q][key + 1] = cost
    #print dp
    return min(dp[dst].values())

def find_cheapest_flightI(num_cities, fare_chart, src, dst, max_stops):  
    # create the adjacency list
    graph = {}
    visited = set()

    for e in fare_chart:
        [start, next_node, cost] = e 
        if start not in graph:
            graph[start] = []
        graph[start].append([next_node, cost])

    best_fare = dfs(graph, src, dst, visited, max_stops)
    return best_fare if best_fare < sys.maxsize else -1

def find_cheapest_flightII(num_cities, fare_chart, src, dst, max_stops):  
    best_fare = bm(num_cities, src, dst, fare_chart, max_stops)
    return best_fare if best_fare < sys.maxsize else -1

def findCheapestPrice(n, flights, src, dst, K, dp=False):
    """
    :type n: int
    :type flights: List[List[int]]
    :type src: int
    :type dst: int
    :type K: int
    :rtype: int
    """
    if dp is False:
        return find_cheapest_flightI(n, flights, src, dst, K)
    else:
        return find_cheapest_flightII(n, flights, src, dst, K)

class Tests(unittest.TestCase):

    def test_01(self):
        num_cities = 5
        #fare_chart = [[0,1,5],[1,2,5],[0,3,2],[3,1,2],[1,4,1],[4,2,1]]
        fare_chart = [[0,1,5],[1,2,5],[0,3,2],[3,1,2],[1,4,1],[4,2,1],[1,2,1]]
        src = 0
        dst = 2
        max_stops = 2
        ans1 = findCheapestPrice(num_cities, fare_chart, src, dst, max_stops, False)
        print 'cheapest price I  :{}'.format(ans1)
        ans2 = findCheapestPrice(num_cities, fare_chart, src, dst, max_stops, True)
        print 'cheapest price II :{}'.format(ans2)
        self.assertEqual(ans1, ans2)
        
    def test_02(self):
        num_cities = 17
        fare_chart = [[0,12,28],[5,6,39],[8,6,59],[13,15,7],[13,12,38],[10,12,35],[15,3,23],[7,11,26],[9,4,65],[10,2,38],[4,7,7],[14,15,31],[2,12,44],[8,10,34],[13,6,29],[5,14,89],[11,16,13],[7,3,46],[10,15,19],[12,4,58],[13,16,11],[16,4,76],[2,0,12],[15,0,22],[16,12,13],[7,1,29],[7,14,100],[16,1,14],[9,6,74],[11,1,73],[2,11,60],[10,11,85],[2,5,49],[3,4,17],[4,9,77],[16,3,47],[15,6,78],[14,1,90],[10,5,95],[1,11,30],[11,0,37],[10,4,86],[0,8,57],[6,14,68],[16,8,3],[13,0,65],[2,13,6],[5,13,5],[8,11,31],[6,10,20],[6,2,33],[9,1,3],[14,9,58],[12,3,19],[11,2,74],[12,14,48],[16,11,100],[3,12,38],[12,13,77],[10,9,99],[15,13,98],[15,12,71],[1,4,28],[7,0,83],[3,5,100],[8,9,14],[15,11,57],[3,6,65],[1,3,45],[14,7,74],[2,10,39],[4,8,73],[13,5,77],[10,0,43],[12,9,92],[8,2,26],[1,7,7],[9,12,10],[13,11,64],[8,13,80],[6,12,74],[9,7,35],[0,15,48],[3,7,87],[16,9,42],[5,16,64],[4,5,65],[15,14,70],[12,0,13],[16,14,52],[3,10,80],[14,11,85],[15,2,77],[4,11,19],[2,7,49],[10,7,78],[14,6,84],[13,7,50],[11,6,75],[5,10,46],[13,8,43],[9,10,49],[7,12,64],[0,10,76],[5,9,77],[8,3,28],[11,9,28],[12,16,87],[12,6,24],[9,15,94],[5,7,77],[4,10,18],[7,2,11],[9,5,41]]
        src =13
        dst = 4
        max_stops = 13
        ans1 = findCheapestPrice(num_cities, fare_chart, src, dst, max_stops, False)
        print 'cheapest price I  :{}'.format(ans1)
        ans2 = findCheapestPrice(num_cities, fare_chart, src, dst, max_stops, True)
        print 'cheapest price II :{}'.format(ans2)
        self.assertEqual(ans1, ans2)

    def test_03(self):
        num_cities = 5
        fare_chart = [[0,1,100],[0,2,100],[0,3,10],[1,2,100],[1,4,10],[2,1,10],[2,3,100],[2,4,100],[3,2,10],[3,4,100]]
        src = 0
        dst = 4
        max_stops = 3
        ans1 = findCheapestPrice(num_cities, fare_chart, src, dst, max_stops, False)
        print 'cheapest price I  :{}'.format(ans1)
        ans2 = findCheapestPrice(num_cities, fare_chart, src, dst, max_stops, True)
        print 'cheapest price II :{}'.format(ans2)
        self.assertEqual(ans1, ans2)

    def test_04(self):
        num_cities = 5
        fare_chart = [[4,1,1],[1,2,3],[0,3,2],[0,4,10],[3,1,1],[1,4,3]]
        src = 2
        dst = 1
        max_stops = 1
        ans1 = findCheapestPrice(num_cities, fare_chart, src, dst, max_stops, False)
        print 'cheapest price I  :{}'.format(ans1)
        ans2 = findCheapestPrice(num_cities, fare_chart, src, dst, max_stops, True)
        print 'cheapest price II :{}'.format(ans2)
        self.assertEqual(ans1, ans2)

    def test_05(self):
        num_cities = 5
        fare_chart = [[0,1,5],[1,2,5],[0,3,2],[3,1,2],[1,4,1],[4,2,1]]
        src = 0
        dst = 2
        max_stops = 2
        ans1 = findCheapestPrice(num_cities, fare_chart, src, dst, max_stops, False)
        print 'cheapest price I  :{}'.format(ans1)
        ans2 = findCheapestPrice(num_cities, fare_chart, src, dst, max_stops, True)
        print 'cheapest price II :{}'.format(ans2)
        self.assertEqual(ans1, ans2)

if __name__ == "__main__":
    unittest.main()
