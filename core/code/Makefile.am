bin_PROGRAMS = epoch 
epoch_SOURCES = main/epoch.cpp
SUBDIRS = detection
epoch_LDFLAGS = -static
epoch_LDADD =  -lpthread
epoch_LDADD+= share/library/debug/libdetection.a
#lord_LDADD+= -LShare/llib/ -lmysqlclient

INCLUDES =  -Ishare/
INCLUDES += -Ishare/detection/
INCLUDES += -Idetection/
