import pygame
import cb

class Note:
    def __init__(self, screen, x, y, speed, size, BIG):
        self.screen = screen
        self.x = x
        self.y = y
        self.speed = speed
        self.size = size
        if BIG: self.color=(255, 0, 0)
        else: self.color=(0, 0, 0)
        self.BIG=BIG

    def moveNote(self):
        self.y += self.speed
        pygame.draw.rect(self.screen, self.color, pygame.Rect(self.x, self.y, self.size, 10))

    def getY(self):
        return self.y+10 
    
class Song:
    def __init__(self, screen, speed):
        self.screen = screen
        self.speed = speed
        self.shown = []
        self.notes = cb.mnote
        self.touched = False

    def draw(self):
        for i in self.shown:
            for j in i[:5]:
                if j != 0: j.moveNote()

    def playGame(self):
        if len(self.notes) == 0:
            return 0
        thisLine = self.notes.pop(0)
        if thisLine[5]:
            if thisLine[0] == 1:
                thisLine[0] = Note(self.screen, 0, 0, 8, 120, True)
            if thisLine[1] == 1:
                thisLine[1] = Note(self.screen, 120, 0, 8, 120, True)
            if thisLine[2] == 1:
                thisLine[2] = Note(self.screen, 240, 0, 8, 120, True)
            if thisLine[3] == 1:
                thisLine[3] = Note(self.screen, 360, 0, 8, 120, True)
            if thisLine[4] == 1:
                thisLine[4] = Note(self.screen, 480, 0, 8, 120, True)
        else:
            if thisLine[0] == 1:
                thisLine[0] = Note(self.screen, 20, 0, 8, 80, False)
            if thisLine[1] == 1:
                thisLine[1] = Note(self.screen, 140, 0, 8, 80, False)
            if thisLine[2] == 1:
                thisLine[2] = Note(self.screen, 260, 0, 8, 80, False)
            if thisLine[3] == 1:
                thisLine[3] = Note(self.screen, 380, 0, 8, 80, False)
            if thisLine[4] == 1:
                thisLine[4] = Note(self.screen, 500, 0, 8, 80, False)
            
        if thisLine[:5] != [0, 0, 0, 0, 0]: self.shown.insert(0, thisLine)
        return 1

    def touch(self, minY, maxY, isBIG):
        if len(self.shown) != 0:
            for i in self.shown[-1][:5]:
                if i != 0: lineY = i.getY()
            
            if minY <= lineY <= maxY:
                self.touched = True
                return True
            if lineY>maxY: 
                self.touched=False
                if not isBIG: self.shown.pop(-1)
        return False

    def hit(self, key, isBIG):
        if self.shown[-1][key] != 0:
            self.touched = False
            if isBIG: 
                self.shown[-1][key].size=80
                self.shown[-1][key].x+=5
                self.shown[-1][key].color=(0, 0, 0)
                self.shown[-1][key].BIG=False
            else: 
                self.shown.pop(-1)
            return True
        else:
            return False
