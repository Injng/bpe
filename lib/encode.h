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

/**
 * bpe_text_to_arr() - Turns a character string into a unsigned int array.
 * @text - The pointer to the character string.
 *
 * This function takes in a chraacter array/string, text, and transforms it into
 * a dynamic array with type unsigned int. Each unsigned int corresponds to the
 * character's ASCII code, which means that an unencoded text would have all
 * values under 256.
 */
unsigned int *bpe_text_to_arr(char *text);

/**
 * bpe_encode() - Encodes one iteration of a byte pair string, if it is smaller.
 * @encoded - The struct containing the text, its encodings, and frequencies.
 *
 * This function gets the most frequent byte pair and assigns an encoding to it.
 * It will then proceed to attempt to replace all matching pairs with this
 * encoding, thereby compressing it. It will compare the new size with its
 * previous size, returning 0 and updating the encodings, text, and
 * frequencies if it is smaller, and returning -1 and exiting if it is larger.
 */
int bpe_encode(struct encoded *encoded);

#endif
