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
 *				  this file contains the infrastructure routines
 *				  to implement tree data structure general interface.
 *				  <This file is not complete yet....>
 */

#include <stdio.h>
#include <errno.h>
#include "tree_ag.h"


/*
 * the routine to swap the two items whose type is not known. 
 */
void swap_data (void *first_item, void *second_item, size_t item_size)
{
	void *temp;
	if (!(temp = (void *)malloc (item_size))) {
		Printf ("%S(%d): unrecoverable error: no memory..!!!\n",
                __FUNCTION__, __LINE__);
		return;
	}
	memcpy (temp, first_item, item_size);
	memcpy (first_item, second_item, item_size);
	memcpy (second_item, temp, item_size);	
    free(temp);
}

void postorder_bst_node(node_t *root, OPERATION oper)
{
    if (root) {
        postorder_bst_node(root->left, oper);
        postorder_bst_node(root->right, oper);
        oper(root->data);
    }
}

// Left SubTree, Right SubTree, Root
void   postorder_bst(bst_t *bst, OPERATION oper)
{
    postorder_bst_node(bst->root, oper);
}

void preorder_bst_node(node_t *root, OPERATION oper)
{
    if (root) {
        oper(root->data);
        preorder_bst_node(root->left, oper);
        preorder_bst_node(root->right, oper);
    }
}

// Root, Left SubTree, Right SubTree, 
void   preorder_bst(bst_t *bst, OPERATION oper)
{
    preorder_bst_node(bst->root, oper);
}

void   inorder_bst_node(node_t *root, OPERATION oper)
{
    if (root) {
        inorder_bst_node(root->left, oper);
        oper(root->data);
        inorder_bst_node(root->right, oper);
    }
}


// Left SubTree, Root, Right SubTree, 
void   inorder_bst(bst_t *bst, OPERATION oper)
{
    inorder_bst_node(bst->root, oper);
}

// Walks the tree, based on different traversals and argument is the 
// function that does an operations
void    display_bst (bst_t *bst, OPERATION oper)
{
    printf("%s(%d): InOrder traveral, Left, Root, Right\n",
            __FUNCTION__, __LINE__);
    inorder_bst(bst, oper);
    printf("\n\n");

    printf("%s(%d): PreOrder traveral, Root, Left, Right\n",
            __FUNCTION__, __LINE__);
    preorder_bst(bst, oper);
    printf("\n\n");

    printf("%s(%d): PostOrder traveral, Left, Right, Root\n",
            __FUNCTION__, __LINE__);
    postorder_bst(bst, oper);
    printf("\n\n");
}




node_t *find_bst_node (bst_t *bst, node_t *root, void *data, node_t **node_parent) 
{
    int comp_val; 

    // leverage BST property and look for data based on node's data and 
    // data being sought to traverse left or right and if we reach end of the tree
    // without match return null.
    if (NULL == root) {
        Printf("%s(%d): No match found in the BST\n",
                __FUNCTION__, __LINE__);
        *node_parent = NULL;
        return NULL;
    }

    // check data with comparator function and move accodingly to right or left
    // of the tree
    comp_val = bst->comp(root->data, data);

    // Found the match, return the node. parent must be set by recursive caller.
    // first caller is expected to have set it to NULL.
    // alternately we csn see if the node being returned is bst root set it to NULL.
    if (0 == comp_val) {
        if (root == bst->root) {
            Printf("%s(%d): Found match in the BST root node\n",
                    __FUNCTION__, __LINE__);
            *node_parent = NULL;
        } else {
            Printf("%s(%d): Found match\n",
                    __FUNCTION__, __LINE__);
        }
        return root;
    } 

    // If data is less then currnet node value go left and search
    // Either way set the parent to current node for next sub tree 
    // search.
    *node_parent = root;
    if (comp_val > 0) 
        root = root->left;
    else 
        root = root->right;

    return find_bst_node(bst, root, data, node_parent);
}

void *lookup_bst (bst_t *bst, void *data)
{
    node_t *node, *node_parent;
    
    node = find_bst_node(bst, bst->root, data, &node_parent);
    if (node) 
        return node->data;
    return NULL;
}

node_t *find_inorder_successor (node_t *root, node_t **succ_parent)
{
    // In order successor is the left most node in the right child tree
    *succ_parent = root;
    root = root->right;
    while (root->left) {
        *succ_parent = root;
        root = root->left;
    }
    return root;
}


