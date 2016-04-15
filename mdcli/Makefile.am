AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = mdcli
mdcli_SOURCES = \
	Main.cc

mdcli_CPPFLAGS =  \
		$(BOOST_CPPFLAGS) \
		$(SOIL_CPPFLAGS) \
		$(ZOD_CPPFLAGS) \
		$(CATA_CPPFLAGS) \
		$(RAPIDJSON_CPPFLAGS) \
		$(JSON_CPPFLAGS)

mdcli_LDADD = \
	$(BOOST_LIBADD) \
	$(SOIL_LIBADD) \
	$(ZOD_LIBADD) \
	$(CATA_MD_LIBADD) \
	$(JSON_LIBADD)


mdcli_LDFLAGS = $(LIBADD_DL) -Wl,--no-as-needed -pthread

# header files
noinst_HEADERS = 

EXTRA_DIST = 

# mddir = $(bindir)
# md_DATA = $(EXTRA_DIST)

