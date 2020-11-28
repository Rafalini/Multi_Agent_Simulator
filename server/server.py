import asyncio
import websockets
import json
import build.map_module
from src_py.Map import Map
from src_py.Agent import Agent
from src_py.City import City


async def request_handler(websocket, path):
    while True:
        try:
            request = await asyncio.wait_for(websocket.recv(), timeout = 3600)
            #print(f"request: {request}", flush=True)
            dict = json.loads(request)
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

            print("wczytuje miasta i agentow do mapy...")

            mapka = build.map_module.Agents_Map() # tworzenie i proba mapki cpp
            for x in cities:
                mapka.add_city(x.name, x.coordX, x.coordY)
                
            mapka.idiotic_respond()

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
