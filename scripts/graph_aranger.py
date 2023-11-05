#!/usr/bin/env python3

# SPDX-FileCopyrightText: 2023 ShinagwaKazemaru
# SPDX-License-Identifier: MIT License

import matplotlib.pyplot as plt
from matplotlib.figure import Figure
from matplotlib.axes import Axes
from matplotlib.cm import ScalarMappable
from matplotlib.image import imread

class GraphArrangerBase:
    def __init__(self, ax_infos:dict):
        self.ax_infos = ax_infos
        self.graph = imread(self.ax_infos['graph_path'])
        self.xlabel = self.ax_infos['xlabel']
        self.ylabel = self.ax_infos['ylabel']
        self.xmin = self.ax_infos['xmin']
        self.xmax = self.ax_infos['xmax']
        self.ymin = self.ax_infos['ymin']
        self.ymax = self.ax_infos['ymax']


    def _append_other(self, fig:Figure, ax:Axes): pass


    def write(self, out_path:str, width:int, height:int):
        # 100 = default dpi of self.fig
        fig = plt.figure(figsize=(width/100,height/100))
        ax = fig.add_subplot()

        ax.imshow(self.graph, extent=(self.xmin,self.xmax,self.ymin,self.ymax), aspect='auto')

        ax.set_xlabel(self.xlabel)
        ax.set_ylabel(self.ylabel)

        self._append_other(fig, ax)

        fig.tight_layout()
        fig.savefig(out_path)


class LineGraphArranger(GraphArrangerBase):
    def _append_other(self, fig: Figure, ax: Axes):
        ax.set_yticks([0])


class HeatmapArranger(GraphArrangerBase):
    def _append_other(self, fig: Figure, ax: Axes):
        fig.colorbar( \
            ScalarMappable(cmap='binary'), label=self.ax_infos['clabel'], \
            ax=ax, location='right', orientation='vertical', ticks=[0] \
        )
