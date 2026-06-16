from shapely import Polygon

cfg = {
    "targetAddr": "localhost",
    "targetPort": 8888,
    "multicon": True, # If true, send each cluster with a new TCP connection
    "clusters": [
        {
            "entityCount": 100,
            "interval": 3, # In seconds
            "initialDelay": 0, # In seconds
            "initialBoundPoylygon": Polygon(()), # Must be >= 3 vertex Polygon
            "angle": [0, 360], # Degree. Random range, 1 element for fixed value
            "speed": [5, 50], # m/s. Random range, 1 element for fixed value
            "angleDelta": [-2, 2], # Empty for fixed angle
        }
    ],
}
