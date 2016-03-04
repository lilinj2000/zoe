AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = db
db_SOURCES = \
	DBConfig.cc \
	DBServer.cc \
	Main.cc

db_CPPFLAGS =  \
		$(BOOST_CPPFLAGS) \
		$(SOIL_CPPFLAGS) \
		$(ZMQ_CPPFLAGS) \
		$(SQLITE_CPPFLAGS) \
		$(RAPIDJSON_CPPFLAGS)

db_LDADD = \
	$(BOOST_LIBADD) \
	$(SOIL_LIBADD) \
	$(ZMQ_LIBADD) \
	$(SQLITE_LIBADD)


db_LDFLAGS = $(LIBADD_DL) -Wl,--no-as-needed -pthread

# header files
noinst_HEADERS = DBConfig.hh DBLog.hh DBServer.hh 

EXTRA_DIST = env.sh db.cfg log.cfg

# dbdir = $(bindir)
# db_DATA = $(EXTRA_DIST)

