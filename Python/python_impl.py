import numpy as np
import math

def faster_bilinear(Z, x0, y0):
    i, j = int(math.floor(x0)), int(math.floor(y0))
    XT, YT = (x0 - i), (y0 - j)
    result = (1 - YT) * (1 - XT) * Z[i, j]
    nx, ny = Z.shape

    if i + 1 < nx:
        result = result + (1 - YT) * XT * Z[i + 1, j]
    if j + 1 < ny:
        result = result + YT * (1 - XT) * Z[i, j + 1]
    if i + 1 < nx and j + 1 < ny:
        result = result + YT * XT * Z[i + 1, j + 1]
    return result

def rayshade(volcano):
    volcanoshadow = np.ones_like(volcano)

    sunangle = 45. / 180. * np.pi
    angle = -90. / 180. * np.pi
    diffangle = 90. / 180. * np.pi
    nangles = 25
    anglebreaks = np.tan(np.linspace(angle, diffangle, nangles, endpoint=True))

    maxdistance = int(np.floor(np.sqrt(float(volcano.shape[0] ** 2 + volcano.shape[1] ** 2))) + 1)
    sinsun, cossun = np.sin(sunangle), np.cos(sunangle) # does pythran have sincos?

    for i in range(0, volcano.shape[0]):
        for j in range(0, volcano.shape[1]):
            vij = volcano[i, j]
            for anglei in anglebreaks:
                for k in range(1, maxdistance):
                    xcoord = (i + sinsun * k)
                    ycoord = (j + cossun * k)
                    if (xcoord >= volcano.shape[0] - 1 or
                        ycoord >= volcano.shape[1] - 1 or
                        xcoord < 0 or ycoord < 0):
                        break
                    else:
                        tanangheight = vij + anglei * k
                        cx, cy = int(math.ceil(xcoord)), int(math.ceil(ycoord))
                        fx, fy = int(math.floor(xcoord)), int(math.floor(ycoord))

                        if (volcano[cx, cy] < tanangheight or
                            volcano[fx, cy] < tanangheight or 
                            volcano[cx, fy] < tanangheight or
                            volcano[fx, fy] < tanangheight):
                            continue

                        if tanangheight < faster_bilinear(volcano, xcoord, ycoord):
                            volcanoshadow[i, j] = volcanoshadow[i, j] - 1 / nangles
                            break

    return volcanoshadow