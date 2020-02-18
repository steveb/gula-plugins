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

Vintage Mics
============

An LV2 plugin which processes the signal with impulse responses from vintage microphones.
The plugin packages impulse responses from the
`Microphone Impulse Response Project`_ and these impulses are licensed as `CC BY-SA 4.0`_.

God's Cab
=========

An LV2 plugin which processes the signal with impulse responses from the
God's Cab collection created by `Wilkinson Audio`_. Only a subset of the
collection is included (room and TS impulses are removed,
only presence=5 impulses are included).

.. _Faust installation: https://faust.grame.fr/doc/manual/index.html#compiling-and-installing-the-faust-compiler
.. _MOD Devices: https://www.moddevices.com/
.. _Microphone Impulse Response Project: http://micirp.blogspot.com/
.. _CC BY-SA 4.0: https://creativecommons.org/licenses/by-sa/4.0/
.. _Wilkinson Audio: https://wilkinsonaudio.com/
