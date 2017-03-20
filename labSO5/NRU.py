# coding: utf-8



class NRU:
	def __init__(self):
		self.cases = {	0: not_r_not_m,
						1: not_r_m,
						2: r_not_m,
						3: r_m
		}
		# uma ideia seria guardar 4 listas separadas (1 pra cada caso) e 
		# ir operando (rm, add, swap) nessas listas de acordo com a prioridade das listas e
		# a ordem de uso das paginas
		
		self.not_r_not_m = []
		self.not_r_m = []
		self.r_not_m = []
		self.r_m = []
		
		# outra, seria assiociar a cada page_frame um inteiro de prioridade/status
		# que determinaria que paginas devem sair da memoria
		
		
	def evict():
		return self.cases[case]()

	def not_r_not_m(self):
		page_id = ?
		return page_id
		
	def not_r_m(self):
		page_id = ?
		return page_id
		
	def r_not_m(self):
		page_id = ?
		return page_id
		
	def r_m(self):
		page_id = ?
		return page_id
		
  def put(self, frameId):
    """Allocates this frameId for some page"""
    # Notice that in the physical memory we don't care about the pageId, we only
    # care about the fact we were requested to allocate a certain frameId
    pass

  def evict(self):
    """Deallocates a frame from the physical memory and returns its frameId"""
    # You may assume the physical memory is FULL so we need space!
    # Your code must decide which frame to return, according to the algorithm
    pass

  def clock(self):
    """The amount of time we set for the clock has passed, so this is called"""
    # Clear the reference bits (and/or whatever else you think you must do...)
    pass

  def access(self, frameId, isWrite):
    """A frameId was accessed for read/write (if write, isWrite=True)"""
    pass
