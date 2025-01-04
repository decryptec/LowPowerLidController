# ATmega328P Pin Descriptions (Arduino Uno)

## Important Pins

### INT0: External Interrupt Pin
- **Physical Pin**: 32  
- **Signal**: PD2 (INT0/PCINT18)  
- **Usage**: Designed for wake-up functionality using a PIR sensor.

### Any GPIO Pin (For Servo Control)
- **Physical Pin**: 12  
- **Signal**: PB0 (PCINT0/CLKO/ICP1)  

---

## External Interrupts

### EICRA - External Interrupt Control Register A
- **Bits**:
  - **ISC01, ISC00**: INT0 Control Sense Configuration  
    - Configure these bits to set the sense control for the external interrupt.  

### EIMSK - External Interrupt Mask Register
- **Bit 0**: INT0  
  - Enables the external interrupt request for INT0.

### EIFR - External Interrupt Flag Register
- **Bit 0**: INTF0  
  - Represents the external interrupt flag for INT0.

---

## I/O Ports

### DDxn: Data Direction Register
- **Configuration**:
  - `DDxn = 1`: Configure `Pxn` as an output pin.  
  - `DDxn = 0`: Configure `Pxn` as an input pin.  

### PORTxn: Port Data Register
- **Behavior**:
  - If `PORTxn = 1` (and the pin is configured as input), it activates the internal pull-up resistor.

---

## Visual References

### Sense Control for INT0
![Sense Control for INT0](https://github.com/user-attachments/assets/a960f928-9220-42b3-8a85-ca59f6facc8f)

### I/O Ports Behavior
![I/O Ports Behavior](https://github.com/user-attachments/assets/89d427ef-84db-4b55-b035-7b43999a452d)
