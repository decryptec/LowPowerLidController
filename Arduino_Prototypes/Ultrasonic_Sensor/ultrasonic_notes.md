# Ultrasonic Sensor Notes

Initially, an **ultrasonic sensor** was used for proximity detection. While a **low-power sleep mode** could be implemented for a set duration, it would decrease power consumption and increase battery life, but at the cost of making the system inactive during that time, preventing the lid from opening when a user approached.

To address this, the design was switched to a **PIR sensor**, which only activates on motion. This allows the microcontroller to sleep and wake using interrupts, significantly reducing power consumption while ensuring the lid opens when needed.
