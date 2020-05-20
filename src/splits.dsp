declare name "The Splits";
declare author "Gula Plugins";
declare copyright "Steve Baker (2020)";
declare version "1.0.0";
declare license "GPLv3";
declare description "An LV2 plugin which sends a controllable proportion of the input to each output";

import("gula.lib");
si = library("signals.lib");

raw_split = hslider("split [name: Split Proportion]", 1.0, 1.0, 4.0 ,0.001);
raw_spread = hslider("spread [name: Spread Overlap]", 1.0, 0.0, 3.0 ,0.001);

split = raw_split - 1.0 : si.smooth(0.9995);
spread = raw_spread : si.smooth(0.999);

process = _ <:
    *(gula_fade_gain(split, spread, 0.0)),
    *(gula_fade_gain(split, spread, 1.0)),
    *(gula_fade_gain(split, spread, 2.0)),
    *(gula_fade_gain(split, spread, 3.0));