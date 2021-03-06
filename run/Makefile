SHELL := /bin/bash

RCXX=$(shell root-config --cflags)
RLIB=$(shell root-config --libs)

CXX		= g++
CFLAGS		= -pipe -g \
-D __SKIP_CLASS_DEF__ \
-Wall -Wextra -Winit-self -Wcast-align -Wno-comment -Wno-ignored-qualifiers \
-O2 -march=native -mfpmath=sse -fPIC \
-Wl,--no-as-needed

#---- Paths ----#
inc = ../include
src = ../src

#---- Links ----#
links = -I$(inc) -I$(ROOTSYS)/include

CXXFLAGS	= $(CFLAGS) $(RCXX)
LDFLAGS		= -lm -L. $(RLIB)

#---- Targets ----#
Targets = makeOutput makeShared

#---- Generic Commands ----#
all: Makefile $(Targets)

obj/%.o:
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(links)
obj/%.so:
	$(CXX) -shared $< -o $@ -fPIC $(links)
obj/%_Dict.cxx:
	rootcint -f $@ -c $(links) $+

#---- CINT ----#
rootclass = 			\
	$(inc)/Event.h 		\
	$(inc)/Antenna.h 	\
	$(inc)/MetaData.h	\
	$(inc)/Summary.h	\
	$(inc)/Tools.h		\
	$(src)/Tools.cxx

obj/Event_Dict.cxx: 	$(rootclass) $(inc)/LinkDef.h
obj/Antenna_Dict.cxx:	$(rootclass) $(inc)/LinkDef.h
obj/MetaData_Dict.cxx:  $(rootclass) $(inc)/LinkDef.h
obj/Summary_Dict.cxx: 	$(rootclass) $(inc)/LinkDef.h
obj/Tools_Dict.cxx:	$(rootclass) $(inc)/LinkDef.h

#---- OBJ ----#
obj/Classes_Dict.o: 		\
	obj/Event_Dict.cxx 	\
	obj/Antenna_Dict.cxx 	\
	obj/MetaData_Dict.cxx 	\
	obj/Summary_Dict.cxx	\
	obj/Tools_Dict.cxx


#---- Shared Obj ----#
obj/Classes_Dict.so: 	 					\
	obj/Event_Dict.cxx $(inc)/Event.h  			\
	obj/Antenna_Dict.cxx $(inc)/Antenna.h 			\
	obj/MetaData_Dict.cxx $(inc)/MetaData.h			\
	obj/Summary_Dict.cxx $(inc)/Summary.h			\
	obj/Tools_Dict.cxx $(inc)/Tools.h $(src)/Tools.cxx 	

#---- Additional Objects ----#
obj/Reader.o:		$(src)/Reader.cxx
obj/TreeMaker.o:	$(src)/TreeMaker.cxx
#obj/Tools.o:		$(src)/Tools.cxx

makeOutput:			\
	obj/Reader.o		\
	obj/Classes_Dict.o	\
	obj/TreeMaker.o	
	$(CXX) $+ -o $@ $(CXXFLAGS) $(LDFLAGS) $(links)

makeShared: obj/Classes_Dict.so

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
	rm -f obj/*.o
	rm -f obj/*.so
	rm -f obj/*.cxx
	rm -f obj/*.h
