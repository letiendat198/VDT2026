from shapely import Polygon

cfg = {
    "targetAddr": "localhost",
    "targetPort": 8888,
    "clusters": [
        {
            "entityCount": 1000,
            "interval": 1, # In seconds
            "initialDelay": 0, # In seconds
            "initialBoundPolygon": Polygon(((17.719230, 107.198103), (15.495328, 109.456255), (11.823654, 110.161928), (11.162869, 117.469560), (19.561649, 119.084766))), # Must be >= 3 vertex Polygon
            "angle": [0, 360], # Degree. Random range, 1 element for fixed value
            "speed": [1000], # m/s. Random range, 1 element for fixed value
            "angleDelta": [], # Empty for fixed angle
        },
        # {
        #     "entityCount": 1000,
        #     "interval": 1, # In seconds
        #     "initialDelay": 0, # In seconds
        #     "initialBoundPolygon": Polygon(((17.719230, 107.198103), (15.495328, 109.456255), (11.823654, 110.161928), (11.162869, 117.469560), (19.561649, 119.084766))), # Must be >= 3 vertex Polygon
        #     "angle": [0, 360], # Degree. Random range, 1 element for fixed value
        #     "speed": [2000], # m/s. Random range, 1 element for fixed value
        #     "angleDelta": [], # Empty for fixed angle
        # },
        # {
        #     "entityCount": 1000,
        #     "interval": 1, # In seconds
        #     "initialDelay": 0, # In seconds
        #     "initialBoundPolygon": Polygon(((17.719230, 107.198103), (15.495328, 109.456255), (11.823654, 110.161928), (11.162869, 117.469560), (19.561649, 119.084766))), # Must be >= 3 vertex Polygon
        #     "angle": [0, 360], # Degree. Random range, 1 element for fixed value
        #     "speed": [1000], # m/s. Random range, 1 element for fixed value
        #     "angleDelta": [], # Empty for fixed angle
        # },
        # {
        #     "entityCount": 1000,
        #     "interval": 1, # In seconds
        #     "initialDelay": 0, # In seconds
        #     "initialBoundPolygon": Polygon(((17.719230, 107.198103), (15.495328, 109.456255), (11.823654, 110.161928), (11.162869, 117.469560), (19.561649, 119.084766))), # Must be >= 3 vertex Polygon
        #     "angle": [0, 360], # Degree. Random range, 1 element for fixed value
        #     "speed": [2000], # m/s. Random range, 1 element for fixed value
        #     "angleDelta": [], # Empty for fixed angle
        # },
        # {
        #     "entityCount": 1000,
        #     "interval": 1, # In seconds
        #     "initialDelay": 0, # In seconds
        #     "initialBoundPolygon": Polygon(((17.719230, 107.198103), (15.495328, 109.456255), (11.823654, 110.161928), (11.162869, 117.469560), (19.561649, 119.084766))), # Must be >= 3 vertex Polygon
        #     "angle": [0, 360], # Degree. Random range, 1 element for fixed value
        #     "speed": [1000], # m/s. Random range, 1 element for fixed value
        #     "angleDelta": [], # Empty for fixed angle
        # },
        # {
        #     "entityCount": 1000,
        #     "interval": 1, # In seconds
        #     "initialDelay": 0, # In seconds
        #     "initialBoundPolygon": Polygon(((17.719230, 107.198103), (15.495328, 109.456255), (11.823654, 110.161928), (11.162869, 117.469560), (19.561649, 119.084766))), # Must be >= 3 vertex Polygon
        #     "angle": [0, 360], # Degree. Random range, 1 element for fixed value
        #     "speed": [2000], # m/s. Random range, 1 element for fixed value
        #     "angleDelta": [], # Empty for fixed angle
        # },
        # {
        #     "entityCount": 1000,
        #     "interval": 1, # In seconds
        #     "initialDelay": 0, # In seconds
        #     "initialBoundPolygon": Polygon(((17.719230, 107.198103), (15.495328, 109.456255), (11.823654, 110.161928), (11.162869, 117.469560), (19.561649, 119.084766))), # Must be >= 3 vertex Polygon
        #     "angle": [0, 360], # Degree. Random range, 1 element for fixed value
        #     "speed": [1000], # m/s. Random range, 1 element for fixed value
        #     "angleDelta": [], # Empty for fixed angle
        # },
        # {
        #     "entityCount": 1000,
        #     "interval": 1, # In seconds
        #     "initialDelay": 0, # In seconds
        #     "initialBoundPolygon": Polygon(((17.719230, 107.198103), (15.495328, 109.456255), (11.823654, 110.161928), (11.162869, 117.469560), (19.561649, 119.084766))), # Must be >= 3 vertex Polygon
        #     "angle": [0, 360], # Degree. Random range, 1 element for fixed value
        #     "speed": [2000], # m/s. Random range, 1 element for fixed value
        #     "angleDelta": [], # Empty for fixed angle
        # },
        # {
        #     "entityCount": 1000,
        #     "interval": 1, # In seconds
        #     "initialDelay": 0, # In seconds
        #     "initialBoundPolygon": Polygon(((17.719230, 107.198103), (15.495328, 109.456255), (11.823654, 110.161928), (11.162869, 117.469560), (19.561649, 119.084766))), # Must be >= 3 vertex Polygon
        #     "angle": [0, 360], # Degree. Random range, 1 element for fixed value
        #     "speed": [1000], # m/s. Random range, 1 element for fixed value
        #     "angleDelta": [], # Empty for fixed angle
        # },
        # {
        #     "entityCount": 1000,
        #     "interval": 1, # In seconds
        #     "initialDelay": 0, # In seconds
        #     "initialBoundPolygon": Polygon(((17.719230, 107.198103), (15.495328, 109.456255), (11.823654, 110.161928), (11.162869, 117.469560), (19.561649, 119.084766))), # Must be >= 3 vertex Polygon
        #     "angle": [0, 360], # Degree. Random range, 1 element for fixed value
        #     "speed": [2000], # m/s. Random range, 1 element for fixed value
        #     "angleDelta": [], # Empty for fixed angle
        # },
    ],
}
