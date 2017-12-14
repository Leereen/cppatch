LIBDISPATCH=./swift-corelibs-libdispatch

# dirty build
libdispatch:
	(cd ${LIBDISPATCH} && ./autogen.sh && ./configure \
	&& $(MAKE) && sudo $(MAKE) install)
