include sources/driver/Ethernet/src/utility/Makefile.mk

CPPFLAGS += -I./sources/driver/Ethernet/src

VPATH += sources/driver/Ethernet/src

SOURCES_CPP += sources/driver/Ethernet/src/Dhcp.cpp
SOURCES_CPP += sources/driver/Ethernet/src/Dns.cpp
SOURCES_CPP += sources/driver/Ethernet/src/EthernetClient.cpp
SOURCES_CPP += sources/driver/Ethernet/src/Ethernet.cpp
SOURCES_CPP += sources/driver/Ethernet/src/EthernetServer.cpp
SOURCES_CPP += sources/driver/Ethernet/src/EthernetUdp.cpp
