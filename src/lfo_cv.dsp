declare name "LFO CV";
declare author "Gula Plugins";
declare copyright "Steve Baker (2022)";
declare version "1.0.0";
declare license "GPLv3";
declare description "A CV output of an LFO with multiple shape modes and shapes";

import("gula.lib");

shape_mode = hslider("[01]shape_mode [name: Shape Mode][style:menu{'Random -> Sine': 0; 'Sine -> Square': 1; 'Impulse -> Square -> Pulse': 2; 'Saw (asc) -> Tri -> Saw (desc)': 3}]", 0, 0, 3, 1);
freq = hslider("[02]rate [log][name: Rate][tooltip: Frequency of oscillator]", 4.0, 0.4, 10.0 ,0.01);
amp = hslider("[03]amplitude [name: Amplitude][tooltip: Amplitude of signal]", 10, 0.0, 10.0 ,0.1);
offset = hslider("[04]offset [name: Offset][tooltip: Offset of signal]", 0, -5.0, 5.0 ,0.1);
shape = hslider("[05]shape [name: Shape][tooltip: Wave shape for mode]", 1.0, 0.0, 1.0 ,0.01), 0.99 : min;

output = gula_lf_osc_normal(freq, shape_mode + shape) : scale(-0.5 + (offset / 10), amp) ;

process = output : hbargraph("lfo_out", -10, 10);