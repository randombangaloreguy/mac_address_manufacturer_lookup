#include <stdio.h>
#include <string.h>
#include "manuf_lookup.h"

int main() {
    const char* filename = "data/manuf.txt";
    ManufEntry* head = load_manufacturer_data(filename);

    if (head == NULL) {
        return 1;
    }

    char mac_address[MAC_ADDRESS_LENGTH + 1];
    printf("Enter MAC address: ");
    scanf("%17s", mac_address);

    const char* manufacturer = find_manufacturer(head, mac_address);
    printf("Manufacturer: %s\n", manufacturer);

    free_manufacturer_data(head);
    return 0;
}

