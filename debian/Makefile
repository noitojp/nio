dummy:

install:
	mkdir -p ${DESTDIR}/etc/ld.so.conf.d
	install -m644 nio.conf ${DESTDIR}/etc/ld.so.conf.d/nio.conf
	mkdir -p ${DESTDIR}/home/z/lib
	install -m755 libnio.so.1 ${DESTDIR}/home/z/lib/libnio.so.1
	ln -s libnio.so.1 ${DESTDIR}/home/z/lib/libnio.so
	mkdir -p ${DESTDIR}/home/z/include/nio
	install -m644 sock_util.h ${DESTDIR}/home/z/include/nio/sock_util.h
