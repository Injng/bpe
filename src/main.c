#define STB_DS_IMPLEMENTATION

#include "../lib/stb_ds.h"
#include <stdio.h>
#include <string.h>

/**
 * struct pair - Defines a pair of characters representing a single unit in byte pair encoding.
 * @first: The first in the pair of characters.
 * @second: The second in the pair of characters.
 *
 * The pair structure is used to encode information about a pair of characters used in byte pair encoding.
 * It is created to be used as the key in a key-value pair for a hash map implementation.
 */
struct pair {
    char first;
    char second;
};

/**
 * struct freq - Defines a key-value pair with the key as a pair of characters and the value as the frequency of that pair.
 * @key: The pair of characters as the key.
 * @value: The frequency as the value.
 *
 * The freq structure is used to encode information about the frequency a pair of characters appear in a set of text.
 * The pair of characters is the key used to access the key-value pair, and the frequency is the value.
 * This structure is meant to be used as a key-value pair in the stb hash map implementation.
 */
struct freq {
    struct pair key;
    int value;
};

int main(void) {
    // Robert Frost, The Road Not Taken
    char *text = "Two roads diverged in a yellow wood, \
    And sorry I could not travel both \
    And be one traveler, long I stood \
    And looked down one as far as I could \
    To where it bent in the undergrowth; \
    Then took the other, as just as fair, \
    And having perhaps the better claim, \
    Because it was grassy and wanted wear; \
    Though as for that the passing there \
    Had worn them really about the same, \
    And both that morning equally lay \
    In leaves no step had trodden black. \
    Oh, I kept the first for another day! \
    Yet knowing how way leads on to way, \
    I doubted if I should ever come back. \
    I shall be telling this with a sigh \
    Somewhere ages and ages hence: \
    Two roads diverged in a wood, and I— \
    I took the one less traveled by, \
    And that has made all the difference.";

    // get the length of the text
    int length = strlen(text);

    // define the hash map implementation
    struct freq *freqs = NULL;

    // extract all pairs of characters from the text
    for (int i = 0; i < length - 1; i++) {
        // define the pair of characters to be used as the key
        struct pair p = {
            .first = text[i],
            .second = text[i+1]
        };

        // check if the key exists in the hash map
        if (hmgeti(freqs, p) >= 0) {
            // if so, get and update the frequency
            int value = hmget(freqs, p);
            hmput(freqs, p, ++value);
        } else {
            // otherwise, create a new key-value pair
            hmput(freqs, p, 1);
        }
    }

    // iterate through the hash map and print values
    for (int i = 0; i < hmlen(freqs); i++) {
        printf("%c%c: %d\n", freqs[i].key.first, freqs[i].key.second, freqs[i].value);
    }

    return 0;
}
