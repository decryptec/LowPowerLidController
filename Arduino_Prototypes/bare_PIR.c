#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define PIR_PIN     PD2  // PIR sensor pin
#define LED_PIN     PB5  // LED pin

#define STABILIZATION_TIME 30000  // Stabilization time in milliseconds

volatile unsigned long millis_counter = 0;
unsigned long startTime = 0;
bool motionState = false;        
bool previousMotionState = false; 

void init_io(void);
void init_timer(void);
void init_interrupt(void);
unsigned long get_millis(void);

int main(void) {
    init_io();      // Initialize I/O pins
    init_timer();   // Initialize timer
    init_interrupt(); // Initialize interrupts
    sei();  // Enable global interrupts

    // Stabilization period
    startTime = get_millis();
    while (get_millis() - startTime < STABILIZATION_TIME) {
        if (get_millis() % 1000 < 50) {
            // Toggle LED to indicate stabilization
            PORTB |= (1 << LED_PIN);
            _delay_ms(100);
            PORTB &= ~(1 << LED_PIN);
        }
    }

    // Main loop to check motion state
    while (1) {
        motionState = !(PIND & (1 << PIR_PIN));  // Read PIR sensor

        // Check if motion state has changed
        if (motionState != previousMotionState) {
            if (motionState) {
                PORTB |= (1 << LED_PIN);  // Turn on LED if motion detected
            } else {
                PORTB &= ~(1 << LED_PIN); // Turn off LED if no motion
            }
            previousMotionState = motionState;
        }
    }

    return 0;
}

void init_io(void) {
    DDRB |= (1 << LED_PIN);  // Set LED pin as output
    DDRD &= ~(1 << PIR_PIN); // Set PIR pin as input
    PORTD &= ~(1 << PIR_PIN);  // Enable pull-down resistor on PIR pin
}

void init_timer(void) {
    TCCR0A = 0;  // Normal mode
    TCCR0B = (1 << CS00) | (1 << CS02);  // Set prescaler to 1024
    TIMSK0 = (1 << TOIE0);  // Enable Timer0 overflow interrupt
}

void init_interrupt(void) {
    EICRA |= (1 << ISC01);  // Trigger interrupt on falling edge (motion detection)
    EICRA &= ~(1 << ISC00);
    EIMSK |= (1 << INT0);   // Enable INT0 interrupt
}

unsigned long get_millis(void) {
    return millis_counter;  // Return milliseconds count
}

// Timer0 overflow interrupt (increments millis_counter)
ISR(TIMER0_OVF_vect) {
    millis_counter++;
}

// External interrupt (for PIR sensor) - Not used directly in this code
ISR(INT0_vect) {
}

