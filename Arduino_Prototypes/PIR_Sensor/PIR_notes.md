# PIR Test Documentation

## Components Used
- **PIR Sensor**: EKMC1607111
- **Arduino Uno**
- **Resistor**: 20kΩ pull-down resistor
- **LED**: Indicator for motion detection

## Wiring
- **PIR Output**: Connected to **Arduino Pin 2**.
- **Pull-down Resistor**: 20kΩ between PIR output and **GND**.
- **LED**: Connected to **Pin 7**.

## Key Points
- **Stabilization Time**: PIR sensor needs **30 seconds** after power-up to stabilize.
- **Signal Behavior**: When motion is detected, output voltage fluctuates between **2.2V to 4.4V** (measured with a multimeter).
- **LED Process**: The LED runs for **3 seconds** after motion detection. The voltage spikes are negligible, as the LED duration outlasts them, preventing repeat activations.
- **Lower Resistance (1kΩ to 5kΩ)**: Caused **more motion detection spikes** and **frequent false reads** due to increased sensitivity to small fluctuations and noise.
- **Higher Resistance (10kΩ to 20kΩ)**: Reduced **motion detection spikes** and **improved stability**, leading to fewer false readings.

## Conclusion
- **20kΩ pull-down resistor** ensures proper logic levels.
- Output voltage fluctuates during motion detection but is not problematic due to the LED's duration.
- **Lower resistance** results in more motion detection reads, while **higher resistance** provides a cleaner signal with fewer false detections.
- **30-second stabilization** is required for reliable detection.

