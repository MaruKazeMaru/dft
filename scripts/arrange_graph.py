#!/usr/bin/env python3

# SPDX-FileCopyrightText: 2023 ShinagwaKazemaru
# SPDX-License-Identifier: MIT License

import json
import argparse

from graph_aranger import LineGraphArranger, HeatmapArranger

def main(args):
    with open(args.info, 'r') as f:
        ax_infos = json.load(f)

    if ax_infos['type'] == 'linegraph':
        arranger = LineGraphArranger(ax_infos)
    elif ax_infos['type'] == 'heatmap':
        arranger = HeatmapArranger(ax_infos)

    arranger.write(args.out, args.width, args.height)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('info', help='path of graph info', type=str)
    parser.add_argument('out', help='path of output image', type=str)
    parser.add_argument('-w', '--width',  help='width  of output image', type=int, default=960)
    parser.add_argument('-h', '--height', help='height of output image', type=int, default=540)
    main(parser.parse_args())
