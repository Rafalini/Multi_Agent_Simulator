class Agent:
    def __init__(self, begin, destination, load):
        self.beginingCity = begin
        self.destunationCity = destination
        self.load = load

    def print(self):
        print(self.beginingCity)
        print(self.destunationCity)
        print(self.load)
