#ifndef MANUF_LOOKUP_H
#define MANUF_LOOKUP_H

#define MAX_LINE_LENGTH 256
#define MAC_ADDRESS_LENGTH 17

typedef struct ManufEntry {
    char prefix[MAC_ADDRESS_LENGTH + 1];
    char short_name[32];
    char full_name[128];
    struct ManufEntry* next;
} ManufEntry;

ManufEntry* load_manufacturer_data(const char* filename);
const char* find_manufacturer(ManufEntry* head, const char* mac_address);
void free_manufacturer_data(ManufEntry* head);

#endif

