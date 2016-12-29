# UHD VNA

This is a super-hacky experiment to use a UHD-based software defined radio as a
vector network analyzer.

Required ingredients for a VNA are:

* Two phase-coherent receivers per test port (four receivers for a two-port VNA).
* One source transmitter, which does not need to be phase-coherent.
* A test set. This can be configured a number of different ways, but an example
  starting point for a 2-port VNA would be a pair of splitters, a pair of
  directional couplers, and a reference load.

A Python API and a command-line tool are offered.

This tool is structured as a Python package with a native C++ extension that
directly uses the UHD C++ API. While it would be simpler in some ways to use
GNU Radio blocks via Python (and avoid the need for a native C++ extension),
there are two problems with a strictly GNU Radio based approach:

* As of the initial writing (Dec 2016) GNU Radio does not support Python 3.
* Certain advanced LO (local oscillator) configurations are not available via
  the GNU Radio API.

# Building

First install UHD. Then:

    $ pip install uhdvna

If UHD is not installed in the default prefix (``/usr/local``), you can specify
the prefix with an environment variable:

    $ PREFIX=/opt/local pip install uhdvna
