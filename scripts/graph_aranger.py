#!/usr/bin/env python3

# SPDX-FileCopyrightText: 2023 ShinagwaKazemaru
# SPDX-License-Identifier: MIT License

import matplotlib.pyplot as plt
from matplotlib.figure import Figure
from matplotlib.axes import Axes
from matplotlib.cm import ScalarMappable
from matplotlib.image import imread

class GraphArrangerBase:
    default_ticks_fontsize = 16
    default_label_fontsize = 20

    def __init__(self, ax_infos:dict, info_path:str):
        self.ax_infos = ax_infos
        ps = info_path.split('/')
        ps[-1] = self.ax_infos['graph_path']
        self.graph = imread('/'.join(ps))
        self.xlabel = self.ax_infos['xlabel']
        self.ylabel = self.ax_infos['ylabel']
        self.xmin = self.ax_infos['xmin']
        self.xmax = self.ax_infos['xmax']
        self.ymin = self.ax_infos['ymin']
        self.ymax = self.ax_infos['ymax']


    def _append_other(self, fig:Figure, ax:Axes, fontscale:float): pass


    def write(self, out_path:str, width:int, height:int):
        # 960 = default figure width
        # 20 = fontsize for 960x540
        fontscale = max(width, height) / 960
        plt.rcParams["font.size"] = self.default_ticks_fontsize * fontscale

        # 100 = default dpi of self.fig
        fig = plt.figure(figsize=(width/100,height/100))
        ax = fig.add_subplot()

        ax.imshow(self.graph, extent=(self.xmin,self.xmax,self.ymin,self.ymax), aspect='auto', cmap='gray')

        fontsize = fontscale * self.default_label_fontsize

        ax.set_xlabel(self.xlabel, fontsize=fontsize)
        ax.set_ylabel(self.ylabel, fontsize=fontsize)

        self._append_other(fig, ax, fontscale)

        fontsize = fontscale * self.default_ticks_fontsize
        ax.tick_params(labelsize=fontsize)

        fig.tight_layout()
        fig.savefig(out_path)


class LineGraphArranger(GraphArrangerBase):
    def _append_other(self, fig: Figure, ax: Axes, fontscale:float):
        ax.set_yticks([0])


class HeatmapArranger(GraphArrangerBase):
    def _append_other(self, fig: Figure, ax: Axes, fontscale:float):
        cb = fig.colorbar( \
            ScalarMappable(cmap='binary'), ax=ax, location='right', \
            orientation='vertical'\
        )
        fontsize = fontscale * self.default_label_fontsize
        cb.set_label(label=self.ax_infos['clabel'], fontsize=fontsize)
        cb.set_ticks([0])
