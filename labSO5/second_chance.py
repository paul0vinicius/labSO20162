# coding: utf-8

class second_chance(fifo):
		
	def evict(self):
		page_id = self.fifo.pop(0)
		
		while referenced(page_id):
			atualiza_referencia(page_id)
			self.fifo.append(page_id)
			page_id = self.fifo.pop(0)
			
		put(page_id)
		return page_id
