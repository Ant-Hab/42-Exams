#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node {
	enum { ADD, MULTI, VAL } type;
	int val;
	struct node *l;
	struct node *r;
} node;

node *new_node(node n)
{
	node *ret = calloc(1, sizeof(n));
	if (!ret)
		exit(1);
	*ret = n;
	return (ret);
}

void destroy_tree(node *n)
{
	if (!n) return;
	if (n->type != VAL)
	{
		destroy_tree(n->l);
		destroy_tree(n->r);
	}
	free(n);
}

void unexpected(char c)
{
	if (c)
		printf("Unexpected token '%c'\n", c);
	else
		printf("Unexpected end of input\n");
}

int accept(char **s, char c)
{
	if (**s == c)
	{
		(*s)++;
		return (1);
	}
	return (0);
}

int expect(char **s, char c)
{
	if (accept(s, c))
		return (1);
	unexpected(**s);
	exit(1);
}

node *parse_expr_rec(char **s);

node *parse_factor(char **s)
{
	if (isdigit((unsigned char)**s))
	{
		node n = {VAL, **s - '0', NULL, NULL};
		(*s)++;
		return (new_node(n));
	}
	else if (accept(s, '('))
	{
		node *res = parse_expr_rec(s);
		expect(s, ')');
		return (res);
	}
	unexpected(**s);
	exit(1);
}

node *parse_term(char **s)
{
	node *left = parse_factor(s);
	while (accept(s, '*'))
	{
		node *right = parse_factor(s);
		node n = {MULTI, 0, left, right};
		left = new_node(n);
	}
	return (left);
}

node *parse_expr_rec(char **s)
{
	node *left = parse_term(s);
	while (accept(s, '+'))
	{
		node *right = parse_term(s);
		node n = {ADD, 0, left, right};
		left = new_node(n);
	}
	return (left);
}

node *parse_expr(char *s)
{
	node *ret = parse_expr_rec(&s);
	if (*s)
	{
		unexpected(*s);
		destroy_tree(ret);
		exit(1);
	}
	return (ret);
}

int eval_tree(node *tree)
{
	if (tree->type == ADD)
		return (eval_tree(tree->l) + eval_tree(tree->r));
	if (tree->type == MULTI)
		return (eval_tree(tree->l) * eval_tree(tree->r));
	return (tree->val);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	node *tree = parse_expr(argv[1]);
	printf("%d\n", eval_tree(tree));
	destroy_tree(tree);
	return (0);
}
