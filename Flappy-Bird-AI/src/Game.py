import pygame
import os
import random
import Queue as q
import NeuralNet as nn
import GeneticAlg as ga


WIDTH = 800
HEIGHT = 600

os.environ['SDL_VIDEO_CENTERED'] = '1' #centers the window

pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption('Flappy Bird')

clock = pygame.time.Clock()


class Player:

    size = 20

    def __init__(self):
        self.y = HEIGHT//2
        self.x = 100
        self.ySpeed = 0
        self.dead = False
        self.brain = nn.NeuralNetwork((4,12,1))
        self.fitnessScore = 0
        self.color = (random.randint(50,255), random.randint(50,255), random.randint(50,255))

    def draw(self):
        #(x,y) is the exact center of the circle
        pygame.draw.circle(screen, self.color, (self.x, int(self.y)), self.size)

    def update(self, pipe):
        self.ySpeed += 0.35
        self.y += self.ySpeed

        if self.brain.feedForward([self.y, pipe.y, pipe.gapSize, pipe.x])[0][0] > 0.5:
            self.flap()

        if self.dead:
            if self.y > HEIGHT - self.size:
                self.y = HEIGHT - self.size
            if self.y < self.size:
                self.y = self.size


    def flap(self):
        if not self.dead:
            self.ySpeed = -7

    def collision(self, pipe):
        if self.y - self.size < 0 or self.y + self.size > HEIGHT:
            return True

        if self.x + self.size < pipe.x or self.x - self.size > pipe.x + pipe.width:
            return False

        if self.y - self.size < pipe.y - pipe.gapSize//2:#top pipe
            return True

        if self.y + self.size > pipe.y + pipe.gapSize // 2:#bottom pipe
            return True

        return False


class Pipe:

    width = 60
    height = HEIGHT
    speed = 3.5
    passed = False
    xDiff = 275

    def __init__(self):
        self.x = WIDTH
        self.y = random.randint(HEIGHT//4, 3*HEIGHT//4)
        self.gapSize = random.randint(HEIGHT//4, HEIGHT//3)
        self.frontPipe = False
        self.color = (0,255,0)

    def draw(self):
        #upper pipe
        pygame.draw.rect(screen, self.color, (int(self.x), (self.y-self.gapSize//2)-HEIGHT, self.width, self.height))
        #lower pipe
        pygame.draw.rect(screen, self.color, (self.x, self.y+self.gapSize//2, self.width, self.height))

    def update(self):
        self.x -= self.speed
        if self.frontPipe:
            self.color = (255,0,0)
        else:
            self.color = (0,255,0)

    def __str__(self):
        return str(self.x)


def renderFont(text, color, size, position):
    font = pygame.font.SysFont("arial", size)
    label = font.render(text, True, color)
    screen.blit(label, position)


def mainLoop():

    running = True

    pipes = q.Queue()# head is the furthest left pipe, tail is furthest right
    pipes.put(q.Node(Pipe()))
    frontPipe = pipes.head# the pipe that is directly in front of the bird
    frontPipe.data.frontPipe = True

    genAlg = ga.GeneticAlg(100)
    players = genAlg.population

    score = 0
    generation = 0
    tick = 0

    while running:

        clock.tick(60)# makes loop always run at the same speed (ticks per second)

        pygame.display.flip()

        screen.fill((0, 0, 0))

        if pipes.tail.data.x < WIDTH - Pipe.xDiff:
            pipes.put(q.Node(Pipe()))

        if not frontPipe.data.passed and frontPipe.data.x + frontPipe.data.width < players[0].x:
            score += 1
            frontPipe.data.passed = True
            frontPipe.data.frontPipe = False
            frontPipe = frontPipe.next
            frontPipe.data.frontPipe = True

        # remove the pipe when its off the screen
        if pipes.head.data.x < 0 - pipes.head.data.width:
            pipes.get()

        pipes.update()
        pipes.draw()

        tick += 1

        for player in players:
            player.update(frontPipe.data)
            player.draw()

            if not player.dead:
                player.fitnessScore += 1

                if player.collision(pipes.head.data):
                    player.dead = True

        if not (False in [player.dead == True for player in players]):#if all players are dead

            for player in players:
                player.y = HEIGHT / 2
                player.ySpeed = 0
                player.dead = False

            players = genAlg.newGen()
            pipes = q.Queue()
            pipes.put(q.Node(Pipe()))
            frontPipe = pipes.head  # the pipe that is directly in front of the bird
            frontPipe.data.frontPipe = True
            score = 0
            tick = 0
            generation += 1

        renderFont(str(score), [255, 255, 255], 72, (WIDTH/2 - 20, 100))
        renderFont("Generation " + str(generation), [255, 255, 255], 24, (20, 20))
        renderFont("Current Score " + str(tick), [255, 255, 255], 24, (20, 45))
        if genAlg.best:
            renderFont("Best Ever Score " + str(genAlg.best.fitnessScore), [255, 255, 255], 24, (20, 70))

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

    pygame.quit()

if __name__ == "__main__":
    mainLoop()