node_t *find_inorder_predecessor (node_t *root, node_t **pred_parent)
{
    // In order predecessor is the right most node in the left tree of the 
    // tree being passed to us.
    *pred_parent = root;
    root = root->left;
    while (root && root->right) {
        *pred_parent = root;
        root = root->right;
    }
    return root;
}


/*
 * destory the whole tree 
 */
void delete_bst(bst_t *bst);

//#define DELETE_BST_RECURSIVE
#ifdef DELETE_BST_RECURSIVE
node_t *delete_bst_node (node_t *root, void *data, size_t item_size, COMPARATOR comp)
{
    static int recurs_level = 0;
    node_t *temp; 
    int    comp_val;

    recurs_level++;
    // if reached end of the recursion and not found 
    if (NULL == root) {
        Printf("%s(%d): R(%d) Delete node not found\n",
                    __FUNCTION__, __LINE__, recurs_level);
    } else {
        comp_val = comp(root->data, data);

        // Go left for data < root's data
        if (comp_val > 0) {
            Printf("%s(%d): R(%d) Delete node trying in left sub tree\n",
                    __FUNCTION__, __LINE__, recurs_level);
            root->left = delete_bst_node(root->left, data, item_size, comp);
        } else if (comp_val < 0) {
            Printf("%s(%d): R(%d) Delete node trying in right  sub tree\n",
                    __FUNCTION__, __LINE__, recurs_level);
            root->left = delete_bst_node(root->right, data, item_size, comp);
        } else {
            node_t *repl_node, *repl_node_parent = NULL;
            // Found the delete node
            // If the node has both children, find a in-order predecessor 
            // swap the data with current node, 
            // further start deleting the successor node from the left sub tree
            // so that the rest of the recursion works just like first one.
            if (root->left && root->right) {
                Printf("%s(%d): R(%d) Delete node has both children\n",
                    __FUNCTION__, __LINE__, recurs_level);
                repl_node = find_inorder_predecessor (root, &repl_node_parent); 
                // repl_node cannot be NULL since it has left child
                memcpy(root->data, repl_node->data, item_size);
                Printf("%s(%d): R(%d) recurs delete wind root->left %p, repl %p\n",
                            __FUNCTION__, __LINE__, recurs_level, root->left, repl_node);
                root->left = delete_bst_node(root->left, root->data, item_size, comp); 
                Printf("%s(%d): R(%d) recurs delete unwind root->left %p\n",
                            __FUNCTION__, __LINE__, recurs_level, root->left);
            } else {
                node_t *repl_node = root;
                
                Printf("%s(%d): R(%d) Delete node %p\n",
                            __FUNCTION__, __LINE__, recurs_level, root);
                if (root->left == NULL) {
                    Printf("%s(%d): R(%d) Delete node %p has right child\n",
                            __FUNCTION__, __LINE__, recurs_level, root);
                    root = root->right; // On return the left child of parent
                                        // will be set to the right child.
                } else if (root->right == NULL) {
                    Printf("%s(%d): R(%d) Delete node %p has left child\n",
                            __FUNCTION__, __LINE__, recurs_level, root);
                    root = root->left;  // On return the left child of parent
                                        // will be set to the left child.
                } else {
                    Printf("%s(%d): R(%d) Delete node %p has no children\n",
                            __FUNCTION__, __LINE__, recurs_level, root);
                    root = NULL;  // On return the left child of parent
                }
                free(repl_node->data);
                free(repl_node);
                Printf("%s(%d): R(%d) node %p delete complete root %p\n",
                            __FUNCTION__, __LINE__, recurs_level, repl_node, root);
                recurs_level = 1;
            }   // One child node
        } // Found delete node
    }
    Printf("%s(%d): R(%d) returning root node %p\n",
            __FUNCTION__, __LINE__, recurs_level, root);
    return root;
}

int delete_item(bst_t *bst, void *data) 
{
    node_t *root;
    root = delete_bst_node(bst->root, data, bst->item_size, bst->comp);
    Printf("%s(%d): returning root %p bst->root %p\n",
            __FUNCTION__, __LINE__, root, bst->root);
    // If the bst root we had kept is changed, we need to keep this new root 
    // as the tree
    if (root != bst->root) {
        Printf("%s(%d): setting new root %d for bst->root %p\n",
                __FUNCTION__, __LINE__, root, bst->root);
        bst->root = root;
    }
    return 1;
}
#endif  /*  DELETE_BST_RECURSIVE */

