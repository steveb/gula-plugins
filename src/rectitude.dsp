declare name "Rectitude";
declare author "Gula Plugins";
declare copyright "Steve Baker (2020)";
declare version "1.0.0";
declare license "GPLv3";
declare description "Combines two signals by fully rectifying both in opposite directions";

import("gula.lib");

gain_up = hslider("[1]gain_up [name: Gain Up][tooltip: Gain for the up rectified signal]", 1.0, 0.0, 1.0 ,0.01);
gain_down = hslider("[2]gain_down [name: Gain Down][tooltip: Gain for the down rectified signal]", 1.0, 0.0, 1.0 ,0.01);

rect_up = _, 0 : max * gain_up;
rect_down = _, 0 : min * gain_down;
process = _, _ : rect_up, rect_down :> _ ;