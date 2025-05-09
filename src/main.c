#define STB_DS_IMPLEMENTATION

#include "../lib/freq.h"
#include "../lib/stb_ds.h"
#include <stdio.h>

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
