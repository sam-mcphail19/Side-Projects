import random, copy

from Game import Player

class GeneticAlg:

    def __init__(self, populationSize):
        self.populationSize = populationSize
        self.best = None
        self.population = self.makePopulation(populationSize)

    @staticmethod
    def makePopulation(size):
        population = []
        for i in range(size):
            population.append(Player())

        return population


    def sortPopByFitness(self):
        for i in range(len(self.population)):
            min_idx = i
            for j in range(i + 1, len(self.population)):
                if self.population[min_idx].fitnessScore < self.population[j].fitnessScore:
                    min_idx = j
            self.population[i], self.population[min_idx] = self.population[min_idx], self.population[i]


    def select(self):
        self.sortPopByFitness()

        if self.best is None:
            self.best = copy.deepcopy(self.population[0])

        elif self.population[0].fitnessScore > self.best.fitnessScore:
            self.best = copy.deepcopy(self.population[0])


    @staticmethod
    def mutate(organism):
        mutationRate = 0.15
        mutationRange = 0.5

        organism.color = (random.randint(40,255), random.randint(40,255), random.randint(40,255))
        organism.fitnessScore = 0

        for i in range(len(organism.brain.weights)):
            for j in range(len(organism.brain.weights[i])):
                if random.random() < mutationRate:
                    #change the weight by a value between -1 and 1 multiplied by the range
                    organism.brain.weights[i][j] += 2*random.random()*mutationRange - mutationRange

        for i in range(len(organism.brain.biases)):
            for j in range(len(organism.brain.biases[i])):
                if random.random() < mutationRate:
                    #change the weight by a value between -1 and 1 multiplied by the range
                    organism.brain.biases[i][j] += 2*random.random()*mutationRange - mutationRange

        return organism


    def newGen(self):

        self.select()
        parent = self.best

        self.population = []

        while len(self.population) < self.populationSize:
            self.population.append(self.mutate(copy.deepcopy(parent)))

        return self.population
