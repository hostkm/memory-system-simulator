#include <stdio.h>
#include <stdint.h>

// Memory Setup
#define VIRTUAL_ADDRESS_SPACE 65536  // 2^16 = 64 KB virtual memory
#define PAGE_SIZE 256                // 256 bytes per page
#define NUM_PAGES 256                // Virtual pages
#define FRAME_SIZE 256               // Each frame = 256 bytes
#define NUM_FRAMES 16                // 4 KB main memory / 256 = 16 frames
#define TLB_SIZE 8                   // TLB can store 8 entries
#define CACHE_SIZE 16                // Cache can store 16 blocks

// Data Structures
int page_table[NUM_PAGES];          // Page table
int tlb_page[TLB_SIZE];             // TLB: stores page numbers
int tlb_frame[TLB_SIZE];            // TLB: stores corresponding frame numbers
int tlb_index = 0;                  // FIFO replacement pointer for TLB
int cache_block[CACHE_SIZE];        // Cache blocks
int cache_index = 0;                // FIFO replacement pointer for cache

// Statistics
int tlb_hits = 0, tlb_misses = 0;
int cache_hits = 0, cache_misses = 0;
int page_faults = 0;

// Initialization
void init_page_table() {
    for (int i = 0; i < NUM_PAGES; i++) {
        if (i < NUM_FRAMES) {
            page_table[i] = i;   // Page i is initially mapped to frame i
        } else {
            page_table[i] = -1;  // Not loaded into memory
        }
    }
}

void init_tlb() {
    for (int i = 0; i < TLB_SIZE; i++) {
        tlb_page[i] = -1;
        tlb_frame[i] = -1;
    }
}

void init_cache() {
    for (int i = 0; i < CACHE_SIZE; i++) {
        cache_block[i] = -1;
    }
}

        // TLB Functions
int search_tlb(int page_number) {
    for (int i = 0; i < TLB_SIZE; i++) {
        if (tlb_page[i] == page_number) {
            tlb_hits++;
            return tlb_frame[i];        // TLB Hit
        }
    }
    tlb_misses++;
    return -1;      // TLB Miss
}

void add_to_tlb(int page_number, int frame_number) {
    tlb_page[tlb_index] = page_number;
    tlb_frame[tlb_index] = frame_number;
    tlb_index = (tlb_index + 1) % TLB_SIZE;     // FIFO replacement
}

// Cache Functions
int search_cache(int block_number) {
    for (int i = 0; i < CACHE_SIZE; i++) {
        if (cache_block[i] == block_number) {
            cache_hits++;
            return 1;   // Cache Hit
        }
    }
    cache_misses++;
    return 0;       // Cache Miss
}

void add_to_cache(int block_number) {
    cache_block[cache_index] = block_number;
    cache_index = (cache_index + 1) % CACHE_SIZE; // FIFO replacement
}

// Page Fault Handler
int handle_page_fault(int page_number) {
    page_faults++;
    int frame_number = page_number % NUM_FRAMES;  // Simple replacement
    page_table[page_number] = frame_number;       // Load page into memory
    return frame_number;
}

// Address Translation
int translate_address(uint16_t virtual_address) {
    int page_number = (virtual_address >> 8) & 0xFF;  // Higher 8 bits
    int offset = virtual_address & 0xFF;              // Lower 8 bits

            // Step 1 for TLB Lookup
    int frame_number = search_tlb(page_number);
    if (frame_number != -1) {
        printf("TLB Hit. ");
    } else {
        printf("TLB Miss. ");
            // Step 2 for Page Table Lookup
        frame_number = page_table[page_number];
        if (frame_number == -1) {
            printf("Page Fault. ");
            frame_number = handle_page_fault(page_number);
        }
        add_to_tlb(page_number, frame_number);
    }

        // Step 3 for Cache Lookup
    int block_number = frame_number;  // 1 frame = 1 block
    if (search_cache(block_number)) {
        printf("Cache Hit. ");
    } else {
        printf("Cache Miss. ");
        add_to_cache(block_number);
    }

        // Step 4 for Physical Address
    int physical_address = (frame_number << 8) | offset;
    return physical_address;
}

        // Main Part
int main() {
    init_page_table();
    init_tlb();
    init_cache();

    while (1) {
        printf("\nEnter a virtual address (0 - 65535, -1 to exit): ");  // Getting input
        int input_address;
        scanf("%d", &input_address);

        if (input_address == -1) break;                             // exit
        if (input_address < 0 || input_address > 65535) {
            printf("Error: Enter address between 0 - 65535 only.\n");
            continue;                                               // skip invalid input
        }

        uint16_t virtual_address = (uint16_t)input_address;         // safe to cast
        int physical_address = translate_address(virtual_address);

        printf("\nVirtual Address: %u", virtual_address);
        printf("\nPage Number: %d, Offset: %d", virtual_address >> 8, virtual_address & 0xFF);
        printf("\nPhysical Address: %d\n", physical_address);
    }

    // Print statistics
    printf("\n--- Simulation Stats ---\n");
    printf("TLB Hits: %d, TLB Misses: %d\n", tlb_hits, tlb_misses);
    printf("Cache Hits: %d, Cache Misses: %d\n", cache_hits, cache_misses);
    printf("Page Faults: %d\n", page_faults);

    return 0;
}
