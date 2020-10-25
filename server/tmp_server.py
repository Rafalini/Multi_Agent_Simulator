import asyncio
import websockets
import json


async def request_handler(websocket, path):
    while True:
        try:
            request = await asyncio.wait_for(websocket.recv(), timeout = 3600)
            print(f"request: {request}", flush=True)
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
