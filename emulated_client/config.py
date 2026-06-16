from shapely import Polygon

cfg = {
    "targetAddr": "localhost",
    "targetPort": 8888,
    "clusters": [
        {
            "entityCount": 100,
            "interval": 3, # In seconds
            "initialDelay": 0, # In seconds
            "initialBoundPolygon": Polygon(((20., 106.), (18., 106.), (18., 108.), (14., 109.))), # Must be >= 3 vertex Polygon
            "angle": [0, 360], # Degree. Random range, 1 element for fixed value
            "speed": [5, 50], # m/s. Random range, 1 element for fixed value
            "angleDelta": [-2, 2], # Empty for fixed angle
        }
    ],
}
