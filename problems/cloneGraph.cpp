/*-----------------------------------------------------------------------------
 * Copyright (C) 2017, Saptarshi Sen
 *
 * Algorithm : Clone a graph using DFS
 *
 * https://leetcode.com/submissions/detail/101405976/
 * ---------------------------------------------------------------------------*/

#include <vector>
#include <unordered_map>

struct UndirectedGraphNode {
   int label;
   vector<UndirectedGraphNode *> neighbors;
   UndirectedGraphNode(int x) : label(x) {};
};

class Solution {

public:

    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        unordered_map<int, UndirectedGraphNode*> visited;
        return (node == NULL) ? NULL : cloneGraphMain(node, visited);
    }

    UndirectedGraphNode *cloneGraphMain(UndirectedGraphNode *node,
        unordered_map<int, UndirectedGraphNode*>& visited) {
        // Fix : Use map to store new allocated cloned nodes.
        // I was returning the original node here.
        if (visited.find(node->label) != visited.end()) {
            return visited[node->label];
        }

        auto clone = new UndirectedGraphNode(node->label);
        // Fix : Update the visited prior doing DFS for adjacent nodes
        visited[clone->label] = clone;

        if (!(node->neighbors.empty())) {
           auto adjNodeList = node->neighbors;
           for (auto iter = adjNodeList.begin(); iter != adjNodeList.end(); iter++) {
              clone->neighbors.push_back(cloneGraphMain(*iter, visited));
           }
        }
        return clone;
    }
};
