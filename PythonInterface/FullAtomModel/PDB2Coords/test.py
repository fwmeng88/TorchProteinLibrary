import sys
import os
import matplotlib.pylab as plt
import numpy as np
import mpl_toolkits.mplot3d.axes3d as p3
import seaborn as sea

import torch
from PDB2Coords import PDB2CoordsBiopython

if __name__=='__main__':
    # coords = torch.DoubleTensor(3*1309)
    # cppPDB2Coords.PDB2Coords("TestFig/2lzm.pdb", coords)

    p2c = PDB2CoordsBiopython()
    coords, res, anames, num_atoms = p2c(["f4TQ1_B.pdb"], ["A"])
    print (coords.size())
    print (res.size())
    print (anames.size())
    print (num_atoms)

    coords = coords.numpy()
    coords = coords.reshape(int(coords.shape[1]/3), 3)
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    x = coords[:,0]
    y = coords[:,1]
    z = coords[:,2]
    ax.scatter(x,y,z)
    plt.show()
