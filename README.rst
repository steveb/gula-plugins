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
* 1: This behaves like a crossfade in reverse. The split value will send the input
     to 2 adjacent outputs in proportion to the split fraction
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

.. _Faust installation: https://faust.grame.fr/doc/manual/index.html#compiling-and-installing-the-faust-compiler
.. _MOD Devices: https://www.moddevices.com/
