declare name "Peak audio to CV";
declare author "GULA";
declare copyright "Steve Baker (2022)";
declare version "1.0.0";
declare license "GPLv3";
declare description "CV output value derived from the amplitude of the input, with auto-detection of the peak aplitude";

import("stdfaust.lib");
import("gula.lib");

attack = hslider("[01]attack[unit:s][name: Attack]", 0.01, 0, 0.5, 0.01);
release = hslider("[02]release[unit:s][name: Release]", 0.5, 0, 2, 0.01);
peak_decay = hslider("[03]peak_decay[unit:s][name: Peak Decay]", 5, 0, 30, 0.1);

process = _ : gula_ab_amp(attack, release, peak_decay) * 10 : _ ;
