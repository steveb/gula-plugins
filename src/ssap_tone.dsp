declare name "SSaP Tone";
declare author "Gula Plugins";
declare copyright "Steve Baker (2020)";
declare version "1.0.0";
declare license "GPLv3";
declare description "Tone shaping with a low shelf, a high shelf and a parametric EQ, all on the same frequency";

import("gula.lib");

freq_raw = hslider("[1]freq[name:Freq][tooltip:frequency (Hz)]", 900, 200, 2000, 10);
bass_raw = hslider("[2]bass[name:Bass][unit:dB]", 0, -20, 20, 0.1);
mid_raw = hslider("[3]mid[name:Mid][unit:dB]", 0, -20, 20, 0.1);
mid_q_raw = hslider("[4]mid_q[name:Mid Q]", 1, 0.1, 4, 0.1);
treble_raw = hslider("[5]treble[name:Treble][unit:dB]", 0, -20, 20, 0.1);

bass = bass_raw : si.smooth(0.999);
mid = mid_raw : si.smooth(0.999);
mid_q = mid_q_raw : si.smooth(0.999);
treble = treble_raw : si.smooth(0.999);
freq = freq_raw : si.smooth(0.995);

bass_filter = fi.lowshelf(3,bass,freq);
treble_filter = fi.highshelf(3,treble,freq);
mid_filter = fi.peak_eq_cq(mid, freq, mid_q);
process = _ : bass_filter : treble_filter : mid_filter : _ ;


