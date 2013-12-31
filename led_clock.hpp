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


class led
{
private:
	uint8_t const led0_;
	uint8_t const led1_;
	uint8_t const led2_;
	uint8_t const led3_;
	uint8_t const led4_;
	uint8_t const led5_;
	uint8_t const led6_;
	uint8_t const led7_;
	uint8_t const led8_;
	uint8_t const led9_;
	uint8_t const led10_;
	ustd::array<uint8_t,11> led_array;
	

public:	
	led(): led0_(5), led1_(13), led2_(12), led3_(6), led4_(11), led5_(9), led6_(10), led7_(7), led8_(8), led9_(4), led10_(A1)
	{
		pinMode(led0_, OUTPUT);
		pinMode(led1_, OUTPUT);
		pinMode(led2_, OUTPUT);
		pinMode(led3_, OUTPUT);
		pinMode(led4_, OUTPUT);
		pinMode(led5_, OUTPUT);
		pinMode(led6_, OUTPUT);
		pinMode(led7_, OUTPUT);
		pinMode(led8_, OUTPUT);
		pinMode(led9_, OUTPUT);
		pinMode(led10_, OUTPUT);
		
		led_array[0]=led0_;
		led_array[1]=led1_;
		led_array[2]=led2_;
		led_array[3]=led3_;
		led_array[4]=led4_;
		led_array[5]=led5_;
		led_array[6]=led6_;
		led_array[7]=led7_;
		led_array[8]=led8_;
		led_array[9]=led9_;
		led_array[10]=led10_;
		}
		
void set_led(uint8_t led_nbr, bool hl){
	digitalWrite(led_array[led_nbr],hl);
	}
};
