class Algorithm:

  def __init__(self):
    pass
	
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

class SecondChance(Algorithm):
  global REFERENCED
  global NOT_REFERENCED
  REFERENCED = 1
  NOT_REFERENCED = not REFERENCED

  def __init__(self):
    self.fifo = []

  def put(self, frameId):
    self.fifo.append([frameId, REFERENCED])

  def evict(self):
    pageFrame = self.fifo.pop(0)

    while pageFrame[1]: # Enquanto a pagina estiver referenciada
      self.fifo.append([pageFrame[0], NOT_REFERENCED])
      pageFrame = self.fifo.pop(0)

    return pageFrame[0]

  def access(self, frameId, isWrite):
    for f_id in self.fifo:
      if frameId == f_id[0]:
        f_id[1] = REFERENCED

class NRU(Algorithm):
  global REFERENCED
  global NOT_REFERENCED
  global MODIFIED
  global NOT_MODIFIED
  REFERENCED = 1
  NOT_REFERENCED = not REFERENCED
  MODIFIED = 1
  NOT_MODIFIED = not MODIFIED

  def __init__(self):
    self.page_frames = []

  def put(self, frameId):
    self.page_frames.append([frameId, REFERENCED, MODIFIED])

  def evict(self):
    self.page_frames.sort(key=lambda pf: pf[1])
    self.page_frames.sort(key=lambda pf: pf[0])

    return self.page_frames.pop(0)[0]

  def clock(self):
    for p_frame in self.page_frames:
      p_frame[1] = NOT_REFERENCED

  def access(self, frameId, isWrite):
    for p_frame in self.page_frames:
      if p_frame[0] == frameId:
        p_frame[1] = REFERENCED
        p_frame[2] = isWrite


class Aging(Algorithm):
  global REFERENCED
  global NOT_REFERENCED
  REFERENCED = 1
  NOT_REFERENCED = not REFERENCED

  def __init__(self):
    self.page_frames = []

  def put(self, frameId):
    self.page_frames.append([frameId, 0])

  def evict(self):
    self.page_frames.sort(key=lambda pf: pf[1])

    return self.page_frames.pop(0)[0]

  def clock(self):
    for p_frame in self.page_frames:
      p_frame[1] >>= 1

  def access(self, frameId, isWrite):
    for p_frame in self.page_frames:
      if p_frame[0] == frameId:
        p_frame[1] >>= 1
        p_frame[1] | 128