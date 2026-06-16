from shapely import Point
from struct import pack
import socket
import math
from time import time, sleep
import random
import pointpats
from typing import List

from config import cfg

class Ship:
    def __init__(self, initPos: Point, initAngle: float, initSpeed: float) -> None:
        self.pos = initPos
        self.angle = initAngle
        self.speed = initSpeed

    def tick(self, duration, angleDelta):
        self.angle += angleDelta

        distant = self.speed * duration
        angleRad = math.radians(self.angle)
        x = math.sin(angleRad) * distant
        y = math.cos(angleRad) * distant

        self.pos = Point(self.pos.x + x, self.pos.y + y)

    def toBytes(self):
        b = pack("!ddddQ", self.pos.x, self.pos.y, self.angle, self.speed, int(time() * 1000))
        return b

def init(cluster) -> List[Ship]:
    listShip = []

    randomInitial = pointpats.random.normal(cluster.initialBoundPolygon, size = cluster.entityCount)

    for i in range(0, cluster.entityCount):
        angleArgs =  len(cluster.angle)
        speedArgs = len(cluster.speed)

        initAngle = 0
        if angleArgs == 1:
            initAngle = cluster.angle[0]
        elif angleArgs == 2:
            initAngle = random.randrange(cluster.angle[0], cluster.angle[1])
        else:
            raise Exception("Not supported argument number")

        initSpeed = 0
        if speedArgs == 1:
            initSpeed = cluster.angle[0]
        elif speedArgs == 2:
            initSpeed = random.randrange(cluster.angle[0], cluster.angle[1])
        else:
            raise Exception("Not supported argument number")

        listShip.append(Ship(randomInitial[i], initAngle, initSpeed))

    return listShip

def makeMessage(listShip: List[Ship]) -> bytes:
    message = b'0'

    listBytes = []

    for ship in listShip:
        listBytes.append(ship.toBytes())

    body = b''.join(listBytes)

    message = message + pack('!I', len(body)) + body

    return message

def run(cluster):
    listShip = init(cluster)
    angleDeltaArgs = len(cluster.angleDelta)

    message = makeMessage(listShip)

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((cfg["targetAddr"], cfg["targetPort"]))

    sleep(cluster.initialDelay)

    while True:
        s.send(message)

        start = time()

        for ship in listShip:
            angleDelta = 0
            if angleDeltaArgs == 1:
                angleDelta = cluster.angleDelta[0]
            elif angleDeltaArgs == 2:
                angleDelta = random.randrange(cluster.angleDelta[0], cluster.angleDelta[1])

            ship.tick(cluster.interval, angleDelta)

        end = time()
        elapse = end - start
        if (elapse < cluster.interval):
            sleep(cluster.interval - elapse)


if __name__ == '__main__':
    pass
