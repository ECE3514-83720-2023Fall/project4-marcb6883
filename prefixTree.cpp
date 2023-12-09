

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

prefixTree::prefixTree(std::string filename) {


}



prefixTree::~prefixTree()
{
	
}






bool prefixTree::add(const std::string netid, const int port) {
	
	return false;
}

int prefixTree::findPort(std::string ipaddr) const
{

	return -1;
	
}



bool prefixTree::remove(const std::string prefix)
{
	
	return false;
}

void prefixTree::clear()
{
	
	return;
}


std::string prefixTree::postorderTraverseHelper(std::string visit(std::shared_ptr<treeNode> NodePtr), std::shared_ptr<treeNode> treePtr) const
{
	
	return "";
}



RoutingEntry  prefixTree::getRoutingEntry(const std::string netId) const 
{

	return RoutingEntry{ "", -1 };
}

std::string prefixTree::postorderTraverse(std::string visit(std::shared_ptr<treeNode> NodePtr)) const {
	return "";
}



int prefixTree::getHeightHelper(std::shared_ptr<treeNode> subTreePtr) const
{
	return -1;
}

int prefixTree::getNumberOfNodesHelper(std::shared_ptr<treeNode> subTreePtr) const
{
	return -1;
}





bool prefixTree::isEmpty() const {
	return true;
}

int prefixTree::getHeight() const
{
	return 0;
}

int prefixTree::getNumberOfNodes() const
{
	return 0;
}


