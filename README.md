# Immediate tiny strings

Ahead of you is a small C library for what I called "immediate tiny
strings": Short ("tiny") strings are stored as immediate (without
indirection through a pointer) values.  This saves both time and space
overhead incurred by the otherwise necessary dynamic allocation.
Obviously using this library only makes sense when you expect lots of
rather short strings.

Note: A probably better known term for this is "small string
optimization".


## Dependencies

This library is written in pure C (I tried to stick to C99, to be
precise).  Thus no other libraries are necessary to build and use this
library.  In case you're using the sources directly from git you'll
need the autotools (autoconf, automake, libtool) to generate the build
system, though.


## Building

This library uses the autotools as its build system. Thus, from git
sources, you first need to generate the configure script and associate
files:


``` bash
# in top source directory
autoreconf -fvi
```

Afterwards, or when you got the source from a release, just do the usual

``` bash
# assuming in-source-build; thus in top source directory
./configure
make
make check
```

If you want you can then install the library:

``` bash
make install
```

If you want to keep it in a staging area (for testing, packaging,
whatever) first just specify `DESTDIR`:

``` bash
make DESTDIR=my/place install
```


## Using

First make sure that the library is in the library search path of your
compiler. Then include the header **its.h** and link with `-lits`.


## Documentation

The source code is mostly documented. If you have doxygen installed,
then a html documentation will be generated during `make`. If you have
the dot tool from graphviz installed then this documentation will
additionally feature nice little call graphs.

Be warned that the documentation is currently a mixture between
internal and public API documentation.


## Reporting bugs and contributing

If you find a bug then please let me know! Just open an issue here on
the bug tracker of this github project.  Same if you have a feature
request.  If you want to contribute code / documentation then please
open a pull request.
