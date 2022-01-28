declare name "Sweabed";
declare author "GULA";
declare copyright "Steve Baker (2020)";
declare version "1.0.0";
declare license "GPLv3";
declare description "Midrange parametic EQ with A and B settings which can be swept between with a single control";

import("gula.lib");

freq_a = hslider("[1]freq_a[name:Freq A][tooltip:frequency (Hz)]", 900, 100, 2400, 10);
gain_a = hslider("[2]gain_a[name:Gain A][unit:dB]", 0, -40, 40, 0.1);

freq_b = hslider("[4]freq_b[name:Freq B][tooltip:frequency (Hz)]", 900, 100, 2400, 10);
gain_b = hslider("[5]gain_b[name:Gain B][unit:dB]", 0, -40, 40, 0.1);

q_mult = 0.2;
q_a = gain_a : abs * q_mult, 0.1 : max;
q_b = gain_b : abs * q_mult, 0.1 : max;

ab_sweep_raw = hslider("[7]ab_sweep[name:A-B Sweep]", 0, 0, 1, 0.01);
ab_sweep = ab_sweep_raw : si.smooth(0.997);

process = _ : gula_ab_filter(freq_a, gain_a, q_a, freq_b, gain_b, q_b, ab_sweep) : _ ;
