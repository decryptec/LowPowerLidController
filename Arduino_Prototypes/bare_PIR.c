#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define PIR_PIN     PD2
#define LED_PIN     PB5

#define STABILIZATION_TIME 30000  

volatile unsigned long millis_counter = 0;
unsigned long startTime = 0;
bool motionState = false;        
bool previousMotionState = false; 

void init_io(void);
void init_timer(void);
void init_interrupt(void);
unsigned long get_millis(void);

int main(void) {
    init_io();
    init_timer();
    init_interrupt();
    sei();  

    startTime = get_millis();
    while (get_millis() - startTime < STABILIZATION_TIME) {
        if (get_millis() % 1000 < 50) {
            PORTB |= (1 << LED_PIN);
            _delay_ms(100);
            PORTB &= ~(1 << LED_PIN);
        }
    }

    while (1) {
        motionState = !(PIND & (1 << PIR_PIN));  

        if (motionState != previousMotionState) {
            if (motionState) {
                PORTB |= (1 << LED_PIN);
            } else {
                PORTB &= ~(1 << LED_PIN);
            }
            previousMotionState = motionState;
        }
    }

    return 0;
}

void init_io(void) {
    DDRB |= (1 << LED_PIN);
    DDRD &= ~(1 << PIR_PIN);   
    PORTD |= (1 << PIR_PIN);   
}

void init_timer(void) {
    TCCR0A = 0;
    TCCR0B = (1 << CS00) | (1 << CS02);  
    TIMSK0 = (1 << TOIE0);     
}

void init_interrupt(void) {
    EICRA |= (1 << ISC01);     
    EICRA &= ~(1 << ISC00);    
    EIMSK |= (1 << INT0);      
}

unsigned long get_millis(void) {
    return millis_counter;
}

ISR(TIMER0_OVF_vect) {
    millis_counter++;
}

ISR(INT0_vect) {
}
