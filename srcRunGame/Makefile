#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES := runGame.cpp oledController.cpp beeperControl.cpp

# header files in this project
HEADERS := runGame.hpp gameParameters.hpp gameTimer.hpp oledController.hpp beeperControl.hpp

# other places to look for files for this project
SEARCH  := ../srcBeeper

# set RELATIVE to the next higher directory and defer to the Makefile.due
RELATIVE := $(RELATIVE)../
include $(RELATIVE)MakefileACM.due
