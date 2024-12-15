import sys
import json
import os

print(os.getcwd())

def serialize(game_map, row_size, col_size, file_path, file_name):
    game_map_array = game_map.split("\r\n")

    data = {
        "row_size": "{}".format(row_size),
        "col_size": "{}".format(col_size),
        "game_map": game_map_array
    }
    
    stringify_data = json.dumps(data)
    
    with open("{}{}.json".format(file_path, file_name), "w") as file:
        file.write(stringify_data)
