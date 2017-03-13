# coding: utf-8

class fifo:
	def __init__(self):
		self.fifo = []
		
	def evict(self):
		page_id = self.fifo.pop(0)
		put(page_id)
	
		
		
