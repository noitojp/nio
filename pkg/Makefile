dummy:

install:
	mkdir -p ${DESTDIR}/etc/ld.so.conf.d
	install -m644 nio.conf ${DESTDIR}/etc/ld.so.conf.d/nio.conf
	mkdir -p ${DESTDIR}/home/y/lib
	install -m755 libnio.so.1 ${DESTDIR}/home/y/lib/libnio.so.1
	ln -s libnio.so.1 ${DESTDIR}/home/y/lib/libnio.so
	mkdir -p ${DESTDIR}/home/y/include/nio
	install -m644 sock_util.h ${DESTDIR}/home/y/include/nio/sock_util.h
