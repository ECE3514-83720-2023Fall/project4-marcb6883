#ifndef DATARECORD_
#define DATARECORD_


#include <iostream>
#include <string>
#include "treeNode.h"
#include "prefixTree.h"

std::string visitNode(std::shared_ptr<treeNode> nodePtr);
std::string visitRoutingEntry(std::shared_ptr<treeNode> nodePtr);
#endif