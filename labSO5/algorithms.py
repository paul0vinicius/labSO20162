class Algorithm:
	
  def put(self, frameId):
    pass

  def evict(self):
    pass

  def clock(self):
    pass

  def access(self, frameId, isWrite):
    pass
    
class Fifo(Algorithm):
  def __init__(self):
    self.fifo = []
		
  def put(self, frameId):
    self.fifo.append(frameId)
		
  def evict(self):
    return self.fifo.pop(0)
    
  def access(self, frameId, isWrite):
    return 0
  
	
