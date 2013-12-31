// Author:  Cyrill R. Frei <cfrei89@gmail.com>
// Date:    15.10.2013 01:07:01 CEST
// File:    empty template.cpp

/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ or COPYING for more details. */

#include <Arduino.h>
#include <ustd.hpp>
#include <tool.hpp>

class time
{
private:
	uint8_t hour; 	// 0-24
	uint8_t min;	// 0-60
	uint8_t sec;	// 0-60
	
public:
	time(){
		hour = 0;
		min = 0;
		sec = 0;
		}
			
	void set(uint8_t h, uint8_t m, uint8_t s){
			hour = h;
			min = m;
			sec = s;
		}
	
	void update(){
		++sec;
		if (sec == 60){
			sec = 0;
			++min;
			if (min == 60){
				min =0;
				++hour;
				if (hour%12 == 0){
					hour = 0;
					}
				}
			}
		}
	uint8_t get_hour(){return hour;}
	uint8_t get_min(){return min;}
	uint8_t get_sec(){return sec;}
	
};

