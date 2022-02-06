declare name "Pequed";
declare author "GULA";
declare copyright "Steve Baker (2022)";
declare version "1.0.0";
declare license "GPLv3";
declare description "Midrange parametic EQ with high and low values interpolated based on the peak amplitude of the input";

import("stdfaust.lib");
import("gula.lib");

freq_hi = hslider("[01]freq_hi[name:Freq Hi][tooltip:frequency (Hz)]", 900, 100, 2400, 10);
gain_hi = hslider("[02]gain_hi[name:Gain Hi][unit:dB]", 0, -40, 40, 0.1);

freq_lo = hslider("[03]freq_lo[name:Freq Lo][tooltip:frequency (Hz)]", 900, 100, 2400, 10);
gain_lo = hslider("[04]gain_lo[name:Gain Lo][unit:dB]", 0, -40, 40, 0.1);

q_mult = 0.2;
q_a = gain_lo : abs * q_mult, 0.1 : max;
q_b = gain_hi : abs * q_mult, 0.1 : max;

attack = hslider("[05]attack[unit:s][name: Attack]", 0.01, 0, 0.5, 0.01);
release = hslider("[06]release[unit:s][name: Release]", 0.5, 0, 2, 0.01);
peak_decay = release * 10;

process = _ <: gula_ab_amp(attack, release, peak_decay) , _ : gula_ab_filter(freq_lo, gain_lo, q_a, freq_hi, gain_hi, q_b) : _;
