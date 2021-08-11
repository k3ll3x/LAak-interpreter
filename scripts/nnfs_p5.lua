-- Neural network from scratch
vec = vector.new
mat = matrix.new

-- Layer Dense class

Layer_Dense = {
	weights,
	biases,
	out,
}

Layer_Dense.new = function(n_inputs, n_neurons)
	o = {}
	setmetatable(o, Layer_Dense)
	Layer_Dense.__index = Layer_Dense
	o.weights = mat(n_inputs, n_neurons, "rand")
	o.biases = vec(n_neurons):t()
	return o
end

Layer_Dense.forward = function(self, inputs)
	self.out = (inputs * self.weights) + self.biases
end

----------------------------

-- Activation "Rectified" Linear Unit Class

Activation_ReLU = {
	out,
}

Activation_ReLU.forward = function(self, inputs)
	self.out = 
end

----------------------------

--input data
X = mat(
	{
		{1, 2, 3, 2.5},
		{2.0, 5.0, -1.0, 2.0},
		{-1.5, 2.7, 3.3, -0.8}
	}
)

-- n_inputs is X cols and n_neurons is X rows
layer1 = Layer_Dense.new(X:cols(), X:rows())
layer2 = Layer_Dense.new(X:rows(), 2)

layer1:forward(X)
print(layer1.out)
layer2:forward(layer1.out)
print(layer2.out)







