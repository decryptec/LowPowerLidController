# Low Power Trash Lid

Development of a low-power, autonomous trashcan lid controller. Arduino Uno Rev 3 for rapid prototyping and refined using an ATtiny84 microcontroller, custom PCB, and a lithium-ion battery for long-term operation.

## Features

### Prototyping Phase:

- Arduino Uno Rev 3 for initial design and functionality testing.
- Modular, easy-to-understand code for rapid iteration.

### Final Implementation:

- ATtiny84 microcontroller for compact, optimized performance.
- Custom PCB design tailored for low-power operation.
- Integrated lithium-ion battery for extended autonomy.

## Development Environment

This project uses a Nix environment for managing dependencies and a Makefile for compiling and flashing firmware to the MCU.

### Setting Up the Development Environment

Ensure you have [Nix package manager](https://nixos.org/download.html) installed. Then, set up the environment using the provided `shell.nix` file.

Activate the shell:

```sh
nix-shell
```

### Programming the MCU

A Makefile is used to compile and upload the firmware to the MCU. Use the following commands:

1. Enter the Nix shell:
   ```sh
   nix-shell
   ```
2. Compile the firmware:
   ```sh
   make
   ```
3. Upload to the MCU:
   ```sh
   make upload
   ```
4. Clean build files:
   ```sh
   make clean
   ```

Ensure the correct `PORT` is set in the Makefile for your system. You can check the connected devices using:

```sh
ls /dev/tty*
```

