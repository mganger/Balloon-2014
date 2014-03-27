Balloon-2014
============

Houghton College Science Honors Balloon Project

This is the code designed to control the weather balloon (radiosonde). The
repository currently contains the code for the balloon (slave), computer on the
ground (master), and a codePlayground section designed to hold various programs
which may be of use in designing the main code. The slave code is written to be
compiled and uploaded to an Arduino (oriented toward the Due model) while the
master code is designed to be compiled and run on Linux (and potentially other
Unix-based operating systems like OSX). To run on Windows, much of the serial
read and write code has to be rewritten.

The master program will use gnuplot to produce graphs of the data in realtime.
This will be concatenated within a webpage with a frame of the current GPS
track (some sort of KML). In this state, it will be very easy to run a webserver
to allow remote viewing. A benefit to this is that simpler pages can also be
produced; these can be used within iframes in various places (like the Science
Honors blog).

Compiling is currently acheived directly through the use of G++.
	g++ -o foo foo.cc
While simple todo, it has the disadvantage of explicit includes:
	#include "foo.h"
	#include "foo.cc"
However, for the relative simplicity of this program, this is the method which
will be employed until a makefile can be produced.
