class Agent:
    def __init__(self, begin, destination, load):
        self.beginingCity = begin
        self.destinationCity = destination
        self.load = load

    def print(self):
        print(self.beginingCity)
        print(self.destinationCity)
        print(self.load)
