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

            map = dict["map"]
            map_agents = dict["agents"]
            map_cities = map["cities"]

            cpp_map = build.map_module.Agents_Map()
            print("wczytuje miasta i agentow do mapy...")

            for x in map_cities:
                cpp_map.add_city(x["name"], x["x"], x["y"])
            for x in map_agents:
                cpp_map.add_agent(x["begining"], x["destination"], x["load"])

            print("wczytano miasta i agentow do mapy")

            cpp_map.run()

            output_json =""
            for x in agents:
                output_json += json.dumps(cpp_map.get_agent_route(x.id).__dict__)

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
