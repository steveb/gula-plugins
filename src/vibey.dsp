declare name "The Vibey";
declare author "Gula Plugins";
declare copyright "Steve Baker (2019)";
declare version "1.0.0";
declare license "GPLv3";
declare description "An LV2 plugin which is a combination of vibrato and tremolo";

import("gula.lib");

freq = hslider("rate [log][name: Rate][tooltip: Frequency of tremolo and vibrato]", 4.0, 0.4, 10.0 ,0.01);
trem_depth = hslider("trem_depth [name: Tremolo Depth][tooltip: Depth of the Tremolo]", 0.24, 0.0, 1.0 ,0.01);
trem_shape = hslider("trem_shape [name: Tremolo Shape][tooltip: Wave shape of tremelo]", 0.0, 0.0, 4.99 ,0.01);

vib_depth = hslider("vib_depth [name:Vibrato Depth][tooltip: Amount of pitch bend of the vibrato]", 0.12, 0.0, 1.0 ,0.01);
vib_offset = hslider("vib_offset [name:Vibrato Offset][tooltip: Phase offset of the vibrato vs the tremolo]", 0.0, 0.0, 1.0, 0.01);

// trem = gula_lf_osc(freq, trem_depth, trem_shape) : hbargraph("trem level", 0.0, 1.0);
trem = gula_lf_osc(freq, trem_depth, trem_shape);
vibrato = gula_vibrato(freq, vib_depth, vib_offset);

process = _ <: trem * vibrato, (1-trem) * vibrato : _,_;