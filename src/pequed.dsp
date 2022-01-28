declare name "Pequed";
declare author "GULA";
declare copyright "Steve Baker (2022)";
declare version "1.0.0";
declare license "GPLv3";
declare description "Midrange parametic EQ with high and low values interpolated based on the peak amplitude of the input";

import("stdfaust.lib");
import("gula.lib");

freq_b = hslider("[01]freq_b[name:Freq Hi][tooltip:frequency (Hz)]", 900, 100, 2400, 10);
gain_b = hslider("[02]gain_b[name:Gain Hi][unit:dB]", 0, -40, 40, 0.1);

freq_a = hslider("[03]freq_a[name:Freq Lo][tooltip:frequency (Hz)]", 900, 100, 2400, 10);
gain_a = hslider("[04]gain_a[name:Gain Lo][unit:dB]", 0, -40, 40, 0.1);

q_mult = 0.2;
q_a = gain_a : abs * q_mult, 0.1 : max;
q_b = gain_b : abs * q_mult, 0.1 : max;

attack = hslider("[05]attack[unit:s][name: Attack]", 0.01, 0, 0.5, 0.01);
release = hslider("[06]release[unit:s][name: Release]", 0.5, 0, 2, 0.01);
peak_decay = release * 10;

process = _ <: gula_ab_amp(attack, release, peak_decay) , _ : gula_ab_filter(freq_a, gain_a, q_a, freq_b, gain_b, q_b) : _;
