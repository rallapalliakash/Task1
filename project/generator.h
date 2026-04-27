/*
 * generator.h
 *
 *  Created for: GlobalLogic
 *       Author: serhii.denysov
 *
 * Generator class header.
 *
 * You have to change this file to fix build errors, and make
 * the unit tests passed.
 *
 */

#ifndef GENERATOR_H
#define GENERATOR_H

// #include <stdexcept>
// #include <limits>

/*
 * NOTE: #pragma pack is intentionally removed.
 *
 * The sizeof test compares Generator against:
 *   typedef struct { int* b; int s; } generator_t;
 *
 * On 64-bit platforms (no pack):
 *   int* b  = 8 bytes
 *   int  s  = 4 bytes
 *   padding = 4 bytes  (compiler aligns struct to pointer size)
 *   total   = 16 bytes
 *
 * Generator must also be 16 bytes with the same natural alignment.
 * Using #pragma pack(1) forces 12 bytes which breaks the sizeof test.
 * Removing pack lets both structs use the same natural alignment = 16 bytes.
 */
class Generator
{
private:
    // deep-copy
    void copy(const Generator &other);

public:
    // Default constructor— initializes to empty/null state
    Generator() : data(nullptr), count(0) {}

    // Destructor 
    ~Generator();

    // Copy constructor 
    Generator(const Generator &other);

    // Assignment operator
    Generator& operator=(const Generator &other);

    // Returns read-only pointer to internal array
    const int* get_data() const;

    // Returns number of elements stored
    int get_count() const;

    
    // input validation - Throws logic_error if src is null, n is 0, or n >= UINT_MAX
    void set(int* src, int n);

    // Generates n values that all pass check(), strictly increasing, unique.
    void generate(int n);

private:
    int* data;   
    int  count;  
};
#endif // GENERATOR_H

