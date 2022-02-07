GULA Plugins
------------

A collection of guitar effect LV2 plugins with `MOD Devices`_ user interfaces.

To build the plugins you will require a working `Faust installation`_. The LV2
shared libraries can then be built by running::

  make all

This will result in the `lv2/*.lv2` directories being ready to be copied to the
desired LV2 plugin directory.

The Vibey
=========

An LV2 plugin which is a combination of vibrato and tremolo. The depth of
each can be controlled and the phase offset of the vibrato can be set
relative to the tremolo. The tremolo waveform can be a blend of sine,
sawtooth, triangle and square waves. The output is stereo with the tremolo
allocating between the left and right channels. The right channel can be
ignored for a mono tremolo effect.

The Tremolo Shape (T SHAPE) control sets the following tremolo waveform
for each value:

* 0 -> 1: random -> sine wave
* 1 -> 2: sine wave -> square wave
* 2 -> 3: square wave with changing on/off ratio
* 3 -> 4: saw (ascending) -> triangle -> saw (descending)
* 4 -> 5: manual static value from 1 -> 0

The Splits
==========

An LV2 plugin which sends a controllable proportion of the input to up to 4 outputs.

The split control determines which output the input signal is sent to. This value
is smoothed so that it can be modulated with minimal audible artifacts.

The spread control determines how much of the input signal is sent to other outputs:
* 1: This behaves like a crossfade in reverse. The split value will send the input to 2 adjacent outputs in proportion to the split fraction
* 0: This behaves like a switch between adjacent outputs
* 1 -> 3: For higher spread values, the input signal is spread to 3 or more outputs

The Fades
=========
An LV2 plugin which crossfades up to 4 inputs to one output.

The fade control determines the mix of which inputs are sent to the output. This value
is smoothed so that it can be modulated with minimal audible artifacts.

The spread control determines how much of the other input signals is sent to output:
* 1: This behaves like a crossfade. The fade value will mix 2 adjacent inputs in proportion to the fade fraction
* 0: This behaves like a switch between adjacent inputs
* 1 -> 3: For higher spread values, the mix includes 3 or more inputs

SSaP Tone
=========
Tone shaping with a low shelf, a high shelf and a parametric EQ, all on the same frequency.

This is an attempt at replacing the classic amp tone stack using digital filter modules.
The bass and treble controls are shelf filters which can raise or lower by 20dB. The midrange
is a parametric EQ which includes its own Q value. The frequency for all three filters is determined
by a single frequency value. The result is a pedal flexible enough to do subtle tone shaping, wah effects,
strong midrange scoops, or midrange boosts.

Sweabed
=======
Midrange parametic EQ with A and B settings which can be swept between with a single control

Parametric EQ values for A and B are set independently, and the AB Sweep control
interpolates between them. Instead of having an independent Q value, there is a
proportional Q which raises with the absolute gain.

This can be used to create wah-like effects, or other effects sweeping
broad/narrow boosts/cuts.

Pequed
======
Midrange parametic EQ with high and low values interpolated based on the peak amplitude of the input

Parametric EQ values for A and B are set independently, and the amplitude of the input
interpolates between them. Instead of having an independent Q value, there is a
proportional Q which raises with the absolute gain.

Attack and Release determine how fast the interpolated index can change.

The 'LO' values are the interpolation point for silent input. The 'HI' values are the interpolation point
for the most recent peak amplitude. This peak amplitude decays at a rate 10 times the Release value. This allows
full interpolation to be possible for an input which varies in amplitude over time.

Peak audio to CV
================
CV output value derived from the amplitude of the input, with auto-detection of the peak aplitude

Attack and Release determine how fast the output value changes. The Peak Decay determines how quickly the
detected peak value decays back to zero.

LFO CV
======
A CV output of an LFO with multiple shape modes and shapes

The Shape control determines the LFO shape depending on the Mode:

Random -> Sine:
0, smoothed random values changing at the Rate
0.5, a blend of random and sine wave
1, a sine wave

Sine -> Square
0, a sine wave
0.5, a blend of sine and square
1, a square wave

Impulse -> Square -> Pulse
0, an impulse
0.5, a square wave
1, a pulse (on until the end of the cycle, then off)

Saw (asc) -> Tri -> Saw (desc)
0, an ascending saw wave
0.5, a triangle wave
1, a descending saw wave

Rectitude
=========
Combines two signals by fully rectifying both in opposite directions

The first signal is rectified only passing positive values, and the second only
passing negative values. When the same signal is used for both inputs then even
harmonics can be produced by changing one of the gains. Other distortion effects
can be achieved by mixing a dry and a distorted signal, or combining two
distorted signals.

.. _Faust installation: https://faust.grame.fr/doc/manual/index.html#compiling-and-installing-the-faust-compiler
.. _MOD Devices: https://www.moddevices.com/
