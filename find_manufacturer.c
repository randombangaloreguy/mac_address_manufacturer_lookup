#include <stdio.h>                                                                                                                                                                                          
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_ENTRIES 100000
#define MAC_ADDRESS_LENGTH 18

typedef struct {
    char prefix[MAC_ADDRESS_LENGTH];
    char short_name[50];
    char full_name[128];
    int prefix_length;
} ManufEntry;

ManufEntry manuf_entries[MAX_ENTRIES];
int entry_count = 0;

void load_manuf_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Could not open manufacturer file");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '#' || strlen(line) < 5) {
            continue; // Skip comments and invalid lines
        }

        ManufEntry entry;
        char *token = strtok(line, " \t");
        if (token == NULL) continue;
        char *slash_pos = strchr(token, '/');
        if (slash_pos != NULL) {
            entry.prefix_length = atoi(slash_pos + 1);
            *slash_pos = '\0';
        } else {
            entry.prefix_length = 24;
        }
        strncpy(entry.prefix, token, sizeof(entry.prefix) - 1);
        entry.prefix[sizeof(entry.prefix) - 1] = '\0'; // Ensure null termination

        token = strtok(NULL, " \t");
        if (token == NULL) continue;
        strncpy(entry.short_name, token, sizeof(entry.short_name) - 1);
        entry.short_name[sizeof(entry.short_name) - 1] = '\0'; // Ensure null termination

        token = strtok(NULL, "\n");
        if (token == NULL) continue;
        strncpy(entry.full_name, token, sizeof(entry.full_name) - 1);
        entry.full_name[sizeof(entry.full_name) - 1] = '\0'; // Ensure null termination

        manuf_entries[entry_count++] = entry;
        if (entry_count >= MAX_ENTRIES) {
            break;
        }
    }

    fclose(file);
}

const char* find_manufacturer(const char *mac_address) {
    for (int i = 0; i < entry_count; i++) {
        int bytes_to_compare = manuf_entries[i].prefix_length / 8;
        int bits_to_compare = manuf_entries[i].prefix_length % 8;

        if (strncmp(mac_address, manuf_entries[i].prefix, bytes_to_compare * 3) == 0) {
            if (bits_to_compare > 0) {
                unsigned char mac_byte = strtol(mac_address + bytes_to_compare * 3, NULL, 16);
                unsigned char prefix_byte = strtol(manuf_entries[i].prefix + bytes_to_compare * 3, NULL, 16);
                unsigned char mask = 0xFF << (8 - bits_to_compare);

                if ((mac_byte & mask) == (prefix_byte & mask)) {
                    return manuf_entries[i].full_name;
                }
            } else {
                return manuf_entries[i].full_name;
            }
        }
    }
    return "Unknown Manufacturer";
}

int main() {
    const char *filename = "manuf.txt";
    load_manuf_file(filename);

    char mac_address[MAC_ADDRESS_LENGTH];
    printf("Enter MAC address: ");
    if (scanf("%17s", mac_address) != 1) {
        fprintf(stderr, "Error reading MAC address\n");
        exit(EXIT_FAILURE);
    }

    const char *manufacturer = find_manufacturer(mac_address);
    printf("Manufacturer: %s\n", manufacturer);

    return 0;
}
