function faster_bilinear(Z::AbstractMatrix{T}, x0, y0) where T
  i = floor(Int, x0)
  j = floor(Int, y0)
  XT = (x0 - i)
  YT = (y0 - j)
  result = (1 - YT) * (1 - XT) * Z[i, j]
  nx, ny = size(Z)
  (i + 1 <= nx) && (result = result + (1-YT) * XT * Z[i + 1, j])
  (j + 1 <= ny) && (result = result + YT * (1-XT) * Z[i, j + 1])
  if i + 1 <= nx && j + 1 <= ny
    result = result + YT * XT * Z[i + 1, j + 1]
  end
  result
end

function rayshade_julia(
    Z, shadow = fill(one(eltype(Z)), size(Z)); 
    sunangle = 45 / 180*pi, 
    angle = -90 / 180 * pi, diffangle = 90 / 180 * pi, angles = 25,
    anglebreaks = range(angle, stop = diffangle, length = angles),
    maxdistance = floor(Int, sqrt(sum(size(Z).^2)))
  )
  tan_angles = tan.(anglebreaks)
  sun = sincos(sunangle)
  for I in CartesianIndices(size(Z)) # iterate over all I=(i, j)
    aij = Z[I]; ivec = Tuple(I)
    for tana in tan_angles
      for k in 1:maxdistance
        tanheight = aij + tana * k
        coord = ivec .+ sun .* k
        clow = floor.(Int, coord); chigh = ceil.(Int, coord)
        checkbounds(Bool, Z, clow...) && 
          checkbounds(Bool, Z, chigh...) || break
        if (Z[clow[1], clow[2]] < tanheight || 
            Z[chigh[1], chigh[2]] < tanheight || 
            Z[clow[1], chigh[2]] < tanheight || 
            Z[chigh[1], clow[2]] < tanheight)
          continue
        end
        if tanheight < faster_bilinear(Z, coord...)
          shadow[I] = shadow[I] - 1 / angles
          break
        end
      end
    end
  end
  shadow
end
