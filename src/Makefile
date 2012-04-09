MK_CFG_DIR = /home/y/share/make_cfg
include $(MK_CFG_DIR)/make.defs

LIBNAME = yio
CSRC = sock_util.c

WARN +=
OPPFLAGS +=
LDFLAGS =
LDLIBS =

include $(MK_CFG_DIR)/make.rules

install:
	mkdir -p ${DESTDIR}/etc/ld.so.conf.d
	install -m644 yio.conf ${DESTDIR}/etc/ld.so.conf.d/yio.conf
	mkdir -p ${DESTDIR}/home/y/lib
	install -m755 libyio.so.1 ${DESTDIR}/home/y/lib/libyio.so.1
	ln -s libyio.so.1 ${DESTDIR}/home/y/lib/libyio.so
	mkdir -p ${DESTDIR}/home/y/include/yio
	install -m644 sock_util.h ${DESTDIR}/home/y/include/yio/sock_util.h
