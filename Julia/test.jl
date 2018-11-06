module Rayshade
	using CxxWrap
	@wrapmodule("./jlrayshade.so")

	function __init__()
	  @initcxx
	end
end

using DelimitedFiles

volcano = readdlm("../assets/volcano.csv", ',', Float32, '\n')
volcano

shaded = Rayshade.rayshade(volcano)
using Plots, BenchmarkTools
heatmap(shaded, aspect_ratio = 1)
gui()
readline(stdin)

println("Benchmarking C++:")
@btime Rayshade.rayshade(volcano)

include("julia_impl.jl")

println("Benchmarking Native:")
@btime rayshade_julia(volcano)