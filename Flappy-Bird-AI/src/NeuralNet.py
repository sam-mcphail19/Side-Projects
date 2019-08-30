import numpy as np

class NeuralNetwork:

    def __init__(self, layerSizes):
        self.layerWeightShapes = [(a,b) for a,b in zip(layerSizes[1:], layerSizes[:-1])]#eg. (3,6,1) gives [[6,3], [1,6]]
        self.weights = [np.random.standard_normal(w)/w[1]**.5 for w in self.layerWeightShapes]#every neuron has a weight
        self.biases = [np.zeros((s,1)) for s in layerSizes[1:]]#a column vector for each layer (other than input layer)


    def feedForward(self, x):
        for w,b in zip(self.weights, self.biases):
            x = self.sigmoid(np.matmul(w,x) + b)

        return x


    @staticmethod
    def sigmoid(x):
        return 1/(1+np.exp(-x))
