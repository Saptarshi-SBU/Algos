#
# Disjoint Set Problem
#  +) DFS
#  +) Union-Find
# https://leetcode.com/submissions/detail/407514942/
# https://leetcode.com/problems/accounts-merge/solution/
#
# initially thought it is a merge-sort problem. But the
# data is in the form of key-value pair
#
class Solution(object):

    def dfs(self, email, graph, visited, result):
    	if email not in graph:
		return
	adj = graph[email]
	for entry in adj:
		if entry in visited:
			continue
		visited.add(entry)
		result.append(entry)
		self.dfs(entry, graph, visited, result)
	return

    def accountsMerge(self, accounts):
        """
        :type accounts: List[List[str]]
        :rtype: List[List[str]]
        """
	graph = dict()
	email_set = set()
	email2name = dict()
	for acc in accounts:
		if acc[1] not in graph:
			graph[acc[1]] = list()
		for email in set(acc[1:]):
			email_set.add(email)
			if email not in graph:
				graph[email] = list()
			graph[email].append(acc[1])
			graph[acc[1]].append(email)
			email2name[email] = acc[0]

	#for g in graph:
	#	print g, graph[g]
	ans = []
	visited = set()
	for email in email_set:
		result = []
		if email not in visited:
			self.dfs(email, graph, visited, result)
			ans.append([email2name[email]] + sorted(result))
	return ans

class DSU(object):

	def __init__(self, n):
		self.ids = range(n)

	def find_parent(self, x):
		if self.ids[x] != x:
			self.ids[x] = self.find_parent(self.ids[x])
		return self.ids[x]
	
	def union(self, x, y):
		self.ids[self.find_parent(x)] = self.find_parent(y)
		
class SolutionII(object):

	def accountsMerge(self, accounts):
		i = 0
		dsu = DSU(100)
		email2id = dict()
		email2name = dict()
		for acc in accounts:
			name = acc[0]
			acc = [x for x in set(acc[1:])]
			for email in acc:
				if email not in email2name:
					email2name[email] = name
				if email not in email2id:
					email2id[email] = i
					i = i + 1
				dsu.union(email2id[acc[0]], email2id[email])
		ans = dict()
		for email in email2name:
			key = dsu.find_parent(email2id[email])
			if key not in ans:
				ans[key] = list()
			ans[key].append(email)
		return [[ email2name[v[0]] ] + sorted(v) for v in ans.values()]

accounts = [
	["John", "johnsmith@mail.com", "john00@mail.com"],
	["John", "johnnybravo@mail.com"],
	["John", "johnsmith@mail.com", "john_newyork@mail.com"],
	["Mary", "mary@mail.com"]
]
rec = Solution().accountsMerge(accounts)
print '####'
for r in rec:
	print r

accounts = [
	["Mary", "mary@mail.com"],
	["JohnB", "johnnybravo@mail.com"],
	["JohnA", "johnsmith@mail.com", "john00@mail.com"],
	["JohnC", "johnsmith@mail.com", "john_newyork@mail.com"]
]
rec = Solution().accountsMerge(accounts)
print '####'
for r in rec:
	print r

accounts = [
	["John", "johnnybravo@mail.com"],
	["John", "johnsmith@mail.com", "john00@mail.com"],
	["John", "johnsmith1@mail.com", "john1_newyork@mail.com"]
]
rec = Solution().accountsMerge(accounts)
print '####'
for r in rec:
	print r

accounts = [
	["John", "johnsmith@mail.com"],
	["John", "johnsmith@mail.com", "john00@mail.com"],
	["John", "johnsmith@mail.com", "john1_newyork@mail.com"]
]
rec = Solution().accountsMerge(accounts)
print '####'
for r in rec:
	print r

accounts = [
	["Gabe","Gabe0@m.co","Gabe3@m.co","Gabe1@m.co"],
	["Kevin","Kevin3@m.co","Kevin5@m.co","Kevin0@m.co"],
	["Ethan","Ethan5@m.co","Ethan4@m.co","Ethan0@m.co"],
	["Hanzo","Hanzo3@m.co","Hanzo1@m.co","Hanzo0@m.co"],
	["Fern","Fern5@m.co","Fern1@m.co","Fern0@m.co"]
]
rec = Solution().accountsMerge(accounts)
print '####'
for r in rec:
	print r

accounts = [
	["Alex","Alex5@m.co","Alex4@m.co","Alex0@m.co"],
	["Ethan","Ethan3@m.co","Ethan3@m.co","Ethan0@m.co"],
	["Kevin","Kevin4@m.co","Kevin2@m.co","Kevin2@m.co"],
	["Gabe","Gabe0@m.co","Gabe3@m.co","Gabe2@m.co"],
	["Gabe","Gabe3@m.co","Gabe4@m.co","Gabe2@m.co"]
]

rec = Solution().accountsMerge(accounts)
print '####'
for r in rec:
	print r

accounts = [
	["David","David0@m.co","David1@m.co"],
	["David","David3@m.co","David4@m.co"],
	["David","David4@m.co","David5@m.co"],
	["David","David2@m.co","David3@m.co"],
	["David","David1@m.co","David2@m.co"]
]

rec = Solution().accountsMerge(accounts)
print '####'
for r in rec:
	print r

rec = SolutionII().accountsMerge(accounts)
print '####'
for r in rec:
	print r
