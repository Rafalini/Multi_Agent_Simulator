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
            parameters = dict["parameters"]

            cpp_map = build.map_module.Agents_Map()

            #print("\nwczytuje miasta i agentow do mapy...\n")

            cpp_map.addSpeeds(parameters["max_speed_0"],parameters["max_speed_1"],parameters["max_speed_2"])
            cpp_map.addLoadingSpeeds(parameters["unload_speed"],parameters["load_speed"])
            cpp_map.addAccident(parameters["accident"], parameters["time_between_breaks"], parameters["break_duration"])

            for x in map_cities:
                cpp_map.addMapPoint(x["id"],x["name"], x["x"], x["y"])
                #print("Miasto: "+str(x["id"])+" "+x["name"]+" "+str(x["x"])+" "+str(x["y"]))
            for x in map_points:
                cpp_map.addMapPoint(x["id"],"point_"+str(x["id"]), x["x"], x["y"])
                #print("Punkt:  "+str(x["id"])+" "+"point_"+str(x["id"])+" "+str(x["x"])+" "+str(x["y"]))
            for x in map_agents:
                cpp_map.addAgent(x["id"],x["begining"], x["destination"], x["load"], x["capacity"])
                #print("Agent: "+str(x["id"])+" "+x["begining"]+" "+x["destination"]+" "+str(x["load"])+str(x["capacity"]))
            for x in map_paths:
                cpp_map.addPath(x["id"],x["begining"],x["end"],x["type"])


            if parameters["isGraphical"] == 1: #graphical mode answer
                cpp_map.run()
                output_json ="{ \"agents\" : ["
                for x in map_agents:
                    output_json += "{ \"history\": "
                    output_json += cpp_map.getAgentRoute(x["id"])+", "
                    output_json += "\"statistics\": {"
                    output_json += cpp_map.getAgentRaport(x["id"])+"} },"
                output_json = output_json[:-1]
                output_json += "], \"paths\" : ["
                output_json += cpp_map.getPaths()
                output_json += " ] }"
            else:
                for x in range(parameters["number_of_simulations"]):
                    cpp_map.run()
                    cpp_map.restart()

                output_json ="["
                for x in map_agents:
                    output_json += cpp_map.getAgentStats(x["id"],parameters["number_of_simulations"])+","
                output_json = output_json[:-1]
                output_json += " ]"

            print(output_json)

            cpp_map.clean()

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
