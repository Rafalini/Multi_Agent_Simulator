import asyncio
import websockets
import json
import build.map_module


async def request_handler(websocket, path):
    while True:
        try:
            request = await asyncio.wait_for(websocket.recv(), timeout = 3600)
            dict = json.loads(request)
            #print(dict)

            map = dict["map"]
            map_agents = dict["agents"]
            map_cities = map["cities"]
            map_points = map["points"]
            map_paths = map["paths"]

            cpp_map = build.map_module.Agents_Map()
            print("\nwczytuje miasta i agentow do mapy...\n")

            for x in map_cities:
                cpp_map.add_map_point(x["id"],x["name"], x["x"], x["y"])
                print("Miasto: "+str(x["id"])+" "+x["name"]+" "+str(x["x"])+" "+str(x["y"]))
            for x in map_points:
                cpp_map.add_map_point(x["id"],"point_"+str(x["id"]), x["x"], x["y"])
                print("Pubnkt: "+str(x["id"])+" "+"point_"+str(x["id"])+" "+str(x["x"])+" "+str(x["y"]))
            for x in map_agents:
                cpp_map.add_agent(x["id"],x["begining"], x["destination"], x["load"])
                print("Agent: "+str(x["id"])+" "+x["begining"]+" "+x["destination"]+" "+str(x["load"]))
            for x in map_paths:
                cpp_map.add_path(x["begining"],x["end"],x["type"])

            print("\nwczytano miasta i agentow do mapy\n")

            cpp_map.run()

            output_json ="["
            iter = 0
            for x in map_agents:
                #output_json += json.loads(cpp_map.get_agent_route(iter).__dict__)
                output_json += cpp_map.get_agent_route(iter)+", "
                iter += 1

            output_json = output_json[:-2]
            output_json += "]"
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
