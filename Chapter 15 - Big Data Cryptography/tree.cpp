#include <iostream>
#include <iomanip>
#include "tree.h"

using namespace std;

merkle_tree::merkle_tree(vector<tree_node*> vector_nodes) 
{
    vector<tree_node*> aux_nodes;
    while (vector_nodes.size() != 1) 
    {
        print_hash_values(vector_nodes);
        for (int i = 0, n = 0; i < vector_nodes.size(); i = i + 2, n++) {
            if (i != vector_nodes.size() - 1) // check if there is a neighbour block
            { 
                // merges the neighbour nodes and computes the hash value of the new node
                aux_nodes.push_back(new tree_node(compute_sha256(vector_nodes[i]->hash_value + vector_nodes[i + 1]->hash_value)));
                // link the new node with the left neighbour and the right neighbour
                aux_nodes[n]->l_neighbour = vector_nodes[i]; 
                aux_nodes[n]->r_neighbour = vector_nodes[i + 1];
            } else 
            {
                aux_nodes.push_back(vector_nodes[i]);
            }
        }
        cout << "\n";
        vector_nodes = aux_nodes;
        aux_nodes.clear();
    }

    // picks the first node as the root of the tree
    this->tree_root = vector_nodes[0];
}

merkle_tree::~merkle_tree() 
{
    delete_merkle_tree(tree_root);
    cout << "The tree was deleted." << endl;
}

void merkle_tree::print_merkle_tree(tree_node *node, int index)
{
    if (node) {
        if (node->l_neighbour) {
            print_merkle_tree(node->l_neighbour, index + 4);
        }
        if (node->r_neighbour) {
             print_merkle_tree(node->r_neighbour, index + 4);
        }
        if (index) {
            cout << setw(index) << ' ';
        }
        cout << node->hash_value[0] << "\n ";
    }
}

void merkle_tree::delete_merkle_tree(tree_node *node) 
{
    if (node) {
        delete_merkle_tree(node->l_neighbour);
        delete_merkle_tree(node->r_neighbour);
        node = NULL;
        delete node;
    }
}