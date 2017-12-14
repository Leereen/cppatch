[![Travis Build Status](https://travis-ci.org/Leereen/cppatch.svg?branch=master)](https://travis-ci.org/Leereen/cppatch)

WIP


## Current travis builds:

### Trusty

#### Dependencies

* [Libdispatch project](https://github.com/apple/swift-corelibs-libdispatch),
  as the `libdispatch` provided in Ubuntu / Debian APT seems not to embed some
  capabilities such as `DISPATCH_QUEUE_PRIORITY_BACKGROUND`. I should check on
  that at some point.

  This library needs the following dependencies: `cmake` `clang` `systemtap-sdt-dev`
  `libbsd-dev` `linux-libc-dev`, maybe `ninja-build` depending how you build.

### OS X

(2017-12-15) Travis' default OS X version is 10.12.6 and Xcode 8.3.3.
The build does not seem to need any dependency for now.