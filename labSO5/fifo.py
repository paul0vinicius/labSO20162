# coding: utf-8

class fifo:
	def __init__(self):
		self.fifo = []
		
	def evict(self):
		page_id = self.fifo.pop(0)
		put(page_id)
	
		
		
  def put(self, frameId):
    """Allocates this frameId for some page"""
    # Notice that in the physical memory we don't care about the pageId, we only
    # care about the fact we were requested to allocate a certain frameId
    
    return put(frame_id)
    
    pass

  def evict(self):
    """Deallocates a frame from the physical memory and returns its frameId"""
    # You may assume the physical memory is FULL so we need space!
    # Your code must decide which frame to return, according to the algorithm
    
    return self.fifo.pop(0)
    
    pass

  def clock(self):
    """The amount of time we set for the clock has passed, so this is called"""
    # Clear the reference bits (and/or whatever else you think you must do...)
    
    # Do nothing
    
    pass

  def access(self, frameId, isWrite):
    """A frameId was accessed for read/write (if write, isWrite=True)"""
    # Do nothing
    pass
