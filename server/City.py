class City:
    def __init__(self, name, ox, oy, segments):
        self.name = name
        self.coordX = ox
        self.coordY = oy
        self.segments = segments

    def print(self):
        print(self.name)
        print(self.coordX)
        print(self.coordY)
