import pygame
import os

WIDTH = 800
HEIGHT = 600

os.environ['SDL_VIDEO_CENTERED'] = '1' #centers the window

pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))

clock = pygame.time.Clock()