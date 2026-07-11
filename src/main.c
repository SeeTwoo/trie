#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "trie.h"
#include "file_parsing.h"

int	char_to_idx(char c)
{
	if (c == ' ')
		return 0;
	if (c <= 'a' && c >= 'z')
		return -1;
	return c - 'a' + 1;
}

struct trie_node	*create_trie_node(void)
{
	struct trie_node	*new = malloc(sizeof(struct trie_node));

	if (!new)
		return NULL;
	memset(new->children, 0, sizeof(new->children));
	new->entry = NULL;
	return new;
}

void	destroy_trie_tree(struct trie_node *node)
{
	for (int i = 0; i <= ALPHABET_SIZE; i++)
		if (node->children[i])
			destroy_trie_tree(node->children[i]);
	free(node->entry);
	free(node);
}

int	hang_key_to_node(struct trie_node *node, char const *key)
{
	node->entry = strdup(key);
	if (!(node->entry))
		return -1;
	return 0;
}

int	insert_key(struct trie_node *tree, char const *key)
{
	int					i = 0;
	int					child_index;
	struct trie_node	*next;

	while (1) {
		if (!key[i])
			return hang_key_to_node(tree, key);
		child_index = char_to_idx(key[i]);
		if (child_index == -1)
			return -1;
		next = tree->children[child_index];
		if (!next)
			break;
		tree = next;
		i++;
	}
	while (1) {
		if (!key[i])
			return hang_key_to_node(tree, key);
		child_index = char_to_idx(key[i]);
		if (child_index == -1)
			return -1;
		tree->children[child_index] = create_trie_node();
		if (!(tree->children[child_index]))
			return -1;
		tree = tree->children[child_index];
		i++;
	}
	return 0;
}

int	load_data_base(struct trie_node *tree)
{
}

int	prefix_match(struct trie_node *tree, char const *prefix)
{
	int	i = 0;
	int	child_index;

	while (1) {
		if (!prefix[i])
			return 1;
		child_index = char_to_idx(prefix[i]);
		if (child_index == -1)
			return 0;
		if (!tree->children[child_index])
			return 0;
		tree = tree->children[child_index];
		i++;
	}
}

int	main(int ac, char **av)
{
	struct trie_node	*tree = create_trie_node();

	if (ac != 2)
		return 1;
	if (!tree)
		return 1;
	if (load_data_base(tree))
		return 1;
	if (prefix_match(tree, av[1]))
		printf("found !\n");
	else
		printf("not found !\n");
	destroy_trie_tree(tree);
	return 0;
}