#define  DEL_BST_NONRECURSIVE
#ifdef  DEL_BST_NONRECURSIVE
int delete_item(bst_t *bst, void *data) 
{
    node_t *del_node, *del_node_parent = NULL, *repl_node = NULL, 
           *repl_node_parent = NULL;

    // Find the item in the BST
    del_node = find_bst_node(bst, bst->root, data, &del_node_parent);
    if (NULL == del_node)
        return 1;

    // If one child is missing
    if (NULL == del_node->right) {
        Printf("%s(%d): Delete node has left child\n",
                    __FUNCTION__, __LINE__);
        repl_node = del_node->left;
    } else if (NULL == del_node->left) {
        Printf("%s(%d): Delete node has right child\n",
                    __FUNCTION__, __LINE__);
        repl_node = del_node->right;
    } else {
        Printf("%s(%d): Delete node has both children\n",
                    __FUNCTION__, __LINE__);
    // The node to be deleted has both children.
    // Options to preserved BST property, pick the in-order predeccesor node [
    // highest node in the left sub-tree]
    // Once we swap the data, the predecessor node can be deleted using above 
    // above method.
    // The only issue is since the node to be deleted will need update to it's 
    // parent.
    // Need to get that when we find the successor the function can also return it's 
    // parent.
    repl_node = find_inorder_predecessor(del_node, &repl_node_parent);
   
    // if the replacement node's parent is not the node to be deleted.
    // it means we promote the replacement node's left child in the place 
    // of the replacement node. 
    if (repl_node_parent != del_node) {
        Printf("%s(%d): replacement node is not immediate child of delete node\n",
                    __FUNCTION__, __LINE__);
        // If replacement node has a left child and not a leaf that gets
        // promoted to the replacement node's parent's right [predecessor]
        if (repl_node->left) {
            Printf("%s(%d): replacement node has left child\n",
                    __FUNCTION__, __LINE__);
            repl_node_parent->right = repl_node->left;
        } else  {
            Printf("%s(%d): replacement node is a leaf node\n",
                    __FUNCTION__, __LINE__);
            repl_node_parent->right = NULL;
        }
    }
    
    // Have to move the children of the deleted node to the replacement node 
    // so that we can safely delete the node we wanted to.
    // Note that replacement node's child is already moved to it's parent
    // so it is essentially a node all by itself.
    // Once case is if the replacement node is immediate child of delete node
    // by setting child pointers of node to itself, we will cause loops.
    // By choosing the predecessor we know the replacement node can only be
    // right most leaf of the node's left child. 
    if (repl_node_parent == del_node) 
        Printf("%s(%d): Avoiding repl_node's "
               "[right child of delete node's left subtree] left "
               "being set to delete node's left child !\n",
                    __FUNCTION__, __LINE__);
    else 
        repl_node->left = del_node->left;
    // taking right child of the deleted node and copying to replacement node is no
    // issue since the replacement node can never be deleted node's right child
    repl_node->right  = del_node->right;
    }

    // If deleted node parent is NULL we changed the root. so set the root to 
    // the replacement node.
    if (NULL == del_node_parent) {
        Printf("%s(%d): updating root node of the tree\n",
                __FUNCTION__, __LINE__);
        bst->root = repl_node; 
    } else {
        // Updte the delete node's parent's right or left as the case was where 
        // delete node was with the replacement node.
        if (del_node_parent->left == del_node) {
            Printf("%s(%d): updating delete node parent's left child with "
               "replacement node\n",
                __FUNCTION__, __LINE__);
            del_node_parent->left = repl_node;    
        } else {
            Printf("%s(%d): updating delete node parent's right child with "
               "replacement node\n",
                __FUNCTION__, __LINE__);
            del_node_parent->right = repl_node;    
       }
    }
    // Now free the node data and the node
    free(del_node->data);
    free(del_node);
}
#endif     /* DEL_BST_NONRECURSIVE */
#ifdef  FIRST_CUT_CORES 
/*
 * delete item
 * this version was to see why certain optimizations were useful and otherwise 
 * to see hwat breaks. This hit a core when root was getting deleted. 
display_bst(83): InOrder traveral, Left, Root, Right
 23 45

display_bst(88): PreOrder traveral, Root, Left, Right
 23 45

display_bst(93): PostOrder traveral, Left, Right, Root
 45 23

        Delete Integer ? : 23
find_bst_node(125): Found match in the BST root node
delete_item(251): Delete node has right child
Segmentation fault (core dumped)

 */
