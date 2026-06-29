import traceback

from shapely import Point
from struct import pack
import socket
import math
from time import time, sleep
import random
import pointpats.random
from typing import List
from concurrent.futures import ThreadPoolExecutor
import uuid
from geographiclib.constants import Constants
from geographiclib.geodesic import Geodesic
import threading

from config import cfg

shipIdCounter = 0
lock = threading.Lock()

class Ship:
    def __init__(self, id: int, initPos: Point, initAngle: float, initSpeed: float) -> None:
        self.id = id
        self.pos = initPos
        self.angle = initAngle
        self.speed = initSpeed

    def tick(self, duration, angleDelta):
        self.angle += angleDelta

        distant = duration * self.speed

        geod = Geodesic(Constants.WGS84_a, Constants.WGS84_f)
        d = geod.Direct(self.pos.x, self.pos.y, self.angle, distant)
        self.pos = Point(d['lat2'], d['lon2'])

    def toBytes(self):
        b = pack("!qddddQ", self.id, self.pos.x, self.pos.y, self.angle, self.speed, int(time() * 1000))
        return b

def init(cluster) -> List[Ship]:
    listShip = []

    randomInitial = pointpats.random.normal(cluster["initialBoundPolygon"], size = cluster["entityCount"])
    randomInitial = [Point(x) for x in randomInitial]

    for i in range(0, cluster["entityCount"]):
        angleArgs =  len(cluster["angle"])
        speedArgs = len(cluster["speed"])

        initAngle = 0
        if angleArgs == 1:
            initAngle = cluster["angle"][0]
        elif angleArgs == 2:
            initAngle = random.randrange(cluster["angle"][0], cluster["angle"][1])
        else:
            raise Exception("Not supported argument number")

        initSpeed = 0
        if speedArgs == 1:
            initSpeed = cluster["speed"][0]
        elif speedArgs == 2:
            initSpeed = random.randrange(cluster["speed"][0], cluster["speed"][1])
        else:
            raise Exception("Not supported argument number")

        # Use a counter so ship ID stay the same, so client won't show tons of ships and can continue to update after restarting
        global lock
        global shipIdCounter

        lock.acquire()
        id = shipIdCounter
        shipIdCounter += 1
        lock.release()

        listShip.append(Ship(id, randomInitial[i], initAngle, initSpeed))

    return listShip

def makeMessage(listShip: List[Ship]) -> bytes:
    message = b'\x00'

    listBytes = []

    for ship in listShip:
        listBytes.append(ship.toBytes())

    body = b''.join(listBytes)

    message = message + pack('!I', len(body)) + body

    return message

def run(cluster):
    try:
        listShip = init(cluster)
        angleDeltaArgs = len(cluster["angleDelta"])

        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        connected = False

        while not connected:
            try:
                s.connect((cfg["targetAddr"], cfg["targetPort"]))
                connected = True
            except Exception:
                print("Can't connect to {target}:{port}. Try again in 5 seconds".format(target = cfg["targetAddr"], port = cfg["targetPort"]))
                sleep(5)

        print("Connected to target. Sending!")

        sleep(cluster["initialDelay"])

        while True:
            message = makeMessage(listShip)
            s.send(message)

            start = time()

            for ship in listShip:
                angleDelta = 0
                if angleDeltaArgs == 1:
                    angleDelta = cluster["angleDelta"][0]
                elif angleDeltaArgs == 2:
                    angleDelta = random.randrange(cluster["angleDelta"][0], cluster["angleDelta"][1])

                ship.tick(cluster["interval"], angleDelta)

            end = time()
            elapse = end - start
            if (elapse < cluster["interval"]):
                sleep(cluster["interval"] - elapse)
    except Exception:
        print(traceback.format_exc())

if __name__ == '__main__':
    clusters = cfg["clusters"]

    with ThreadPoolExecutor() as executor:
        for cluster in clusters:
            executor.submit(run, cluster)

        executor.shutdown(wait = True)
