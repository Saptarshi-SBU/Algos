/*
 *  Based on Concepts of Connected Graph and Articulation Points
 *  
 *  Existence of even an articulation point means that the graph
 *  can be split into two connected components.
 *
 *  Connected component exists for both undirected and directed graph
 *  In directed graph, there exists strongly connected component which
 *  means every node can reach every other node in the graph.
 *  
 *  Computing an articulation point is based on the following:
 *  
 *  A vertex V is articulation point if, in the DFS tree, there exist
 *  a) at least one child of V whose subtree’s vertices have no back edge to any of the ancestor of V. 
 *  b) the ancestor is not a root node, if it is a root node, it must have two or more independent children.
 *  
 *  A biconnected graph does not have any articulation point 
 *
 * Notes:
 *The depth number for each vertex is calculated as they are visited in the DFS tree. For example, vertex A has a depth number 1 and it denotes that the algorithm visits the vertex A one the very first time in the DFS tree. Similarly, the depth number of vertex B is 2. It depicts that the vertex B is the second vertex the algorithm visited the DFS tree.

Let’s talk about how the algorithm calculates the lowest discovery number for each vertex. The rule is simple: Search the reachable vertices with the back edge and see in which vertex this back edge lands. The lowest discovery number of the current vertex will be equal to the depth of that vertex where the back edge lands.

Let’s say we want to calculate the lowest discovery number for vertex B. The neighbor vertex is D, but it doesn’t have any back edge. So the search goes on and reaches vertex C. Vertex C has a back edge, and it connects to vertex A. The lowest discovery number of B is equal to the depth of A. Therefore the lowest discovery number of B is 1.

We can calculate the lowest discovery number for all other vertices in the DFS tree in a similar way.

Now, to find the articulation points, we need to take a pair of vertices (u, v) where u is the parent of v according to the DFS tree. Let’s start with a random pair of vertices (E, F) where E is the parent of F.

Checking condition: low[F] \geq depth[E] \implies 3 \geq 4 \implies FALSE
Therefore, there is no articulation point here. Now let’s take another pair (D, E) where D is the parent of E.

Checking condition: low[E] \geq depth[D] \implies 3 \geq 3 \implies TRUE
Checking condition 2: D\ is\ not\ a\ root\ \Rightarrow TRUE
Therefore, we can conclude that the vertex D is an articulation point in the graph G_2.

In this way, we can find out all the articulation points in any given graph.

References:
  https://www.baeldung.com/cs/graph-articulation-points
  https://medium.com/@lwmarsh06/articulation-points-in-undirected-graph-441c0db59836
  https://emre.me/algorithms/tarjans-algorithm/

 */ 
#include<set>
#include <map>
#include<tuple>
#include<vector>
#include<iostream>

using namespace std;

tuple<int, int> getStartVertex(vector<vector<int>> &grid) {
	for (size_t i = 0; i < grid.size(); i++) {
		for (size_t j = 0; j < grid[0].size(); j++) {
			if (grid[i][j] == 1)
				return make_tuple(i, j);
		}
	}
	// dummy
	return make_tuple(0, 0);
}

