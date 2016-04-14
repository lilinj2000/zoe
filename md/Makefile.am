AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = md
md_SOURCES = \
	Config.cc \
	Server.cc \
	Main.cc

md_CPPFLAGS =  \
		$(BOOST_CPPFLAGS) \
		$(SOIL_CPPFLAGS) \
		$(ZOD_CPPFLAGS) \
		$(CATA_CPPFLAGS) \
		$(RAPIDJSON_CPPFLAGS) \
		$(JSON_CPPFLAGS)

md_LDADD = \
	$(BOOST_LIBADD) \
	$(SOIL_LIBADD) \
	$(ZOD_LIBADD) \
	$(CATA_MD_LIBADD) \
	$(JSON_LIBADD)


md_LDFLAGS = $(LIBADD_DL) -Wl,--no-as-needed -pthread

# header files
noinst_HEADERS = Config.hh Log.hh Server.hh 

EXTRA_DIST = env.sh md.cfg log.cfg

# mddir = $(bindir)
# md_DATA = $(EXTRA_DIST)

