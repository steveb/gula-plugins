GULA Plugins
------------

A collection of guitar effect LV2 plugins with `MOD Devices`_ user interfaces.

To build the plugins you will require a working `Faust installation`_. The LV2
shared libraries can then be built by running::

  make

This will result in the `*.lv2` directories being ready to be copied to the
desired LV2 plugin directory.

The Vibey
=========

An LV2 plugin which is a combination of vibrato and tremolo. The depth of each
can be controlled and the phase offset of the vibrato can be set relative to
the tremolo.


.. _Faust installation: https://faust.grame.fr/doc/manual/index.html#compiling-and-installing-the-faust-compiler
.. _MOD Devices: https://www.moddevices.com/
