# MAC Address Manufacturer Lookup

A C program to identify the manufacturer of a device based on its MAC address using Wireshark's OUI database. This program parses the manufacturer data from the Wireshark manuf file , available at https://www.wireshark.org/download/automated/data/manuf, and allows users to lookup the manufacturer by entering a MAC address. It supports 24, 28, and 36-bit MAC address prefixes.

## Features
- Parses manufacturer data from Wireshark's manuf file.
- Supports 24, 28, and 36-bit MAC address prefixes.
- Provides a simple command-line interface to lookup manufacturers by MAC address.
- find_manufacturer() function can be integrated to existing C source code without much efforts to lookup the manufacturer offline.

## Usage

1. **Clone the repository:**
   ```sh
   git clone https://github.com/yourusername/wireshark-mac-lookup.git
   cd wireshark-mac-lookup
2. **Download the manuf file:**
   Download the manuf file from https://www.wireshark.org/download/automated/data/manuf and save it as manuf.txt in the repository directory.

3. **Compile the program:**
   ```sh
   gcc -o find_manuf find_manufacturer.c

4. **Run:**
   ```sh
   $ ./find_manuf
   Enter MAC address: FC:FB:FB
   Manufacturer:       	Cisco Systems, Inc


*TODO*
   Provide a way to search the manufacturer from a complete mac address instead of from OUI part of it.
