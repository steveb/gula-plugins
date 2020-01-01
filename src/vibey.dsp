declare name "The Vibey";
declare author "Gula Plugins";
declare copyright "Steve Baker (2019)";
declare version "1.0.0";
declare license "GPLv3";
declare description "An LV2 plugin which is a combination of vibrato and tremolo";

import("stdfaust.lib");
vib_dmax = 1024;

freq = hslider("rate [log][name: Rate][tooltip: Frequency of tremolo and vibrato]", 4.0, 0.4, 10.0 ,0.01);
trem_depth = hslider("trem_depth [name: Tremolo Depth][tooltip: Depth of the Tremolo]", 0.24, 0.0, 1.0 ,0.01);
trem_shape = hslider("trem_shape [name: Tremolo Shape][tooltip: Wave shape of tremelo]", 0.0, 0.0, 4.99 ,0.01);

vib_depth = hslider("vib_depth [name:Vibrato Depth][tooltip: Amount of pitch bend of the vibrato]", 0.12, 0.0, 1.0 ,0.01);
vib_offset = hslider("vib_offset [name:Vibrato Offset][tooltip: Phase offset of the vibrato vs the tremolo]", 0.0, 0.0, 1.0, 0.01);

trem_saw = os.lf_sawpos(freq);
trem_sawd = 1.0 - os.lf_sawpos(freq);
trem_tri = os.lf_trianglepos(freq);
trem_squ = os.lf_squarewavepos(freq);
trem_sin = (os.oscsin(freq) + 1.0) / 2.0;

trem_a = trem_sin, trem_saw, trem_tri, trem_sawd, trem_squ: ba.selectn(5, trem_shape : int);
trem_b = trem_saw, trem_tri, trem_sawd, trem_squ, trem_sin : ba.selectn(5, trem_shape : int);

trem_b_amp = trem_shape - floor(trem_shape);
trem_a_amp = 1.0 - trem_b_amp;
trem_blend = (trem_a * trem_a_amp) + (trem_b * trem_b_amp) : si.smooth(0.99);

trem_min = ba.lin2LogGain(1 - trem_depth);
trem_depthed = trem_blend * (1 - trem_min) + trem_min;
// trem = trem_depthed : hbargraph("trem level", 0.0, 1.0);
trem = trem_depthed;

vib_amp = ba.lin2LogGain(vib_depth) * vib_dmax : si.smooth(0.999);
vib_osc = (os.oscp(freq, 6.28318 * vib_offset : si.smooth(0.999)) + 1.0) * vib_amp / 2.0;
vibrato = de.fdelayltv(3, vib_dmax, min(vib_dmax, vib_osc));

// process = os.osc(440) <: trem * vibrato, (1-trem) * vibrato;
process = _ <: trem * vibrato, (1-trem) * vibrato;