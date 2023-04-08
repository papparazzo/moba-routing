AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS = \
    moba-routing

moba_routing_SOURCES = \
    main.cpp 

moba_routing_LDADD = \
    -lmobacommon -lncurses $(GTKMM_LIBS) \
    $(srcdir)/../modules/lib-msghandling/src/moba/libmsghandling.a \
    $(srcdir)/../modules/lib-tracklayout/src/moba/libtracklayout.a

LDFLAGS += -L/usr/local/lib

AM_CPPFLAGS = \
    $(GTKMM_CFLAGS) \
    -I$(srcdir)/../modules/lib-msghandling/src \
    -I$(srcdir)/../modules/lib-tracklayout/src \
    -g3 -g -ggdb  -Wall -Wno-deprecated-declarations

CLEANFILES = *~
