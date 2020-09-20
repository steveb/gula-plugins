declare name "SSaP Tone";
declare author "Gula Plugins";
declare copyright "Steve Baker (2020)";
declare version "1.0.0";
declare license "GPLv3";
declare description "Tone shaping with a low shelf, a high shelf and a parametric EQ, all on the same frequency";

import("gula.lib");
si = library("signals.lib");

freq_raw = hslider("[1]freq[name:Freq][tooltip:frequency (Hz)]", 900, 200, 2000, 10);
bass_raw = hslider("[2]bass[name:Bass][unit:dB]", 0, -20, 20, 0.1);
mid_raw = hslider("[3]mid[name:Mid][unit:dB]", 0, -20, 20, 0.1);
mid_q_raw = hslider("[4]mid_q[name:Mid Q]", 1, 0.1, 4, 0.1);
treble_raw = hslider("[5]treble[name:Treble][unit:dB]", 0, -20, 20, 0.1);

bass = bass_raw : si.smooth(0.995);
mid = mid_raw : si.smooth(0.995);
mid_q = mid_q_raw : si.smooth(0.995);
treble = treble_raw : si.smooth(0.995);
freq = freq_raw : si.smooth(0.995);

process = _ : gula_ssap_tone(freq, bass, mid, mid_q, treble) : _ ;