int delete_item(bst_t *bst, void *data) 
{
    node_t *del_node, *del_node_parent, *repl_node, *repl_node_parent;

    // Find the item in the BST
    del_node = find_bst_node(bst, bst->root, data, &del_node_parent);
    if (NULL == del_node)
        return 1;

    // If the node to be deleted is a leaf [no children]
    // make the parent's left or right which points to this node NULL
    if ((NULL == del_node->left) && (NULL == del_node->right)) {
        Printf("%s(%d): Deleting leaf node\n",
                    __FUNCTION__, __LINE__);
        // if this is the root and only node in the BST
        if (NULL == del_node_parent) {
            Printf("%s(%d): Deleting Root node\n",
                    __FUNCTION__, __LINE__);
            bst->root = NULL;
            free(del_node->data);
            free(del_node);
            return 1;
        }
        // The delete node could be the right ot left child of the parent 
        // update the same for delete node parent
        if (del_node == del_node_parent->left)  {
            Printf("%s(%d): Parent's left child is the delete leaf node\n",
                    __FUNCTION__, __LINE__);
            del_node_parent->left = NULL;
        } else {
            Printf("%s(%d): Parent's right child is the delete leaf node\n",
                    __FUNCTION__, __LINE__);
            del_node_parent->right = NULL;
        }
        return 1;
    }

    // If the node to be deleted has only left child
    // we can make the node's left sub tree the left child of parent
    if (NULL == del_node->right) {
        Printf("%s(%d): Delete node has left child\n",
                    __FUNCTION__, __LINE__);
        // The delete node could be the right ot left child of the parent 
        // update the same for delete node parent
        if (del_node == del_node_parent->left)  {
            Printf("%s(%d): Parent's left child is the delete node with left child\n",
                    __FUNCTION__, __LINE__);
            del_node_parent->left = del_node->left;
        } else {
            Printf("%s(%d): Parent's right child is the delete node with left child\n",
                    __FUNCTION__, __LINE__);
            del_node_parent->right = del_node->left;
        }
        return 1;
    }

    // If the node to be deleted has only right child
    // we can make the node's right sub tree the right child of parent
    if (NULL == del_node->left) {
        Printf("%s(%d): Delete node has right child\n",
                    __FUNCTION__, __LINE__);
        // The delete node could be the right ot left child of the parent 
        // update the same for delete node parent
        if (del_node == del_node_parent->left)  {
            Printf("%s(%d): Parent's left child is the delete node with right child\n",
                    __FUNCTION__, __LINE__);
            del_node_parent->left = del_node->right;
        } else {
            Printf("%s(%d): Parent's right child is the delete node with right child\n",
                    __FUNCTION__, __LINE__);
            del_node_parent->right = del_node->right;
        }
        return 1;
    }

    // The node to be deleted has both children.
    // Options to preserved BST property, pick the in-order predeccesor node [
    // highest node in the left sub-tree]
    // Once we swap the data, the predecessor node can be deleted using above 
    // above method.
    // The only issue is since the node to be deleted will need update to it's 
    // parent.
    // Need to get that when we find the successor the function can also return it's 
    // parent.
    repl_node = find_inorder_predecessor(del_node->left, &repl_node_parent);
   
    // if the replacement node's parent is not the node to be deleted.
    // it means we promote the replacement node's left child in the place 
    // of the replacement node. 
    if (repl_node_parent != del_node) {
        Printf("%s(%d): replacement node is not immediate child of delete node\n",
                    __FUNCTION__, __LINE__);
        // If replacement node has a left child and not a leaf that gets
        // promoted to the replacement node's parent's right [predecessor]
        if (repl_node->left) {
            Printf("%s(%d): replacement node has left child\n",
                    __FUNCTION__, __LINE__);
            repl_node_parent->right = repl_node->left;
        } else  {
            Printf("%s(%d): replacement node is a leaf node\n",
                    __FUNCTION__, __LINE__);
            repl_node_parent->right = NULL;
        }
    }
    
    // Have to move the children of the deleted node to the replacement node 
    // so that we can safely delete the node we wanted to.
    // Note that replacement node's child is already moved to it's parent
    // so it is essentially a node all by itself.
    // Once case is if the replacement node is immediate child of delete node
    // by setting child pointers of node to itself, we will cause loops.
    // By choosing the predecessor we know the replacement node can only be
    // right most leaf of the node's left child. 
    if (repl_node_parent == del_node) 
        Printf("%s(%d): Avoiding repl_node's "
               "[right child of delete node's left subtree] left "
               "being set to delete node's left child !\n",
                    __FUNCTION__, __LINE__);
    else 
        repl_node->left = del_node->left;
    // taking right child of the deleted node and copying to replacement node is no
    // issue since the replacement node can never be deleted node's right child
    repl_node->left  = del_node->left;

    // Updte the delete node's parent's right or left as the case was where 
    // delete node was with the replacement node.
    if (del_node_parent->left == del_node) {
        Printf("%s(%d): updating delete node parent's left child with "
               "replacement node\n",
                __FUNCTION__, __LINE__);
        del_node_parent->left = repl_node;    
    } else {
        Printf("%s(%d): updating delete node parent's right child with "
               "replacement node\n",
                __FUNCTION__, __LINE__);
        del_node_parent->right = repl_node;    
    }
}
#endif /* FIRST_CUT_CORES */
    
