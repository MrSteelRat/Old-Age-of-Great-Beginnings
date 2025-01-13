/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
	linux/include/linux/rbtree_types.h
*/
#ifndef RBTREE_TYPES_H
#define RBTREE_TYPES_H

struct rb_node {
	unsigned long  __rb_parent_color;
	struct rb_node *rb_right;
	struct rb_node *rb_left;
} __attribute__((aligned(sizeof(long))));
/* The alignment might seem pointless, but allegedly CRIS needs it */

struct rb_root {
	struct rb_node *rb_node;
};

#define RB_ROOT (struct rb_root) { NULL, }

#endif /* RBTREE_TYPES_H */
