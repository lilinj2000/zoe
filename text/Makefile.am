AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = text
text_SOURCES = \
	TextConfig.cc \
	TextServer.cc \
	Main.cc

text_CPPFLAGS =  \
		$(BOOST_CPPFLAGS) \
		$(SOIL_CPPFLAGS) \
		$(ZMQ_CPPFLAGS)

text_LDADD = \
	$(BOOST_LIBADD) \
	$(SOIL_LIBADD) \
	$(ZMQ_LIBADD)


text_LDFLAGS = $(LIBADD_DL) -Wl,--no-as-needed -pthread

# header files
noinst_HEADERS = TextConfig.hh TextLog.hh TextServer.hh 

EXTRA_DIST = env.sh text.cfg log.cfg

# textdir = $(bindir)
# text_DATA = $(EXTRA_DIST)

