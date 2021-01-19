#include <iostream>
#include "tree.h"

using namespace std;


int main() {
    vector<tree_node*> nodes_set;

    //create sample data
    nodes_set.push_back(new tree_node(compute_sha256("Merkle ")));
    nodes_set.push_back(new tree_node(compute_sha256("tree ")));
    nodes_set.push_back(new tree_node(compute_sha256("node ")));
    nodes_set.push_back(new tree_node(compute_sha256("example.")));
    nodes_set.push_back(new tree_node(compute_sha256("This is an example of merkle tree.")));    

    // initialize leaves
    for (unsigned int i = 0; i < nodes_set.size(); i++) {
        nodes_set[i]->l_neighbour = NULL;
        nodes_set[i]->r_neighbour = NULL;
    }

    merkle_tree *hash_tree = new merkle_tree(nodes_set);
    std::cout << hash_tree->tree_root->hash_value << std::endl;
    hash_tree->print_merkle_tree(hash_tree->tree_root, 0);

    for (int k = 0; k < nodes_set.size(); k++) {
        delete nodes_set[k];
    }

    delete hash_tree;

    return 0;
}