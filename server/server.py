import asyncio
import websockets
import json
import build.map_module
#from src_py.Map import Map
from src_py.Agent import Agent
from src_py.City import City


async def request_handler(websocket, path):
    while True:
        try:
            request = await asyncio.wait_for(websocket.recv(), timeout = 3600)
            dict = json.loads(request)
            cities =[]
            agents =[]

            map = dict["map"]
            map_agents = dict["agents"]
            map_cities = map["cities"]

            id=0
            for x in map_agents["agents"]:
                agents.append(Agent(id,x["begining"],x["destination"],x["weight"]))
                id+=1

            for x in map_cities:
                cities.append(City(x["name"],x["x"],x["y"],x["segments"]))

            mapka = build.map_module.Agents_Map()
            for x in cities:
                mapka.add_city(x.name, x.coordX, x.coordY)

            print("wczytuje miasta i agentow do mapy...")

            #for x in agents:
            #    mapka.add_agent(x.beginingCity, x.destinationCity, x.load)

            #mapka.run()

            output_json =""
            for x in agents:
                x.update_route(mapka.get_agent_route(x.id))
                print(mapka.get_agent_route(x.id))
                output_json += json.dumps(x.__dict__)

            print(output_json)

            await (websocket.send(output_json))
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
