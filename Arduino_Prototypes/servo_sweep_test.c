#define F_CPU 16000000UL  // 16 MHz clock speed
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void timer1_init() {
    DDRB |= (1 << PB1);  // Set PB1 (OC1A) as output

    // Fast PWM mode 14 (ICR1 top)
    TCCR1A = (1 << COM1A1) | (1 << WGM11);
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler 8

    ICR1 = 40000; // 20ms period (50Hz)
    OCR1A = 3000; // Start in the middle (1.5ms pulse)
}

// Blink LED (PB5) to indicate testing
void led_on() { PORTB |= (1 << PORTB5); }
void led_off() { PORTB &= ~(1 << PORTB5); }

int main() {
    timer1_init();
    DDRB |= (1 << DDB5); // LED output

    _delay_ms(3000); // Startup delay

        while (1) {
        for (int i = 1000; i <= 4000; i += 200) {  // Adjusted max value
            led_on();
            OCR1A = i;
            _delay_ms(2000);
            led_off();
            _delay_ms(1000);
        }
    }
    return 0;
}
