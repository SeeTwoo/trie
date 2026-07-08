#ifndef TRIE_H
#define TRIE_H

#define ALPHABET_SIZE 26

struct trie_node {
	struct trie_node	*children[ALPHABET_SIZE + 1];
	char				*entry;
};

#endif