void doDFSVisitor(vector<vector<int>> &grid,
                  set<tuple<int, int>> &visited,
		  int x, int y) {
	vector<vector<int>> dir { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
	visited.insert(make_tuple(x, y));
	for (auto &d : dir) {
		int p = x + d[0];
		int q = y + d[1];
		// boundary cases
		if (p < 0 || p >= grid.size() || q < 0 || q >= grid[0].size())
			continue;
		if (!grid[p][q])
			continue;
		// seen
		if (visited.find(make_tuple(p, q)) != visited.end())
			continue;
		doDFSVisitor(grid, visited, p, q);
	}
}

bool checkSingleIsland(vector<vector<int>> &grid) {
	// check if there are more than one islands
	// in that case, there is no solution.
	set<tuple<int, int>> visited;
	auto origin = getStartVertex(grid);
	#ifdef DEBUG
	std::cout << "origin : " << get<0>(origin) << "," << get<1>(origin) << std::endl;
	#endif
	doDFSVisitor(grid, visited, get<0>(origin), get<1>(origin));
	for (size_t i = 0; i < grid.size(); i++) {
		for (size_t j = 0; j < grid[0].size(); j++) {
			// our DFS did not see it, so there exists multiple graphs/inslands
			// in the grid
			if (grid[i][j] &&
				visited.find(make_tuple(i, j)) == visited.end())
				return false;
			}
	}
	// all '1' elements in the grid were visited
	return true;
}

int CountGridOnes(vector<vector<int>> &grid) {
	int count = 0;
	for (size_t i = 0; i < grid.size(); i++) {
		for (size_t j = 0; j < grid[0].size(); j++) {
			if (grid[i][j])
				count++;
		}
	}
	return count;
}

void getArticulationPointsDFS(vector<vector<int>> &grid,
			      vector<tuple<int, int>> &ap,
			      set<tuple<int, int>> &visited,
			      map<tuple<int, int>, int>& low,
			      map<tuple<int, int>, int>& depth,
			      int x,
			      int y,
			      int h,
			      int rootx,
			      int rooty) {
	vector<vector<int>> dir { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
	visited.insert(make_tuple(x, y));
	depth[make_tuple(x,y)] = h;
	low[make_tuple(x,y)] = h;
	int min_depth = -1;
	#ifdef DEBUG
	std::cout << "traversal entry: " << x << ":" << y << ":" << grid[x][y] << std::endl;
	#endif
	for (auto &d : dir) {
		int p = x + d[0];
		int q = y + d[1];
		// boundary cases
		if (p < 0 || p >= grid.size() || q < 0 || q >= grid[0].size())
			continue;
		if (!grid[p][q])
			continue;
		// seen
		if (visited.find(make_tuple(p, q)) != visited.end()) {
			if (min_depth < 0)
				min_depth = low[make_tuple(p,q)];
			else
				min_depth = min(min_depth, low[make_tuple(p, q)]);
			continue;
		}
		getArticulationPointsDFS(grid, ap, visited, low, depth, p, q, h + 1, rootx, rooty);
		if (min_depth < 0)
			min_depth = low[make_tuple(p,q)];
		else
			min_depth = min(min_depth, low[make_tuple(p,q)]);
		// A vertex V is articulation point if, in the DFS tree, there exist
		// at least one child of V whose subtree’s vertices have no back edge
		// to any of the ancestor of V.
		if ((low[make_tuple(p, q)] >= depth[make_tuple(x, y)]) && !((x == rootx) && (y == rooty))) {
			#if DEBUG
			std::cout << "AP found " << std::endl;
			std::cout << "child index :" << p << "," << q << " parent index :" << x << "," << y << std::endl;
			std::cout << "low_links (child) :" << low[make_tuple(p,q)] << std::endl;
			std::cout << "depth (parent) :" << depth[make_tuple(x,y)] << std::endl;
			#endif
			ap.push_back(make_tuple(x, y));
		}
	}

	if (min_depth >= 0)
		low[make_tuple(x,y)] = min(low[make_tuple(x,y)], min_depth);
}

void getArticulationPoints(vector<vector<int>> &grid,
			   vector<tuple<int, int>> &ap) {
	map<tuple<int, int>, int> depth; //DFS depth
	map<tuple<int, int>, int> low; // ancestor depth, back-edge
	set<tuple<int, int>> visited;
	auto orig = getStartVertex(grid);
        int org_x = std::get<0>(orig), org_y = std::get<1>(orig);
        
        grid[org_x][org_y] = 0;
        // root has connected children
        if (checkSingleIsland(grid)) {
            grid[org_x][org_y] = 1;
            getArticulationPointsDFS(grid, ap, visited, low, depth,
                                 org_x, org_y, 0, org_x, org_y);
        } else {
            grid[org_x][org_y] = 1;
            getArticulationPointsDFS(grid, ap, visited, low, depth,
                                 org_x, org_y, 0, -1, -1);
        }

	#ifdef DEBUG
	for (auto &i : depth) {
		std::cout << std::get<0>(i.first) << " : "
		          << std::get<1>(i.first) << " :"
			  << " depth : " << depth[i.first] << ":"
			  << " low  : " << low[i.first] << std::endl;
	}
	#endif
}            

int minDays(vector<vector<int>> &grid) {
	vector<tuple<int, int>> ap;
	if (!checkSingleIsland(grid)) {
		std::cout << "grid has more than one island" << std::endl;
		return 0;
	}
	// we have single island, compute articulation
	// points from the DFS constructed
	getArticulationPoints(grid, ap);
	if (!ap.empty()) {
		std::cout << "grid has an articulation point:" << ap.size() << std::endl;
		return 1;
	} else { // biconnected graph with no articulation points
		std::cout << "grid is a biconnected graph" << std::endl;
		return CountGridOnes(grid) == 1 ? 1 : 2;
	}
}

void testCase001(void) {
	//two islands
	vector<vector<int>> grid { { 0, 1, 0}, {0, 0, 0}, {0, 1, 0} }; 
	std::cout << __func__ << " minimum days:" << minDays(grid) << " expected: " << 0 << std::endl;
}

void testCase002(void) {
	//one island
	vector<vector<int>> grid { { 0, 1, 0}, {0, 1, 0}, {0, 1, 0} };
	std::cout << __func__ << " minimum days:" << minDays(grid) << " expected: " << 1 << std::endl;
}

void testCase003(void) {
	//biconnected
	vector<vector<int>> grid { { 0, 1, 1}, {0, 1, 1}, {0, 1, 1} };
	std::cout << __func__ << " minimum days:" << minDays(grid) << " expected: " << 2 << std::endl;
}

void testCase004(void) {
	//biconnected
	vector<vector<int>> grid { { 0, 1}, {0, 1} };
	std::cout << __func__ << " minimum days:" << minDays(grid) << " expected: " << 2 << std::endl;
}

void testCase005(void) {
	vector<vector<int>> grid { { 1, 1, 1}, {1, 0, 1}, {1, 1, 1} };
	std::cout << __func__ << " minimum days:" << minDays(grid) << " expected: " << 2 << std::endl;
}

void testCase006(void) {
	vector<vector<int>> grid { { 1, 1, 1}, {1, 0, 1}, {1, 0, 1} };
	std::cout << __func__ << " minimum days:" << minDays(grid) << " expected: " << 1 << std::endl;
}

void testCase007(void) {
	vector<vector<int>> grid { { 1, 0, 0}, {0, 1, 0}, {0, 0, 1} };
	std::cout << __func__ << " minimum days:" << minDays(grid) << " expected: " << 0 << std::endl;
}

void testCase008(void) {
	vector<vector<int>> grid {{0,1,1,0},{0,1,1,0},{0,0,0,0}};
	std::cout << __func__ << " minimum days:" << minDays(grid) << " expected: " << 2 << std::endl;
}

void testCase009(void) {
	vector<vector<int>> grid {{1,1}};
	std::cout << __func__ << " minimum days:" << minDays(grid) << " expected: " << 2 << std::endl;
}

void testCase010(void) {
	vector<vector<int>> grid {{1,0,1,0}};
	std::cout << __func__ << " minimum days:" << minDays(grid) << " expected: " << 0 << std::endl;
}

void testCase011(void) {
	vector<vector<int>> grid {{1,1,0,1,1},
               {1,1,1,1,1},
               {1,1,0,1,1},
               {1,1,0,1,1}};
	std::cout << __func__ << " minimum days:" << minDays(grid) << " expected: " << 1 << std::endl;
}

void testCase012(void) {
	vector<vector<int>> grid {{1,1,0,1,1},
               {1,1,1,1,1},
               {1,1,0,1,1},
               {1,1,1,1,1}};
	std::cout << __func__ << " minimum days:" << minDays(grid) << " expected: " << 2 << std::endl;
}

void testCase013(void) {
	vector<vector<int>> grid {{1,1},{1,0}};
	std::cout << __func__ << " minimum days:" << minDays(grid) << " expected: " << 1 << std::endl;
}

void testCase014(void) {
	vector<vector<int>> grid {{0,1,0},{0,0,0}};
	std::cout << __func__ << " minimum days:" << minDays(grid) << " expected: " << 1 << std::endl;
}

int main(void) {
	testCase001();
	testCase002();
	testCase003();
	testCase004();
	testCase005();
	testCase006();
	testCase007();
	testCase008();
	testCase009();
	testCase010();
	testCase011();
	testCase012();
	testCase013();
	testCase014();
	return 0;
}
