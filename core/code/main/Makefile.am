bin_PROGRAMS = main
lord_SOURCES = ../../code/main/epoch.cpp
SUBDIRS = ../../code/detection
lord_LDFLAGS = -static
lord_LDADD =  -lpthread
lord_LDADD+= ../../code/share/library/libdetection.a
#lord_LDADD+= -LShare/llib/ -lmysqlclient

INCLUDES =  -I@top_srcdir@/code/share/
INCLUDES += -I@top_srcdir@/code/share/detection/
INCLUDES += -I@top_srcdir@/code/detection/