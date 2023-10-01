import("stdfaust.lib");
cv_freq = hslider("freq[name: Frequency]", 2.25, 0, 10, 0.001);
f = 55.0 * pow(2.0, cv_freq);
triangleWave = waveform{0,0.5,1,0.5,0,-0.5,-1,-.5};
triangleOsc(f) = triangleWave,int(os.phasor(8,f)) : rdtable;
process = triangleOsc(f);