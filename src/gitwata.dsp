declare name "Gitwata";
declare author "Gula Plugins";
declare copyright "Steve Baker (2023)";
declare license "GPLv3";
declare description "An LV2 plugin which uses CV inputs to control wavetable synthesis";

import("gula.lib");
import("wavetables/synthwave.lib");

cv_freq = hslider("freq[name: Frequency]", 2.25, 0, 10, 0.001);
cv_amp = hslider("amp[name: Amplitude]", 8.0, 0, 10, 0.01);
cv_index = hslider("index[name: Index]", 0.0, 0, 10, 0.01);

wave_index = cv_index / 10.0;
freq = 55.0 * pow(2.0, cv_freq);
amp = cv_amp / 10.0;

wave_offset = wave_file_offset + int(wave_index * (wave_table_count - 1)) * 2048;

phase = os.phasor(2048, freq);
prev_phase = phase';
delayed_wave_offset = wave_offset : ba.sAndH(phase < prev_phase);
sample_index = phase + delayed_wave_offset;
process = wave_tables, sample_index : rdtable * amp;
