#ifndef ENCODE_H
#define ENCODE_H

#include "freq.h"

/**
 * struct encoding - Defines a key-value pair with the key as a pair of
 * characters and the value as the encoded version of that pair.
 * @key: The pair of characters as the key.
 * @value: The encoding of the pair as the value.
 *
 * The encoding struct is meant to store information linking a pair of
 * characters to its encoded version. The pair of characters is the key used to
 * access the key-value pair, and the encoded integer is the value. This
 * structure is meant to be used as a key-value pair in the stb hash map
 * implementation.
 */
struct encoding {
    struct pair key;
    unsigned int value;
};

/**
 * struct encoded - Defines a struct that contains all the information for an
 * encoded sequence of text.
 * @text: The encoded text as a dynamic array of unsigned int.
 * @encodings: The hash map of encodings to character pairs.
 * @freqs: The frequency of character pair occurences in the text.
 *
 * The encoded struct encapsulates all the information for an encoded sequence
 * of text. The encodings define the mappings between the encoded values
 * in the text, and the decoded ASCII values (0-255). The frequency hash map
 * is updated in-place and contains the frequencies of every character pair
 * in the encoded text.
 */
struct encoded {
    unsigned int *text;
    struct encoding *encodings;
    struct freq *freqs;
};

unsigned int *bpe_text_to_arr(char *text);

unsigned long bpe_get_size(unsigned int *text, struct encoding *encodings);

unsigned int bpe_assign_encoding(struct encoding **encodings, struct pair p);

int bpe_encode(struct encoded *encoded);

#endif
