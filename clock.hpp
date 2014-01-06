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
#include <led_clock.hpp>
#include <util/sleep.hpp>
#include <time.hpp>
#include <math.h>

class watch_hand
{
private:
	uint8_t tilt_short_;
	uint8_t tilt_long_;
	uint8_t hall_;
	uint32_t freq_;
	
	led leds;
	
	ustd::array<uint16_t,360> clock_face;
	time time_now;
	

public:
	watch_hand(): tilt_short_(3), tilt_long_(A0), hall_(2), leds()
		{
		pinMode(tilt_short_, INPUT);
		pinMode(tilt_long_, INPUT);
		pinMode(hall_, INPUT_PULLUP);
		freq_ = 1;
		Serial.println(micros());
		for (uint16_t i = 0; i<360; ++i){
			clock_face[i] = 65535; //  turn off all led
			}
		Serial.println(micros());
		turn_all_off();
		};
		
	void turn_all_on(){
		for (uint8_t i=0;i<11;++i){
			leds.set_led(i,LOW);}
		}
		
	void turn_all_off(){
		for (uint8_t i=0;i<11;++i){
			leds.set_led(i, HIGH);}
		}

	void band() {
		leds.set_led(0, LOW);
		delay(100);
		leds.set_led(1, LOW);
		delay(100);
		leds.set_led(2, LOW);
		leds.set_led(0, HIGH);
		delay(100);
		leds.set_led(3, LOW);
		leds.set_led(1, HIGH);
		delay(100);
		leds.set_led(4, LOW);
		leds.set_led(2, HIGH);
		delay(100);
		leds.set_led(5, LOW);
		leds.set_led(3, HIGH);
		delay(100);
		leds.set_led(6, LOW);
		leds.set_led(4, HIGH);
		delay(100);
		leds.set_led(7, LOW);
		leds.set_led(5, HIGH);
		delay(100);
		leds.set_led(8, LOW);
		leds.set_led(6, HIGH);
		delay(100);
		leds.set_led(9, LOW);
		leds.set_led(7, HIGH);
		delay(100);
		leds.set_led(10, LOW);
		leds.set_led(8, HIGH);
		delay(100);
		leds.set_led(9, HIGH);
		delay(100);
		leds.set_led(10, HIGH);
		}
	
	void blink_all(){
		turn_all_off();
		delay(200);
		turn_all_on();
		delay(200);
		turn_all_off();
		}

	void demo(){
		band();
		blink_all();
		blink_all();
		}
	
	void set_one_led(){
		leds.set_led(1,LOW);
		leds.set_led(2,LOW);
		leds.set_led(3,LOW);
		delay(100);
		leds.set_led(3,HIGH);
		leds.set_led(1,HIGH);
		leds.set_led(2,HIGH);
		leds.set_led(7,LOW);
		leds.set_led(8,LOW);
		leds.set_led(9,LOW);
		delay(100);
		leds.set_led(7,HIGH);
		leds.set_led(8,HIGH);
		leds.set_led(9,HIGH);
//		delay(100);
	
		//leds.set_led(2,LOW);
		//leds.set_led(3,LOW);
		//leds.set_led(4,LOW);
	//	leds.set_led(5,LOW);
	//	leds.set_led(6,LOW);
	//	leds.set_led(7,LOW);
	//	leds.set_led(8,LOW);
		}
	
	uint8_t hall_update(){
		hall_ = digitalRead(2);
		return hall_;
		}
		
	uint8_t tilt_long_update(){
		tilt_long_ = digitalRead(A0);
		return tilt_long_;
		}
		
	uint8_t tilt_short_update(){
		tilt_short_ = digitalRead(3);
		return tilt_short_;
		}
	
	void test_hall(){
		hall_update();
		if (hall_ == HIGH) {leds.set_led(9, LOW);} // kein feld
		if (hall_ == LOW) {leds.set_led(1, LOW);}	// feld
		turn_all_off();		
		Serial.println(hall_);
		}
	
