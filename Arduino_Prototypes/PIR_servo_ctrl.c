#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define PIR_PIN     PD2  // PIR sensor pin
#define SERVO_PIN   PB1  // Servo control pin

#define STABILIZATION_TIME 30000  // Stabilization time in milliseconds

volatile unsigned long millis_counter = 0;
unsigned long startTime = 0;
volatile bool motionTriggered = false;

void init_io(void);
void init_timer(void);
void init_interrupt(void);
void timer1_init(void);
void set_servo_angle(uint8_t angle);
unsigned long get_millis(void);

int main(void) {
    init_io();      // Initialize I/O pins
    init_timer();   // Initialize timer
    init_interrupt(); // Initialize interrupts
    timer1_init();  // Initialize Timer1 for servo control
    sei();  // Enable global interrupts

    // Stabilization period
    startTime = get_millis();
    while (get_millis() - startTime < STABILIZATION_TIME);

    while (1) {
        if (motionTriggered) {
            set_servo_angle(90);  // Open lid
            _delay_ms(2000);       // Keep the lid open for 2 seconds
            set_servo_angle(0);   // Close lid
            motionTriggered = false; // Reset trigger
        }
    }
    return 0;
}

void init_io(void) {
    DDRB |= (1 << SERVO_PIN);  // Set servo pin as output
    DDRD &= ~(1 << PIR_PIN);   // Set PIR pin as input
    PORTD &= ~(1 << PIR_PIN);  // Enable pull-down resistor on PIR pin
}

void init_timer(void) {
    TCCR0A = 0;  // Normal mode
    TCCR0B = (1 << CS00) | (1 << CS02);  // Set prescaler to 1024
    TIMSK0 = (1 << TOIE0);  // Enable Timer0 overflow interrupt
}

void init_interrupt(void) {
    EICRA |= (1 << ISC01) | (1 << ISC00);  // Trigger interrupt on rising edge (motion detected)
    EIMSK |= (1 << INT0);   // Enable INT0 interrupt
}

void timer1_init(void) {
    TCCR1A = (1 << COM1A1) | (1 << WGM11);  // Fast PWM mode 14
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler 8
    ICR1 = 40000; // 20ms period (50Hz)
    OCR1A = 1000;  // Start at 0° (0.5ms pulse)
}

void set_servo_angle(uint8_t angle) {
    if (angle > 90) angle = 90;  // Restrict to max 90°
    OCR1A = 1000 + ((uint32_t)angle * 2000) / 90;
}

unsigned long get_millis(void) {
    return millis_counter;  // Return milliseconds count
}

ISR(TIMER0_OVF_vect) {
    millis_counter++;
}

ISR(INT0_vect) {
    motionTriggered = true; // Set flag to process in main loop
}
