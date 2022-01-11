/*
 * =============================================================================
 *
 *       Filename:  rbtree-tst.c
 *
 *    Description:  rbtree testcase.
 *
 *        Created:  09/02/2012 11:39:34 PM
 *
 *         Author:  Fu Haiping (forhappy), haipingf@gmail.com
 *        Company:  ICT ( Institute Of Computing Technology, CAS )
 *
 * =============================================================================
 */

#include "linux_rbtree.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <list>
#include <assert.h>

#define offsetof_t(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({			\
        const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
        (type *)( (char *)__mptr - offsetof_t(type,member) );})


// #undef NULL
// #if defined(__cplusplus)
//   #define NULL 0
// #else
//   #define NULL ((void *)0)
// #endif

struct mynode {
  	struct rb_node node;
  	int value;
};

struct rb_root mytree = RB_ROOT;

struct mynode * my_search(struct rb_root *root, int value)
{
  	struct rb_node *node = root->rb_node;

  	while (node) {
  		struct mynode *data = container_of(node, struct mynode, node);
		int result;

		result = value - data->value; // strcmp(string, data->string);

		if (result < 0)
  			node = node->rb_left;
		else if (result > 0)
  			node = node->rb_right;
		else
  			return data;
	}
	return NULL;
}

int my_insert(struct rb_root *root, struct mynode *data)
{
  	struct rb_node **n = &(root->rb_node), *parent = NULL;

  	/* Figure out where to put n node */
  	while (*n) {
  		struct mynode *_node = container_of(*n, struct mynode, node);
  		int result = data->value - _node->value ;// strcmp(data->string, _node->string);

		parent = *n;
  		if (result < 0)
  			n = &((*n)->rb_left);
  		else if (result > 0)
  			n = &((*n)->rb_right);
  		else
  			return 0;
  	}

  	/* Add n node and rebalance tree. */
  	rb_link_node(&data->node, parent, n);
  	rb_insert_color(&data->node, root);

	return 1;
}

void my_free(struct mynode *node)
{
	if (node != NULL) {
		free(node);
	}
}

#define NUM_NODES 32

int main()
{
	std::list<struct mynode*> repo;
	srand((u_int32_t)time(NULL));
	const int count=1000*1000;
	for(int i=0;i<count;i++){
		struct mynode *node = new struct mynode;
		node->value = rand();
		if (my_insert(&mytree, node) ==1){
			repo.push_back(node);
		}else{
			delete node;
		}
	}

	// search
	printf("%ld \n",repo.size());
	for(auto const& v: repo) {
		struct mynode *node= my_search(&mytree, v->value) ;
		// printf("s: %ld \n",v->value);
 		assert(node!=NULL);
	}

	// free

	for(auto const& v: repo) {
		// // struct mynode *node= my_search(&mytree, v->value) ;
 		// // assert(ode!=NULL);
		// delete v;
		// printf("d: %ld \n",v->value);
		rb_erase(&v->node,&mytree);
	}

	for(auto const& v: repo) {
		struct mynode *node= my_search(&mytree, v->value) ;
 		assert(node==NULL);
	}

	return 0;
}

