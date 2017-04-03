# This is the only file you must implement

# This file will be imported from the main code. The PhysicalMemory class
# will be instantiated with the algorithm received from the input. You may edit
# this file as you which

# NOTE: there may be methods you don't need to modify, you must decide what
# you need...
from algorithms import *

class PhysicalMemory:
  ALGORITHM_AGING_NBITS = 8
  """How many bits to use for the Aging algorithm"""

  def __init__(self, algorithm):
    assert algorithm in {"fifo", "nru", "aging", "second-chance"}
    
    self.algorithms = {
      "fifo": Fifo(),
      "nru": NRU(),
      "aging": Aging(),
      "second-chance": SecondChance()
    }

    self.algorithm = self.algorithms[algorithm]

  def put(self, frameId):
    self.algorithm.put(frameId)

  def evict(self):
    return self.algorithm.evict()

  def clock(self):
    return self.algorithm.clock()

  def access(self, frameId, isWrite):
    return self.algorithm.access(frameId, isWrite)