#define STB_DS_IMPLEMENTATION

#include "../lib/stb_ds.h"
#include <stdlib.h>
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

/**
 * bpe_get_freq() - Extracts the frequencies of character pairs in a text to a hash map implementation.
 * @freqs - The pointer to the hash map.
 * @text - The text to extract frequencies from.
 *
 * This function takes in a reference to a hash map implementation, freqs, and a text, text.
 * It will then iterate through all pairs in the text, updating the frequency in the hash map accordingly.
 */
void bpe_get_freq(struct freq **freqs, char *text) {
    // get the length of the text
    int length = strlen(text);

    // extract all pairs of characters from the text
    for (int i = 0; i < length - 1; i++) {
        // define the pair of characters to be used as the key
        struct pair p = {
            .first = text[i],
            .second = text[i+1]
        };

        // check if the key exists in the hash map
        if (hmgeti(*freqs, p) >= 0) {
            // if so, get and update the frequency
            int value = hmget(*freqs, p);
            hmput(*freqs, p, ++value);
        } else {
            // otherwise, create a new key-value pair
            hmput(*freqs, p, 1);
        }
    }
}

/**
 * bpe_compare_freqs() - A comparator function for sorting frequencies.
 * @p1 - A pointer to the first frequency.
 * @p2 - A pointer to the second frequency.
 *
 * This function is meant to be used with qsort, to sort the frequencies with the most frequent pair first.
 */
int bpe_compare_freqs(const void *p1, const void *p2) {
    struct freq *f1 = (struct freq *) p1;
    struct freq *f2 = (struct freq *) p2;
    return f2->value - f1->value;
}

/**
 * bpe_sort_freqs() - A function to sort a frequency hash map.
 * @freqs - The frequency hash map.
 *
 * This function uses qsort to sort the frequency hash map, putting the most frequent pair first.
 */
void bpe_sort_freqs(struct freq **freqs) {
    qsort(*freqs, hmlen(*freqs), sizeof(struct freq *), bpe_compare_freqs);
}

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

    // define the hash map implementation
    struct freq *freqs = NULL;

    // get the frequencies of each pair of characters into the hash map
    bpe_get_freq(&freqs, text);

    // sort the hash map
    bpe_sort_freqs(&freqs);

    // iterate through the hash map and print values
    for (int i = 0; i < hmlen(freqs); i++) {
        printf("%c%c: %d\n", freqs[i].key.first, freqs[i].key.second, freqs[i].value);
    }

    return 0;
}
