declare name "The Vibey";
declare author "Gula Plugins";
declare copyright "Steve Baker (2019)";
declare version "1.0.0";
declare license "GPLv3";
declare description "An LV2 plugin which is a combination of vibrato and tremolo";

import("stdfaust.lib");
vib_dmax = 1024;

// enough buffer to move the phase of a 0.4Hz vibrato with SR 48kHz
vib_offset_dmax = 131072;

trem_depth = hslider("trem_depth [name: Tremolo Depth][tooltip: Depth of the Tremolo]", 0.24, 0.0, 1.0 ,0.01);
trem_shape = hslider("trem_shape [name: Tremolo Shape][tooltip: Wave shape of tremelo]", 0.0, 0.0, 3.0 ,0.01);
trem_slant = hslider("trem_slant [name: Tremolo Slant][tooltip: Amount of slant to the left or right of the wave shape]", 0.0, -1.0, 1.0 ,0.01);

vib_depth = hslider("vib_depth [name:Vibrato Depth][tooltip: Amount of pitch bend of the vibrato]", 0.12, 0.0, 1.0 ,0.01);
vib_offset = hslider("vib_offset [name:Vibrato Offset][tooltip: Phase offset of the vibrato vs the tremolo]", 0.0, 0.0, 1.0, 0.01);
freq = hslider("rate [log][name: Rate][tooltip: Frequency of tremolo and vibrato]", 4.0, 0.4, 10.0 ,0.01);

delay_i = ba.lin2LogGain(vib_depth) * vib_dmax : si.smooth(0.999);
vib_delay = vib_offset * ma.SR / freq : si.smooth(0.999);

osc_orig = ba.lin2LogGain(os.osc(freq));
osc_delayed = osc_orig : de.fdelayltv(3, vib_offset_dmax, min(vib_offset_dmax, vib_delay));

trem_min = ba.lin2LogGain(1 - trem_depth);

// TODO implement me
trem_todo = trem_shape + trem_slant;

// scale from -1..1 to desired ranges
// (x-min(x))*(b-a)/(max(x)-min(x)) + a;
osc_trem = (osc_orig + 1.0) * (1 - trem_min) / 2.0 + trem_min;
osc_vib = (osc_delayed + 1.0) * delay_i / 2.0;

vibrato = de.fdelayltv(3, vib_dmax, min(vib_dmax, osc_vib));

// process = os.osc(440) : osc_trem * vibrato : _;
process = _ : osc_trem * vibrato + trem_todo: _;