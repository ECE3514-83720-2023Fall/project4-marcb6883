

#include "treeNode.h"



treeNode::treeNode() {
	
}

treeNode::treeNode(const std::string netId_in,  int port_in) {
	
}

void treeNode::setNetId(const std::string netId_in) {

	

}
void treeNode::setPort(const int port_in) {

	
}



std::string treeNode::getNetId() const {
	
	return "";
}
 int treeNode::getPort() const {
	 return -1;
	
}
 RoutingEntry treeNode::getRoutingEntry() const
 {
	 RoutingEntry s = { "",-1 };
	 return s;
 }
bool treeNode::isLeaf() const {
	
	return false;

}

std::shared_ptr<treeNode> treeNode::getLeftChildPtr() const {

	return nullptr;
	
}
std::shared_ptr<treeNode>  treeNode::getRightChildPtr() const {
	return nullptr;
}

void treeNode::setLeftChildPtr(std::shared_ptr<treeNode> leftPtr) {
	
}

void treeNode::setRightChildPtr(std::shared_ptr<treeNode> rightPtr) {
	

}