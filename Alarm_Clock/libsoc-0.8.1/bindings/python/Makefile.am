libsocdir = $(pyexecdir)/libsoc
libsoc_PYTHON = __init__.py gpio.py i2c.py

AM_CPPFLAGS = $(PYTHON_CFLAGS) -I${top_srcdir}/lib/include -DLIBSOC_SO=\"@prefix@/lib/libsoc.so\"

libsoc_LTLIBRARIES = _libsoc.la
_libsoc_la_LDFLAGS = -module -avoid-version -export-dynamic $(PYTHON_LIBS)
_libsoc_la_SOURCES = gpio_python.c
