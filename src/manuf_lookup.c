#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "manuf_lookup.h"

ManufEntry* load_manufacturer_data(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    ManufEntry* head = NULL;
    ManufEntry* current = NULL;
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        ManufEntry* entry = (ManufEntry*)malloc(sizeof(ManufEntry));
        if (entry == NULL) {
            perror("Error allocating memory");
            fclose(file);
            return NULL;
        }

        sscanf(line, "%17s %31s %[^\n]", entry->prefix, entry->short_name, entry->full_name);
        entry->next = NULL;

        if (head == NULL) {
            head = entry;
        } else {
            current->next = entry;
        }
        current = entry;
    }

    fclose(file);
    return head;
}

const char* find_manufacturer(ManufEntry* head, const char* mac_address) {
    ManufEntry* current;
    char prefix[MAC_ADDRESS_LENGTH + 1];

    // Check 36-bit OUI
    strncpy(prefix, mac_address, 13);
    prefix[13] = '\0';
    current = head;
    while (current) {
        if (strncmp(prefix, current->prefix, 13) == 0) {
            return current->full_name;
        }
        current = current->next;
    }

    // Check 28-bit OUI
    strncpy(prefix, mac_address, 10);
    prefix[10] = '\0';
    current = head;
    while (current) {
        if (strncmp(prefix, current->prefix, 10) == 0) {
            return current->full_name;
        }
        current = current->next;
    }

    // Check 24-bit OUI
    strncpy(prefix, mac_address, 8);
    prefix[8] = '\0';
    current = head;
    while (current) {
        if (strncmp(prefix, current->prefix, 8) == 0) {
            return current->full_name;
        }
        current = current->next;
    }

    return "Unknown Manufacturer";
}

void free_manufacturer_data(ManufEntry* head) {
    ManufEntry* current = head;
    while (current) {
        ManufEntry* next = current->next;
        free(current);
        current = next;
    }
}

