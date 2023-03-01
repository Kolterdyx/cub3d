import argparse
import random

import colorama
from wfc import *
import opensimplex as osn

"""
This generates map files for the game "Cub3D".
It only generates the map, not the textures.
"""


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("map", help="The map file to generate", type=str, default="map.cub")
    # optional width and height
    parser.add_argument("-w", "--width", help="The width of the map", type=int, default=24)
    parser.add_argument("-d", "--height", help="The height of the map", type=int, default=24)
    return parser.parse_args()


def match_wall(x, y, landscape):
    """
    Check if the wall at x, y is surrounded by other walls.
    """
    if x == 0 or y == 0 or y >= len(landscape) - 2 or x >= len(landscape[0]) - 2:
        return False
    print(x, y, len(landscape[0]), len(landscape))
    if (landscape[x - 1][y] == "1" and
        landscape[x + 1][y] == "1" and
        landscape[x][y - 1] == "0" and
        landscape[x][y + 1] == "0") or \
            (landscape[x - 1][y] == "0" and
             landscape[x + 1][y] == "0" and
             landscape[x][y - 1] == "1" and
             landscape[x][y + 1] == "1"):
        return True
    return False


def perlin_noise(scale=100, threshold_low: float = 0, threshold_high: float = 0.1):
    args = parse_args()

    # generate the map
    landscape = []
    noise = osn.OpenSimplex(seed=random.randint(0, 1000000))
    for y in range(args.height):
        row = []
        for x in range(args.width):
            n = noise.noise2(x / scale, y / scale)
            print(n)
            if threshold_low < n < threshold_high:
                row.append("wall")
            else:
                row.append("air")
        landscape.append(row)

    cmap = {
        "air": '0',
        "wall": '1',
        "door": 'D'
    }

    map_str = "1" * (args.width + 2) + "\n"
    for row in landscape:
        map_str += "1"
        for item in row:
            map_str += cmap[item]
        map_str += '1\n'
    map_str += "1" * (args.width + 2) + "\n"

    # Add some random doors
    map_arr = map_str.split("\n")
    map_arr = [list(row) for row in map_arr]
    for x, row in enumerate(map_arr):
        for y, item in enumerate(row):
            if item == "1" and match_wall(x, y, map_arr):
                if random.random() < 0.5:
                    map_arr[x][y] = "D"

    pos = (random.randint(1, args.width - 2), random.randint(1, args.height - 2))
    while map_arr[pos[0]][pos[1]] != "0":
        pos = (random.randint(1, args.width - 2), random.randint(1, args.height - 2))
    map_arr[pos[0]][pos[1]] = random.choice(["N", "S", "E", "W"])
    map_str = "\n".join(["".join(row) for row in map_arr])

    return map_str


def main():
    # map_ = wave_function_collapse()
    map_ = perlin_noise(5, -0.2, 0.2)

    # write the map to a file
    params = f"""
    
F {random.randint(0, 256)},{random.randint(0, 256)},{random.randint(0, 256)}
C {random.randint(0, 256)},{random.randint(0, 256)},{random.randint(0, 256)}

WE assets/test/west.png
NO assets/test/north.png
EA assets/test/east.png
SO assets/test/south.png
DO assets/test/door.png

{map_}
"""
    with open(parse_args().map, "w") as f:
        f.write(params)


if __name__ == '__main__':
    main()
