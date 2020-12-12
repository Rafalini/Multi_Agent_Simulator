class Agent:
    def __init__(self, id, begin, destination, load):
        self.id = id
        self.beginingCity = begin
        self.destinationCity = destination
        self.load = load
        self.route = "_"

    def print(self):
        print(self.id)
        print(self.beginingCity)
        print(self.destinationCity)
        print(self.load)

    def update_route(self,input):
        self.route = input