	void set_frequency(){
		freq_ = 30000;
		uint8_t hall_last;
		uint32_t time_freq = 1;
		uint8_t freq_amount = 50;
		do
		{
			hall_last = hall_update();
			delay(5);
			} while (hall_last == hall_update() || hall_last == 0);
		uint32_t start_time = micros();
		uint32_t timer_freq_last = start_time;
		
		for (uint8_t i = 0; i<freq_amount; ++i){
			do
			{
				
				hall_last = hall_update();
				delay(5);
				} while (hall_last == hall_update() || hall_last == 0);
			if (i>2){
				time_freq = (micros()-timer_freq_last);
				timer_freq_last = micros();
				alter_freq(1000* (1000000*i)/(time_freq), i); // 1000* for accuracy
				Serial.println(1000* (1000000*i)/(time_freq));
				}
			}
		}
		
	// factor: 100 equals 1 to 1, 1 equals 1.99 to 0.01
	void alter_freq(uint32_t new_freq, uint8_t factor){
		freq_ = (((1-factor/100.0)*freq_+(factor/100.0)*new_freq));
		}
	
	// returns frequency
	uint8_t get_freq(){ return freq_;}
	
	
	void check_time_out(){
		tilt_long_update();
		tilt_short_update();
		
		if (tilt_long_ != tilt_short_){
			delay(10);
			tilt_long_update();
			tilt_short_update();
			
			if (tilt_long_ != tilt_short_){
				util::sleep(3, CHANGE);
				}
			}
		}
	
	// row nbr i will be printed	
	void print_row(uint16_t row){ 
		for (uint8_t i = 0; i<11; ++i){
			leds.set_led(i, (clock_face[row]&(1<<i))>>i);
			}
		}

	// creates outer part of clockface
	void create_frame(){
		// outer ring, always on
		for (uint16_t i=0;i<360;++i){
			set_bit(i,10,LOW);
			}
		// ring nr 9, index
		for (uint8_t i=0;i<4;++i){
			set_bit(0+i*90,9,LOW);
			set_bit(1+i*90,9,LOW);
			set_bit(2+i*90,9,LOW);
			set_bit(3+i*90,9,LOW);
			for (uint8_t j=4;j<30;++j){
				set_bit(j+i*90,9,HIGH);
				}
			set_bit(30+i*90,9,LOW);
			set_bit(31+i*90,9,LOW);
			set_bit(32+i*90,9,LOW);
			set_bit(33+i*90,9,LOW);
			for (uint8_t j=34;j<60;++j){
				set_bit(j+i*90,9,HIGH);
				}
			set_bit(60+i*90,9,LOW);
			set_bit(61+i*90,9,LOW);
			set_bit(62+i*90,9,LOW);
			set_bit(63+i*90,9,LOW);
			for (uint8_t j=64;j<90;++j){
				set_bit(j+i*90,9,HIGH);
				}	
			}
		}

	// create clock_face from scratch
	void set_clock_face(uint8_t hour, uint8_t min, uint8_t sec){
		time_now.set(hour, min, sec);
		
		for (uint16_t j=0; j<360; ++j){
			if ((clock_face[j]&(1<<0)>>0) == LOW){
				for (int i=0;i<9;++i){
					set_bit(j,i,HIGH);
					}
				}
			}
		
		//hour
		for (uint8_t i = 0; i<4; ++i){
//			set_bit(((hour%12)*30)-1*30,i,HIGH);
			set_bit((hour%12)*30,i,LOW);
			}
		//min
		for (uint8_t i = 0; i<6; ++i){
//			set_bit((min*6-1*6),i,HIGH);
			set_bit(min*6,i,LOW);
			}
		//sec
		for (uint8_t i = 0; i<8; ++i){
//			set_bit(sec*6-1*6,i,HIGH);
			set_bit(sec*6,i,LOW);
			}
		}

	// change one particular bit on the clockface
	void set_bit(uint16_t coulumn, uint8_t row, bool to_set){
		uint16_t place = pow(2,row);
		if (((clock_face[coulumn]&(1<<row))>>row) == to_set){
			}
		else if (((clock_face[coulumn]&(1<<row))>>row) == 0 && to_set==1){
			clock_face[coulumn] += place;
			}
		else if (((clock_face[coulumn]&(1<<row))>>row) == 1 && to_set==0){
			clock_face[coulumn] -= place;
			}
		}
	
	void print_clock_face(){
		for (uint16_t i=0;i<360; ++i){
			for (int j=0;j<11;++j){
				Serial.print((clock_face[i]&(1<<j))>>j);
				}
			Serial.println("");
			}
		}
		
	// clock_face plus 1 sec
	void update_clock_face(){
		time_now.update();
		set_clock_face(time_now.get_hour(), time_now.get_min(), time_now.get_sec());
		}
	};
