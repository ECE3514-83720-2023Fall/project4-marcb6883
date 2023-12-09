

#include "treeNode.h"



treeNode::treeNode() {
	rtEntry = { "", -1 }; // initialize with base value
	leftChildPtr = nullptr;	
	rightChildPtr = nullptr;
}

treeNode::treeNode(const std::string netId_in,  int port_in) {
	rtEntry = { netId_in, port_in }; // constructor with init input
	leftChildPtr = nullptr;
	rightChildPtr = nullptr;
	
}

void treeNode::setNetId(const std::string netId_in) {

	rtEntry.netId = netId_in; // use equal operator

}
void treeNode::setPort(const int port_in) {

	rtEntry.port = port_in; // use = operator
}



std::string treeNode::getNetId() const {
	
	return rtEntry.netId; // access the private member to return
}
 int treeNode::getPort() const {
	 return rtEntry.port; // access private port member to return
	
}
 RoutingEntry treeNode::getRoutingEntry() const
 {
	 return rtEntry;
 }
bool treeNode::isLeaf() const {
	// shouldn't have ant children
	return !leftChildPtr && !rightChildPtr;

}

std::shared_ptr<treeNode> treeNode::getLeftChildPtr() const {

	return leftChildPtr;
	
}
std::shared_ptr<treeNode>  treeNode::getRightChildPtr() const {
	return rightChildPtr;
}

void treeNode::setLeftChildPtr(std::shared_ptr<treeNode> leftPtr) {
	leftChildPtr = leftPtr;
}

void treeNode::setRightChildPtr(std::shared_ptr<treeNode> rightPtr) {
	rightChildPtr = rightPtr;

}