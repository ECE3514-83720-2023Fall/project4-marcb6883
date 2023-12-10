////////////////////////////////////////////////////////
// ECE 3514, Project 4, Marc-Anthony Barsoum
//
// File name:   prefixTree.h
// Description: Contains the fucntion definitions of
//				prefixTree.
// Date:        12/9/2023
//

#include "prefixTree.h"
//#include "treeNode.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>

prefixTree::prefixTree() 
{
}  // end default constructor

prefixTree::prefixTree(std::string filename) { // argument means read from a file
	std::ifstream file(filename); // read in the file
	std::string line; // declare string from the line
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string netId;
		int port;
		if (std::getline(iss, netId, ':') && iss >> port) {
			add(netId, port); // add the netid and port to prefixTree
		}
	}

}



prefixTree::~prefixTree()
{ // destructor
	
}





// type bool, assume to return true when adding is possible
bool prefixTree::add(const std::string netid, const int port) {
	if (rootPtr == nullptr) { // if can't find, then add to memory
		rootPtr = std::make_shared<treeNode>();
	}

	std::shared_ptr<treeNode> current = rootPtr;// make a pointer to add
	for (char ch : netid) { // iterate through every character in intput string
		if (ch == '0') { // if its a zer...
			if (!current->getLeftChildPtr()) {  // if left child doesn't exist make it
				current->setLeftChildPtr(std::make_shared<treeNode>());
			}
			current = current->getLeftChildPtr(); // put in left
		}
		else if (ch == '1') { // if it is a one..
			if (!current->getRightChildPtr()) { // make a right child if can't find 
				current->setRightChildPtr(std::make_shared<treeNode>());
			}
			current = current->getRightChildPtr(); // add it to current
		}
	}
	current->setNetId(netid); // make the net id and port the args provided
	current->setPort(port);
	return true; // return that you can add
}

int prefixTree::findPort(std::string ipaddr) const // need to find the longest matching prefix
{
	std::shared_ptr<treeNode> current = rootPtr; // make a pointer to the root
	int lastValidPort = -1;
	for (char ch : ipaddr) { // iterate through all of the characters
		if (!current) break; // if at the end then break

		if (current->getPort() >= 0) { // grab the current port 
			lastValidPort = current->getPort();
		}

		if (ch == '0') { // if the input address has a zero go left
			current = current->getLeftChildPtr();
		}
		else if (ch == '1') { // if 1 then go to the right
			current = current->getRightChildPtr();
		}
	}
	return lastValidPort;
	
}



bool prefixTree::remove(const std::string prefix)
{
	std::shared_ptr<treeNode> parent = nullptr; // var for parent
	std::shared_ptr<treeNode> current = rootPtr; // current node
	bool isLeftChild = false; // flag for left or righ

	// Delete the parent first
	for (char ch : prefix) {
		if (!current) return false; // node not found

		parent = current;
		if (ch == '0') {
			current = current->getLeftChildPtr();
			isLeftChild = true;
		}
		else if (ch == '1') {
			current = current->getRightChildPtr();
			isLeftChild = false;
		}
	}

	if (!current) return false; // not found
	// apply cases from slides
	// case 1 where no children
	if (!current->getLeftChildPtr() && !current->getRightChildPtr()) {
		if (current == rootPtr) {
			rootPtr = nullptr;
		}
		else if (isLeftChild) {
			parent->setLeftChildPtr(nullptr);
		}
		else {
			parent->setRightChildPtr(nullptr);
		}
	}
	// case 2 it has one child
	else if (!current->getRightChildPtr()) { // if the child is only left
		if (current == rootPtr) {
			rootPtr = current->getLeftChildPtr();
		}
		else if (isLeftChild) {
			parent->setLeftChildPtr(current->getLeftChildPtr());
		}
		else {
			parent->setRightChildPtr(current->getLeftChildPtr());
		}
	}
	else if (!current->getLeftChildPtr()) { // or if the only child is on the right
		if (current == rootPtr) {
			rootPtr = current->getRightChildPtr();
		}
		else if (isLeftChild) {
			parent->setLeftChildPtr(current->getRightChildPtr());
		}
		else {
			parent->setRightChildPtr(current->getRightChildPtr());
		}
	}
	// third case if there are two children
	else {
		// find the inorder successor (smallest in the right subtree)
		std::shared_ptr<treeNode> successorParent = current;
		std::shared_ptr<treeNode> successor = current->getRightChildPtr();
		while (successor->getLeftChildPtr() != nullptr) {
			successorParent = successor;
			successor = successor->getLeftChildPtr();
		}

		// copy the content of the successor
		current->setNetId(successor->getNetId());
		current->setPort(successor->getPort());

		// delete the original positon of the successor
		if (successor == successorParent->getRightChildPtr()) {
			successorParent->setRightChildPtr(successor->getRightChildPtr());
		}
		else {
			successorParent->setLeftChildPtr(successor->getRightChildPtr());
		}
	}

	return true;
}

void prefixTree::clear()
{
	rootPtr = nullptr;
}


std::string prefixTree::postorderTraverseHelper(std::string visit(std::shared_ptr<treeNode> NodePtr), std::shared_ptr<treeNode> treePtr) const
{
	// need recursion to keep appending to the string
	std::string result;
	if (treePtr != nullptr) {
		result += postorderTraverseHelper(visit, treePtr->getLeftChildPtr()); //result needs from left
		result += postorderTraverseHelper(visit, treePtr->getRightChildPtr()); // and right
		result += visit(treePtr);
	}
	return result;
}



RoutingEntry  prefixTree::getRoutingEntry(const std::string netId) const 
{
	std::shared_ptr<treeNode> current = rootPtr;

	// traverse the tree using for
	for (char ch : netId) {
		if (!current) {
			// if the current node is null netId is not present in the tree
			return RoutingEntry{ "", -1 };
		}

		if (ch == '0') {
			current = current->getLeftChildPtr();
		}
		else if (ch == '1') {
			current = current->getRightChildPtr();
		}
	}

	if (current && current->getNetId() == netId) {
		// If the current node's netId matches the searched netId, return its routing entry
		return current->getRoutingEntry();
	}

	// if no matching node is found return a default RoutingEntry
	return RoutingEntry{ "", -1 };
}

std::string prefixTree::postorderTraverse(std::string visit(std::shared_ptr<treeNode> NodePtr)) const {
	return postorderTraverseHelper(visit, rootPtr);
}



int prefixTree::getHeightHelper(std::shared_ptr<treeNode> subTreePtr) const
{
	if (!subTreePtr) return 0; // if empty return zero
	// I will apply recursion
	// find the maximum value of either going down the right side of the bst or left
	// add the parent
	return 1 + std::max(getHeightHelper(subTreePtr->getLeftChildPtr()), getHeightHelper(subTreePtr->getRightChildPtr()));
}

int prefixTree::getNumberOfNodesHelper(std::shared_ptr<treeNode> subTreePtr) const
{
	// use recursion to add the number of nodes in each subtree before going back up a level
	// add value of parent node
	if (!subTreePtr) return 0; // if empty return zero
	return 1 + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr()) + getNumberOfNodesHelper(subTreePtr->getRightChildPtr());
}






bool prefixTree::isEmpty() const {
	return rootPtr == nullptr;
}

int prefixTree::getHeight() const
{
	return getHeightHelper(rootPtr);
}

int prefixTree::getNumberOfNodes() const
{
	return getNumberOfNodesHelper(rootPtr);
}


