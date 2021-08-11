-- Neural network from scratch
vec = vector.new
mat = matrix.new

inputs = vec(1, 2, 3, 2.5)

weights = mat(
	{
		{0.2, 0.8, -0.5, 1.0},
		{0.5, -0.91, 0.26, -0.5},
		{-0.26, -0.27, 0.17, 0.87}
	}
)

biases = vec(2, 3, 0.5)

out = weights * inputs + biases
out = out:t()
print(out)


