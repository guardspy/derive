import pygame
from pygame.locals import *
from pygame import mixer
import sys
import song

score = 0
score_inc = 100

pygame.init()
screen = pygame.display.set_mode((600, 720))
done = False

pygame.mixer.music.load('밤200-미.mp3')
pygame.mixer.music.set_volume(1)
pygame.mixer.music.play(-1)

thisSong = song.Song(screen, 5)
pygame.time.set_timer(USEREVENT+1, 300)

clock = pygame.time.Clock()

while not done:
    for event in pygame.event.get():
        if event.type == USEREVENT+1:
            if thisSong.playGame() == 0:
                done = True
        if event.type == pygame.QUIT:
            done = True

    pressed = pygame.key.get_pressed()
    if thisSong.touch(480, 520, True):
        if pressed[pygame.K_r]:
            if thisSong.hit(0, True):
                score += score_inc
        if pressed[pygame.K_t]:
            if thisSong.hit(1, True):
                score += score_inc
        if pressed[pygame.K_y]:
            if thisSong.hit(2, True):
                score += score_inc
        if pressed[pygame.K_u]:
            if thisSong.hit(3, True):
                score += score_inc
        if pressed[pygame.K_i]:
            if thisSong.hit(4, True):
                score += score_inc
    
    if thisSong.touch(660, 700, False):
        if pressed[pygame.K_f]:
            if thisSong.hit(0, False):
                score += score_inc
        if pressed[pygame.K_g]:
            if thisSong.hit(1, False):
                score += score_inc
        if pressed[pygame.K_h]:
            if thisSong.hit(2, False):
                score += score_inc
        if pressed[pygame.K_j]:
            if thisSong.hit(3, False):
                score += score_inc
        if pressed[pygame.K_k]:
            if thisSong.hit(4, False):
                score += score_inc

    screen.fill((255, 255, 255))
    pygame.draw.line(screen, (128, 128, 128), (0, 500), (600, 500), 5)
    pygame.draw.line(screen, (128, 128, 128), (0, 680), (600, 680), 5)
    thisSong.draw()
    scoretext = pygame.font.SysFont("Arial", 16).render("Score {0}".format(score), 1, (0,0,0))
    screen.blit(scoretext, (5, 10))

    pygame.display.flip()
    clock.tick(60)