/*
 * Insert a node to bst tree, tree is not empty and no dulicates.
 * if item exists returns 0 or if insertion fails.
 */
int insert_bst_node (node_t *root, node_t *node, COMPARATOR comp)
{
    static int recurs_level = 0;
    int comp_val;
    
    comp_val = comp(root->data, node->data);

    recurs_level++;
    // Duplicate check
    if (0 == comp_val) {
        Printf("%s(%d): R(%d): Duplicae item rejected\n",
            __FUNCTION__, __LINE__, recurs_level);
        return 0;
    }
    Printf("%s(%d): R(%d): root %p node %p comp %p\n",
            __FUNCTION__, __LINE__, recurs_level, root, node, comp);
    // If value is less than root's data,
    if (comp_val > 0) {
        if (NULL == root->left)  {
            // no left sub tree and so this is the right place to insert
            Printf("%s(%d): R(%d): Inserting left leaf\n",
                    __FUNCTION__, __LINE__, recurs_level);
            root->left = node;
        } else  {
            // we have to start finding the right place in the left sub tree
            Printf("%s(%d): R(%d): Searching left sub tree\n",
                    __FUNCTION__, __LINE__, recurs_level);
            return insert_bst_node(root->left, node, comp);
        }
    } else {
    // If value is greater than root's data
        if (NULL == root->right) {
            // no right so this is the right place for the node
            Printf("%s(%d): R(%d): Inserting right leaf\n",
                    __FUNCTION__, __LINE__, recurs_level);
            root->right = node;
        } else {
            // we hve to start finding right place in the right sub tree
            Printf("%s(%d): R(%d): Searching right sub tree\n",
                    __FUNCTION__, __LINE__, recurs_level);
            return insert_bst_node(root->right, node, comp);
        }
    }
    // reset recursion level
    recurs_level = 0;
    return 1;
}

/*
 * If item exists, it returns still success, does not put duplicates
 */
int insert_item(bst_t *bst, void *data)
{
    node_t *node;
    int    ret_val;
    //sanity checks, pointers not null.

    // prepare the node 
    node = (node_t *)malloc(sizeof(node_t));
    node->left = node->right = NULL;
    node->data = malloc(bst->item_size);
    if (NULL == node->data) {
        free(node);
        return 0;
    }
    // Copy the data to the node
    memcpy(node->data, data, bst->item_size);
    
    // If first node make 
    if (NULL == bst->root) {
        Printf("%s:(%d): Insertion node %p as bst root\n", __FUNCTION__, __LINE__, node);
        bst->root = node;
        return 1;
    }
    
    // Tree is not empty, insert it right place.
    ret_val = insert_bst_node (bst->root, node, bst->comp);
    if (0 == ret_val) {
        Printf("%s:(%d): Insertion rejected\n", __FUNCTION__, __LINE__);
        // free node's data container and node itself.
        free(node->data);
        free(node);
    }
    Printf("%s(%d): node %p inserted into bst, root %p\n",
            __FUNCTION__, __LINE__, node, bst->root);
    return ret_val;
}

/* Build tree of data 
 * the comparartor function.
 * returns the tree root if successful, else NULL;
 */
bst_t *create_bst (size_t item_size, COMPARATOR	comp) 
{ 
    bst_t *bst = malloc(sizeof(bst_t));

    if (bst) {
        bst->root      = NULL;
        bst->comp      = comp;
        bst->item_size = item_size;
    }
    return bst;
}

