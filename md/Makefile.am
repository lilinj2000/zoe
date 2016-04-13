AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = md
md_SOURCES = \
	MDConfig.cc \
	MDServer.cc \
	Main.cc

md_CPPFLAGS =  \
		$(BOOST_CPPFLAGS) \
		$(SOIL_CPPFLAGS) \
		$(ZOD_CPPFLAGS) \
		$(CATA_CPPFLAGS)

md_LDADD = \
	$(BOOST_LIBADD) \
	$(SOIL_LIBADD) \
	$(ZOD_LIBADD) \
	$(CATA_MD_LIBADD)


md_LDFLAGS = $(LIBADD_DL) -Wl,--no-as-needed -pthread

# header files
noinst_HEADERS = MDConfig.hh MDLog.hh MDServer.hh 

EXTRA_DIST = env.sh md.cfg log.cfg

# mddir = $(bindir)
# md_DATA = $(EXTRA_DIST)

