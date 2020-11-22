import asyncio
import websockets
import json
from Map import Map
from Agent import Agent
from City import City


async def request_handler(websocket, path):
    while True:
        try:
            request = await asyncio.wait_for(websocket.recv(), timeout = 3600)
            #print(f"request: {request}", flush=True)
            dict = json.loads(request)
            #print(dict["agents"])
            print("")
            print("")

#into data structures
            cities =[]
            agents =[]

            map = dict["map"]
            map_agents = dict["agents"]
            map_cities = map["cities"]

            for x in map_agents["agents"]:
                agents.append(Agent(x["begining"],x["destination"],x["weight"]))

            for x in map_cities:
                cities.append(City(x["name"],x["x"],x["y"],x["segments"]))

            print(map["points"])

            await (websocket.send("request received"))
        except Exception as e:
            print(f'error: {e}', flush=True)
            break;


try:
    start_server = websockets.serve(request_handler, "127.0.0.1", 1111)
    loop = asyncio.get_event_loop()
    loop.run_until_complete(start_server)
    loop.run_forever()
except Exception as e:
    print(f'error: {e}', flush=True)
