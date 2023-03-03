class _DoubleLinkedBase:
	""" A base class providing a doubly linked list representation."""

	class _Node:
		""" Lightweight, nonpublic class for storing a doubly linked node"""
		__slots__ = '_element', '_prev', '_next' # streamline memory

		def __init__(self, element, prev, next): # initialize node's fields
			self._element = element
			self._prev = prev
			self._next = next

	def __init__(self):
		"""Create an empty list"""
		self._header = self._Node(None, None, None)
		self._trailer = self._Node(None, None, None)
		self._header._next = self._trailer
		self._trailer._prev = self._header
		self._size = 0 # number of elements

	def __len__(self):
		"""Return the number of elements in the list"""
		# ===== Start writing your code here =====
		return self._size
		# ===== End writing your code here =====

	def is_empty(self):
		"""Return true if list is empty"""
		# ===== Start writing your code here =====
		if self._size==0:
			return True
		else:
			return False
		# ===== End writing your code here =====

	def _insert_between(self, e, predecessor, successor):
		"""Add element e between two existing nodes and return new node"""
		newest = self._Node(e, predecessor, successor)
		# ===== Start writing your code here =====
		if(predecessor._next!=successor):
			print("Error: Invalid predecessor and successor, they aren't neighbours")
			dummyNode=self._Node(0, predecessor, successor)
			return dummyNode
		predecessor._next=newest
		successor._prev=newest
		self._size+=1		#update size as we added a node
		return newest
		# ===== End writing your code here =====

	def _delete_node(self, node):
		"""Delete nonsentinel node from the list and return its elements"""
		# ===== Start writing your code here =====
		node._prev._next=node._next		#make connections b/w nodes neighboring the one being removed
		node._next._prev=node._prev
		self._size-=1		#update size as we remove a node
		return node._element
		# ===== End writing your code here =====

n = _DoubleLinkedBase()
n5=n._insert_between(5, n._header, n._trailer)
print(n5._element)

print(n.__len__())

n6=n._insert_between(6, n5, n._trailer)
print(n6._element)

n4=n._insert_between(4, n._header, n5)
print(n4._element)

print(n.__len__())

n9=n._insert_between(9, n5, n6)
print(n9._element)

n9=n._insert_between(9, n5, n6)

ele = n._delete_node(n9)
print(ele)

print(n.is_empty())