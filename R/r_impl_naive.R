# Code taken from article: http://www.tylermw.com/throwing-shade/
# Author: Tyler Morgan-Wall

# simple bilinear interpolation:
faster_bilinear <- function (Z, x0, y0){
  i = floor(x0)
  j = floor(y0)
  XT = (x0 - i)
  YT = (y0 - j)
  result = (1 - YT) * (1 - XT) * Z[i, j]
  nx = nrow(Z)
  ny = ncol(Z)
  if(i + 1 <= nx){
    result = result + (1-YT) * XT * Z[i + 1, j]
  }
  if(j + 1 <= ny){
    result = result + YT * (1-XT) * Z[i, j + 1]
  }
  if(i + 1 <= nx && j + 1 <= ny){
    result = result + YT * XT * Z[i + 1, j + 1]
  }
  result
}

rayshade_slow <- function(heightmap) {
  volcanoshadow = matrix(1, ncol = ncol(heightmap), nrow = nrow(heightmap))

  volc = list(x=1:nrow(heightmap), y=1:ncol(heightmap), z=heightmap)
  sunangle = 45 / 180*pi
  angle = -90 / 180 * pi
  diffangle = 90 / 180 * pi
  numberangles = 25
  anglebreaks = sapply(seq(angle, diffangle, length.out = numberangles), tan)
  maxdistance = floor(sqrt(ncol(heightmap)^2 + nrow(heightmap)^2))
  sinsun = sin(sunangle)
  cossun = cos(sunangle)
  for (i in 1:nrow(heightmap)) {
    for (j in 1:ncol(heightmap)) {
      vij = heightmap[i, j]
      for (anglei in anglebreaks) {
        for (k in 1:maxdistance) {
          xcoord = (i + sinsun*k)
          ycoord = (j + cossun*k)
          if(xcoord > nrow(heightmap) || 
             ycoord > ncol(heightmap) || 
             xcoord < 0 || ycoord < 0) {
            break
          } else {
            tanangheight = vij + anglei * k 
            if (all(c(heightmap[ceiling(xcoord), ceiling(ycoord)],
                      heightmap[floor(xcoord), ceiling(ycoord)],
                      heightmap[ceiling(xcoord), floor(ycoord)],
                      heightmap[floor(xcoord), floor(ycoord)]) < tanangheight)) next
            if (tanangheight < faster_bilinear(heightmap, xcoord, ycoord)) {
              volcanoshadow[i, j] =  volcanoshadow[i, j] - 1 / length(anglebreaks)
              break
            }
          }
        }
      }
    }
  }
}