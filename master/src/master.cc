/*
 * master.cc
 * This file is part of Borp
 *
 * Copyright (C) 2014 - Houghton College Science Honors
 *
 * Borp is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Borp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Borp. If not, see <http://www.gnu.org/licenses/>.
 *
 * Current Dependencies:
 *	openssl headers (openssl-devel on fedora)
 *		NOT ANYMORE. MD5 capability in the hash-library
 */


#include <stdio.h>
#include "../lib/md5.h"

int main()
{
	//Transferred from the programFlow chart
	//
	//Send message to slave
	//listen on serial port *We may be able to do this on a different thread
	//for(time<100ms;;){
	//	listen for data
	//	check for error
	//	Write to file
	//}
}
