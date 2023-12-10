#include "hw4_datarecord.h"
#include <string>

std::string visitNode(std::shared_ptr<treeNode> nodePtr) {

	if (nodePtr) {
		return nodePtr->getNetId() + ":" + std::to_string(nodePtr->getPort()) + "\n";
	}
	return "";
	
}

std::string visitRoutingEntry(std::shared_ptr<treeNode> nodePtr) {
	if (nodePtr && nodePtr->getPort() >= 0) {
		return nodePtr->getNetId() + ":" + std::to_string(nodePtr->getPort()) + "\n";
	}
	return "";
}