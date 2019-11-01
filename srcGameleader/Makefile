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
SOURCES := terminal.cpp gameLeaderController.cpp

# header files in this project
HEADERS := terminal.hpp gameLeaderController.hpp bitHelper.hpp 

# other places to look for files for this project
SEARCH  := #./../lasertag/srcSender/

# set REATIVE to the next higher directory 
# and defer to the Makefile.due there
RELATIVE := $(RELATIVE)../
include $(RELATIVE)Makefile.due
