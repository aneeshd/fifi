News for fifi
============

This file lists the major changes between versions. For a more detailed list
of every change, see the Git log.

tbd (master)
------------
* Switched c++11 compiler flag on per default
* Adding optimal prime field
* Moving benchmarks to the gauge tool
* Moved fifi headers to the sub-directory src

2.0.0
-----
* Updated the Waf build system to handle dependencies better. The new tools
  used are not compatible with the old versions so we have to bump the major
  version.

1.0.2
-----
* Added bechmarks
* Added dependency on sak providing timer functionality
  used in benchmarks
* Bumped dependency version for gtest to 1.0.3-gtest_1_6_0
* Bumped dependency version for boost to 1.1.2-boost_1_48_0
* Bumped dependency version for sak to 1.1.1
* Fixed win32 link and cxx flags

