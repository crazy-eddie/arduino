#include <Arduino.h>


unsigned long time_counter = 0;
unsigned long blink_counter = 0;
int prev_state = LOW;

enum States { Cooling, Ready, Level0, Level1, Overloading, Overloaded };

int current_state = Ready;

int pin3_state = HIGH;
int pin4_state = LOW;
int pin5_state = LOW;

void setup() {

    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    
    pinMode(2, INPUT);

    Serial.begin(9600);

}


void loop() {

    int switch_state = digitalRead(2);
    
    if (switch_state == LOW)
    {
        digitalWrite(4, LOW); pin4_state = LOW;
        digitalWrite(5, LOW); pin5_state = LOW;

        if (current_state == Overloaded)
        {
            current_state = Cooling;
            time_counter = millis();
        }
        else if (current_state == Cooling)
        {
            if (millis() - time_counter > 10000)
                current_state = Ready;
        }
        else
        {
            current_state = Ready;
        }

        if (current_state == Cooling)
        {
            if (millis() - blink_counter > 500)
            {
                pin3_state = pin3_state == HIGH ? LOW:HIGH;
                digitalWrite(3, pin3_state);
                blink_counter = millis();
            }
        }
        else
        {
            digitalWrite(3, HIGH); pin3_state = HIGH;
        }

    }
    else // HIGH
    {
        if (current_state == Cooling)
        {
            time_counter = millis();

            if (millis() - blink_counter > 500)
            {
                pin3_state = pin3_state == HIGH ? LOW:HIGH;
                digitalWrite(3, pin3_state);
                blink_counter = millis();
            }
        }
        else
        {
            if (current_state != Overloaded)
            {
                if (millis() - time_counter > 10000)
                {
                    ++current_state;
                    time_counter = millis();
                }

                if (current_state == Overloaded)
                    blink_counter = millis();
            }
            if (current_state == Ready)
            {
                time_counter = millis();
                current_state = Level0;
            }
        }

        if (current_state == Overloaded)
        {
            digitalWrite(3, LOW); pin3_state = LOW;
            digitalWrite(4, LOW); pin4_state = LOW;
            digitalWrite(5, LOW); pin5_state = LOW;
        }
        else if (current_state == Overloading)
        {
            if (millis() - blink_counter > 500)
            {
                pin5_state = pin4_state = pin3_state = pin3_state == HIGH ? LOW:HIGH;
                digitalWrite(3, pin3_state);
                digitalWrite(4, pin4_state);
                digitalWrite(5, pin5_state);
                blink_counter = millis();
            }
        }
        else if (current_state >= Level0)
        {
            digitalWrite(4, HIGH); pin4_state = HIGH;
        }
        if (current_state == Level1)
        {
            digitalWrite(5, HIGH); pin5_state = HIGH;
        }
    }
}
