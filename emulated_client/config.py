from shapely import Polygon

cfg = {
    "targetAddr": "localhost",
    "targetPort": 8888,
    "clusters": [
        {
            "entityCount": 1000,
            "interval": 1, # In seconds
            "initialDelay": 0, # In seconds
            "initialBoundPolygon": Polygon(((21.2884, 108.665), (20.5331, 107.452), (19.9073, 106.73), (19.3336, 106.33), (18.7136, 106.392), (17.2897, 107.511), (15.9319, 108.782), (14.2737, 109.559), (12.4745, 109.791), (11.4585, 109.471), (10.1026, 107.552), (8.46189, 105.428), (8.24032, 104.574), (9.52327, 104.28), (11.7799, 101.828), (11.8118, 100.604), (10.112, 99.8714), (7.58713, 100.951), (5.63607, 103.529), (3.80089, 104.458), (3.47018, 112.326), (6.7864, 115.42), (11.2954, 118.296), (15.4393, 119.443), (18.4493, 119.658), (22.4489, 118.55), (21.7604, 114.707), (20.7021, 111.311), (19.293, 111.311), (17.9845, 110.344), (18.0654, 108.707), (19.1689, 108.114), (20.085, 108.895), (20.8566, 109.322), (21.2884, 108.665)),),
            "angle": [0, 360], # Degree. Random range, 1 element for fixed value
            "speed": [1000], # m/s. Random range, 1 element for fixed value
            "angleDelta": [], # Empty for fixed angle
        },
        {
            "entityCount": 1000,
            "interval": 1, # In seconds
            "initialDelay": 0, # In seconds
            "initialBoundPolygon": Polygon(((21.2884, 108.665), (20.5331, 107.452), (19.9073, 106.73), (19.3336, 106.33), (18.7136, 106.392), (17.2897, 107.511), (15.9319, 108.782), (14.2737, 109.559), (12.4745, 109.791), (11.4585, 109.471), (10.1026, 107.552), (8.46189, 105.428), (8.24032, 104.574), (9.52327, 104.28), (11.7799, 101.828), (11.8118, 100.604), (10.112, 99.8714), (7.58713, 100.951), (5.63607, 103.529), (3.80089, 104.458), (3.47018, 112.326), (6.7864, 115.42), (11.2954, 118.296), (15.4393, 119.443), (18.4493, 119.658), (22.4489, 118.55), (21.7604, 114.707), (20.7021, 111.311), (19.293, 111.311), (17.9845, 110.344), (18.0654, 108.707), (19.1689, 108.114), (20.085, 108.895), (20.8566, 109.322), (21.2884, 108.665)),),
            "angle": [0, 360], # Degree. Random range, 1 element for fixed value
            "speed": [2000], # m/s. Random range, 1 element for fixed value
            "angleDelta": [], # Empty for fixed angle
        },
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
        #     "speed": [2000], # m/s. Random range, 1 element for fixed value
        #     "angleDelta": [], # Empty for fixed angle
        # },
    ],
}
