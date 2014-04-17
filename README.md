Balloon-2014
============

Houghton College Science Honors Balloon Project

This is the code designed to control the weather balloon (radiosonde). The
repository currently contains the code for the balloon (slave), computer on the
ground (master), and a codePlayground section designed to hold various programs
which may be of use in designing the main code. The slave code is written to be
compiled and uploaded to an Arduino (oriented toward the Uno model) while the
master code is designed to be compiled and run on Linux (and potentially other
Unix-based operating systems like OSX). Porting to Windows is probably
unrealistic.

The master program will use gnuplot to produce graphs of the data in realtime.
This will be concatenated within a webpage with a frame of the current GPS
track (some sort of KML). In this state, it will be very easy to run a webserver
to allow remote viewing. A benefit to this is that simpler pages can also be
produced; these can be used within iframes in various places (like the Science
Honors blog).

Compiling of the master is currently acheived directly through the use of G++.

```
g++ -o foo foo.cc
```

While simple to do, it has the disadvantage of explicit includes, which are
essentially like concatenating the libraries into one file:

```
#include "foo.h"
#include "foo.cc"
```

However, for the relative simplicity of this program, this is the method which
will be employed until a makefile can be produced. 

For the slave program, compiling is designed to be compatible with both the
Arduino IDE as well as Ino (a commandline arduino compiler). These compile
using custom makefiles, so expect normal includes:

```
#include "foo.h"
```

For those unfamiliar with the process, the way it works is to compile each *.cpp
separately into *.o files. Then, they are linked together by the compiler into
one binary program.


Libraries
---------

###Data

This handles all data operations. This includes wrapping multiple protocols into
one operation.

Functions:
(coming soon)

###Borp

This handles the radio operations. Sends data, listens to the master, etc.

Functions:
(coming soon)









