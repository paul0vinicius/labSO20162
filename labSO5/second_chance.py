# coding: utf-8

class second_chance(fifo):
		
	def evict(self):
		page_id = self.fifo.pop(0)
		
		while referenced(page_id):
			referencia(page_id)
			self.fifo.append(page_id)
			page_id = self.fifo.pop(0)
			
		put(page_id)
		return page_id

	def referenced(self, page_id):
		return page_table[page_id][2] # bit r da 4-tupla de cada página
		# deve haver um método na interface para acessar a page_table
		# ou que determina diretamente se a page foi ref ou nao
	
	def referencia(page_id):
		# Corrigir isso para algo que tenha sentido assim que descobrir como verificar o bit R de cada pagina
		page_id.ref = True
	pass
# -------------------------------------------------

  def put(self, frameId):
    """Allocates this frameId for some page"""
    # Notice that in the physical memory we don't care about the pageId, we only
    # care about the fact we were requested to allocate a certain frameId
    
    
    pass

  def evict(self):
    """Deallocates a frame from the physical memory and returns its frameId"""
    # You may assume the physical memory is FULL so we need space!
    # Your code must decide which frame to return, according to the algorithm
    
    page_id = self.fifo.pop(0)
		
	while referenced(page_id):
		atualiza_referencia(page_id)
		self.fifo.append(page_id)
		page_id = self.fifo.pop(0)
		
	put(page_id)
	return page_id
		
    pass

  def clock(self):
    """The amount of time we set for the clock has passed, so this is called"""
    # Clear the reference bits (and/or whatever else you think you must do...)
    
    # Do nothing
    pass

  def access(self, frameId, isWrite):
    """A frameId was accessed for read/write (if write, isWrite=True)"""
    referencia(frame_id)
    pass
    
  

