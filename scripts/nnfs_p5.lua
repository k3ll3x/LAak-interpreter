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
	o.weights = mat.random(n_inputs, n_neurons)
	o.biases = vec(n_neurons):t()
	return o
end

Layer_Dense.forward = function(self, inputs)
	self.out = (inputs * self.weights) + self.biases
end

----------------------------

-- Create data, spiral

function create_data(n_points, n_classes)
	local X = mat(n_points * n_classes, 2)
	local Y = vec(n_points * n_classes)
	for class_num = 0, n_classes do
		local r = vector.linspace(n_points, 0.0, 1)
		local t = vector.linspace(n_points, class_num*4, (class_num+1)*4) + (vector.random(n_points)*0.2)
		local idx = n_points * class_num
		local _size = (n_points * (class_num+1)) - idx
		local nmat = mat(n_points, 2)
		nmat:col(0, r*(2.5 * t:sin()))
		nmat:col(1, r*(2.5 * t:cos()))
		--X:segment(idx, _size, )
		Y:segment(idx, _size, class_num)
	end
	return {X, Y}
end

----------------------

-- Activation "Rectified" Linear Unit Class

Activation_ReLU = {
	out,
}

Activation_ReLU.forward = function(self, inputs)
	self.out = inputs:max()
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





