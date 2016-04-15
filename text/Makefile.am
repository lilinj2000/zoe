AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = text
text_SOURCES = \
	Config.cc \
	Server.cc \
	Main.cc

text_CPPFLAGS =  \
		$(BOOST_CPPFLAGS) \
		$(SOIL_CPPFLAGS) \
		$(ZOD_CPPFLAGS)

text_LDADD = \
	$(BOOST_LIBADD) \
	$(SOIL_LIBADD) \
	$(ZOD_LIBADD)


text_LDFLAGS = $(LIBADD_DL) -Wl,--no-as-needed -pthread

# header files
noinst_HEADERS = Config.hh Log.hh Server.hh 

EXTRA_DIST = env.sh text.cfg log.cfg

# textdir = $(bindir)
# text_DATA = $(EXTRA_DIST)

