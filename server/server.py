import asyncio
import websockets
import json
import build.map_module


async def request_handler(websocket, path):
    while True:
        try:
            request = await asyncio.wait_for(websocket.recv(), timeout = 3600)
            dict = json.loads(request)
            cities =[]
            agents =[]

            print(dict)

            map = dict["map"]
            map_agents = dict["agents"]
            map_cities = map["cities"]

            #for x in map_agents["agents"]:
            #    agents.append(Agent(x["begining"],x["destination"],x["load"]))

            #for x in map_cities:
            #    cities.append(City(x["name"],x["x"],x["y"],x["segments"]))

            print("wczytuje miasta i agentow do mapy...")

            cpp_map = build.map_module.Agents_Map()
            for x in map_cities:
                cpp_map.add_city(x["name"], x["x"], x["y"])
            for x in map_agents:
                cpp_map.add_agent(x["begining"], x["destination"], x["load"])

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
