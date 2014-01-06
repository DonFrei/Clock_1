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
#include <clock.hpp>


class program {
public:
    program(): watch() {
        setup();
    }

    void setup(){
		Serial.begin(460800);
		
		//watch.set_frequency();
		//watch.create_frame();
		//watch.set_clock_face(1,20,1);

		//row_counter = 0;
		
		//hall_sonde = watch.hall_update();
		
		//timer = millis();
		
		//freq_timer_now = 0;
		//freq_timer_last = 0;

    }
    

    void loop() {
		watch.set_one_led();
		//// ## print array spalte i
		//watch.print_row(row_counter);
		
		//// ## ++i
		//++row_counter;
		//if (row_counter == 360){
			//row_counter = 0;
			//}
			
		//// ## delay depending on frequency
		//delay((1000*1000/(watch.get_freq()*360)));		//1000*to compensate increased accuracy 1000* because dealy in millis

		//// ## hall als button vergleichen mit letzter abfrage if change => flanke, reset millis
		//if (hall_sonde == 1 && watch.hall_update() == 0 && (freq_timer_last-micros())>1000){
			//Serial.println("flanke");
			//row_counter = 0;
			//freq_timer_last = freq_timer_now;
			//freq_timer_now = micros();
////			watch.alter_freq(1000000000lu/(freq_timer_now-freq_timer_last),20);
			//}
			//hall_sonde = watch.hall_update();

		//// update time if necessary
		//if ((millis()-timer) > 1000){
			//watch.update_clock_face();
			//timer = millis();
			//}
		////	watch.test_hall();
    }
    
private:
watch_hand watch;
uint16_t row_counter;
bool hall_sonde;
uint16_t timer;
uint16_t freq_timer_last;
uint16_t freq_timer_now;
};

#include <main.hpp>
