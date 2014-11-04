SHELL := /bin/bash

RCXX=$(shell root-config --cflags)
RLIB=$(shell root-config --libs)

CXX		= g++
CFLAGS		= -pipe -g \
-D __SKIP_CLASS_DEF__ \
-I.. \
-Wall -Wextra -Winit-self -Wcast-align -Wno-comment -Wno-ignored-qualifiers \
-O2 -march=native -mfpmath=sse -fPIC \
-Wl,--no-as-needed

#---- Paths ----#
inc = ../include
src = ../src

#---- Links ----#
links = -I$(inc)

CXXFLAGS	= $(CFLAGS) $(RCXX) -lTreePlayer
LDFLAGS		= -lm -L. $(RLIB)

#---- Packages Dependencies ----#
Targets = #ana makeTree testTrackTool

all: Makefile $(Targets)

obj/%.so:
	$(CXX) -c $< -o $@ $(SOFLAGS) $(CXXFLAGS) $(links)

#---- ROOT Objects ----#
obj/Event_Dict.cxx: $(inc)/Event.h $(inc)/LinkDef.h
	rootcint -f $@ -c -I$(inc) $+
obj/Antenna_Dict.cxx: $(inc)/Antenna.h $(inc)/LinkDef.h
	rootcint -f $@ -c -I$(inc) $+
obj/MetaData_Dict.cxx: $(inc)/MetaData.h $(inc)/LinkDef.h
	rootcint -f $@ -c -I$(inc) $+
obj/MyClass_Dict.so: \
	obj/Event_Dict.cxx $(inc)/Event.h \
	obj/Antenna_Dict.cxx $(inc)/Antenna.h \
	objc/MetaData_Dict.cxx $(inc)/MetaData.h
	$(CXX) -c $< -o $@ $(SOFLAGS) $(CXXFLAGS) -Os -g1 -I$(inc)

#---- Additional Objects ----#
#obj/DataPoints.so:	$(src)/DataPoints.cxx
#obj/ZHSPoints.so:	$(src)/ZHSPoints.cxx
#obj/Detector.so:	$(inc)/Detector.h

#ana:	 			\
#	obj/Particle_Dict.so	\
#	obj/Event_Dict.so	\
#	obj/TrackTool.so	\
#	obj/DataPoints.so	\
#	obj/ZHSPoints.so	\
#	obj/Detectors.so	\
#	obj/Dim3.so		\
#	obj/Mixer.so		\
#	obj/SaveOutput.so	\
#	obj/Analyze.so		\
#	obj/Ana.so
#	$(CXX) $+ -o $@ $(CXXFLAGS) $(LDFLAGS) $(links)

clean:
	rm -f $(Targets)
	rm -f obj/*.so
	rm -f obj/*.so
	rm -f obj/*.cxx
	rm -f obj/*.h
