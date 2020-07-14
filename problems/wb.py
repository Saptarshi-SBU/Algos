# word segmentation
# python wb.py | grep 'RESULT\|INPUT
#
import copy

class TrieNode(object):

	def __init__(self, word=None):
		self.dict = {}
		self.word = word

	def is_leaf(self):
		if self.word is not None:
			return True if self.word[-1] == '$' else False
		else:
			return False

class Trie(object):

	def __init__(self):
		self.root = TrieNode()
    
	def add2node(self, node, word):
		if word is None or word[0] == '$':
			return

		key = word[0]
		#print key, word
		if key not in node.dict:
			node.dict[key] = TrieNode(word)
			print "==>ADDED {} word: {}".format(node.dict[key], node.dict[key].word)
			return
		else:
			node_word = copy.copy(node.dict[key].word)
			#case I: prefix match
			if len(node_word) == len(word):
				return

			#case II : partial prefix match
			pos = 0
			for x, y in zip(word, node_word):
				if x != y:
					break
				pos = pos + 1

			assert pos > 0
			print "==> add_word split node_word:{} word:{}, pos:{}".format(node_word, word, pos)

			node.dict[key].word = word[0 : pos]
			if word[pos] == '$' or node_word[pos] == '$':
				node.dict[key].word += "$"

			print "UPDATE NODE {}".format(node.dict[key].word)
			node = node.dict[key]

			word1 = node_word[pos : ]
			print "NEXT WORD1 : {}".format(word1)
			self.add2node(node, word1)

			word2 = word[pos : ]
			print "NEXT WORD2 : {}".format(word2)
			self.add2node(node, word2)
			
	def add_word(self, word):
		i = 0
		node = self.root
		print "==> INPUT WORD {}".format(word)
		word  = word + "$"
		self.add2node(node, word)
						
	def match_word(self, word):
		i = 0
		node = self.root
		print "==> MATCHING WORD {}".format(word)
		word  = word + "$"
		while True:
			#print "==> match_word {} {}".format(i, word)
			key = word[0]
			if key not in node.dict:
				return False
			else:
				pos = 0
				cur_word = node.dict[key].word
				if len(cur_word) == len(word):
					return True
				for x, y in zip(word, cur_word):
					if x != y:
						break
					pos = pos + 1
				#split
				#print "==> match_word split cur_word:{} word:{}, pos:{}".format(cur_word, word, pos)
				#print "<== match_word node_word:{}".format(node.dict[key].word)
				word = word[pos :]
				node = node.dict[key]

	def print_word(self, node=None, prefix=None):
                if node is None:
                    node = self.root
                print node.dict.keys()
            	for key in node.dict:
			if prefix is None:
				print "ITEMS", node.dict[key], node.dict[key].word
                    		if node.dict[key].is_leaf():
					self.print_word(node.dict[key], node.dict[key].word[0 : -1])
				else:
					self.print_word(node.dict[key], node.dict[key].word)
			else:
				print "ITEMS", node.dict[key], prefix + node.dict[key].word
                    		if node.dict[key].is_leaf():
					self.print_word(node.dict[key], prefix + node.dict[key].word[0 : -1])
				else:
					self.print_word(node.dict[key], prefix + node.dict[key].word)

def prefix_match(p, q):
	pos = 0
	match = False
	print p, q
	for x, y in zip(p, q):
		if x != y:
			break
		pos = pos + 1
		match = True
	print pos
	return pos if match is True else -1

def segment_word(node, word, prefix, index, word_segments, root):
	org_word = copy.copy(word)
	next_node = copy.copy(node)

	if len(word) == 0:
		return

	key = word[0]
	#print "KEYS", key, next_node.dict.keys()
	if key not in next_node.dict:
		print "NO MATCH :", prefix + word
		return

	node_word = next_node.dict[key].word
	print "CURR NODE WORD:", node_word, "LOOKUPWORD:", word
	if word == node_word[-1]:
		if prefix + word not in word_segments[index]:
			word_segments[index].append(prefix + word)
		print "MATCH"
		return

	print "MATCHING PREFIXES"
	pos = prefix_match(word, node_word)
	assert pos >= 0, "cannot be -ve since we did a key based look-up"

	#    pos < word_len    
	#    pos < node_word_len
	#     - partial match : advance word

	#    hit
	#    pos == word_len    
	#    pos < node_word_len
	#     - match

	#    pos < word_len    
	#    pos == node_word_len
	#     - partial match

	#word matches with a segment in the trie
	if pos == len(node_word) - 1:
		assert node_word[pos] == '$'
		print 'SEGMENT MATCH', prefix + node_word, pos, "NEXT INDEX", index + len(prefix) + pos
		if prefix + word[0 : pos] not in word_segments[index]:
			word_segments[index].append(prefix + word[0 : pos])
		#Look for other matching candidates as well
		segment_word(root,
			     word[pos :],
			     '', #dropped prefix
			     index + len(prefix) + pos,#new index
			     word_segments, root)

	#there is a possibility that we can extend the trie-search from this node
	#DFS for the rest of the word
	segment_word(next_node.dict[key],
		     word[pos :],
		     prefix + word[0 : pos], #continue the prefix, since we did not find the break
		     index,
		     word_segments, root)

def print_word_segments(word_segs, wb_list, index):
	if index not in word_segs:
		return
	for w in word_segs[index]:
		print index, len(w)
		if index + len(w) == len(word_segs):
			wb_list.append(w)
			print "RESULT :", wb_list
			wb_list.pop()
		else:
			wb_list.append(w)
			print_word_segments(word_segs, wb_list, index + len(w))	
			wb_list.pop()
'''
obj_trie = Trie()

obj_trie.add_word("Hello")
assert obj_trie.match_word("Hello")
assert obj_trie.match_word("Hell") is False

obj_trie.add_word("Gell")
assert obj_trie.match_word("Gell")
assert obj_trie.match_word("ell") is False

obj_trie.add_word("Gello")
assert obj_trie.match_word("Gello")

obj_trie.print_word()
'''

'''
obj_trie2 = Trie()
word_list = [ "cats", "and", "dogs", "a", "acats", "act" ]
for w in word_list:
    obj_trie2.add_word(w)
obj_trie2.print_word()
'''

'''
obj_trie3 = Trie()
word_list = [ "a", "aa", "aaa", "aaaa", "aaaaa", "aaaaaa", "aaaaaaa" ]
word_list = word_list + [ "b", "bb", "bbb", "bbbb", "bbbbb", "bbbbbb", "bbbbbbb" ]
word_list = word_list + [ "ab", "abab", "ababab", "abababab", "ababababab", "abababababab", "ababababbabab" ]
for w in word_list:
    obj_trie3.add_word(w)
obj_trie3.print_word()
print obj_trie3.match_word("ababab")
'''
obj_trie4 = Trie()
word_list = [ "cats", "and", "dogs", "a", "acats", "act" ]
word_list = word_list + [ "raja", "rimpi", "lokhi" ]
word_list = word_list + [ "a", "aa", "aaa", "aaaa", "aaaaa", "aaaaaa", "aaaaaaa" ]
for w in word_list:
    obj_trie4.add_word(w)
obj_trie4.print_word()

word = "catsand"
word = "rajalokhirimpi"
word = "acats"
word = "aaaaaaa"
word_segs = {}
for i in range(len(word)):
	word_segs[i] = []
segment_word(obj_trie4.root, word, '', 0, word_segs, obj_trie4.root)
for i in range(len(word_segs)):
	print word_segs[i]
wb_list = []
print "INPUT", word
print_word_segments(word_segs, wb_list, 0)
