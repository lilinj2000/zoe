AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = proxy
proxy_SOURCES = \
	ProxyConfig.cc \
	ProxyServer.cc \
	Main.cc

proxy_CPPFLAGS =  \
		$(BOOST_CPPFLAGS) \
		$(SOIL_CPPFLAGS) \
		$(ZMQ_CPPFLAGS)

proxy_LDADD = \
	$(BOOST_LIBADD) \
	$(SOIL_LIBADD) \
	$(ZMQ_LIBADD)


proxy_LDFLAGS = $(LIBADD_DL) -Wl,--no-as-needed -pthread

# header files
noinst_HEADERS = ProxyConfig.hh ProxyLog.hh ProxyServer.hh 

EXTRA_DIST = env.sh proxy.cfg log.cfg

# proxydir = $(bindir)
# proxy_DATA = $(EXTRA_DIST)

