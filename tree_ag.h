/*
 *
 ******************************************************************************* 

   The MIT License (MIT)

   Copyright (c) <2015> <Anand Girish>

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:
 
   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.
 
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.

 *******************************************************************************
 *
 */


/*
 * description	: 
 *				  This file contains the prototype declarations for 
 *				  the API functions for the Insertion Sort Implementation.
 */

/*
 * comparator function is needed for insertion, lookup functions & always
 * follows the following rules.
 *
 * comp_result = comp(ptr_to_item_in_list, ptr_to_search_item);
 * and
 * comp_result will be
 *
 * -1 if the first argument is smaller
 *  0 if both are equal
 * +1 if the first argument is larger
 */
typedef int (*COMPARATOR)(void *, void *);

typedef void (*OPERATION)(void *);

typedef struct bst {
    struct node     *root;
    COMPARATOR      comp;
    size_t          item_size;
}bst_t;

typedef struct node {
    void            *data;
    struct node     *left;
    struct node     *right;
} node_t;

// Left SubTree, Right SubTree, Root
void   postorder_bst(bst_t *bst, OPERATION oper);
// Root, Left SubTree, Right SubTree, 
void   preorder_bst(bst_t *bst, OPERATION oper);
// Left SubTree, Root, Right SubTree, 
void   inorder_bst(bst_t *bst, OPERATION oper);
// Walks the tree, based on different traversals and argument is the 
// function that does an operations
void    display_bst (bst_t *bst, OPERATION oper); 


/*
 * If item exists, it returns still success, does not put duplicates
 */
int insert_item(bst_t *bst, void *data);
int delete_item(bst_t *bst, void *data);

void *lookup_bst (bst_t *bst, void *data);
/*
 * destory the whole tree 
 */
void delete_bst(bst_t *bst);
/* 
 * save the common node information about comparator function and item_size.
 */
bst_t *create_bst (size_t item_size,	COMPARATOR	c);

#ifdef  DEBUG
#define Printf(...) printf(__VA_ARGS__)
#else   /* DEBUG */
#define Printf(...) 
#endif  /* DEBUG */
