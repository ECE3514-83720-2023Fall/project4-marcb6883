#include"treeNode.h"
#include"prefixTree.h"
#include "hw4_datarecord.h"
#include<iostream>
#include<memory>


void main() {
	prefixTree myTree("routing_table.txt");
	
	std::cout << "-------------Tree ----------------------\n\n";
	std::cout << myTree.postorderTraverse(visitNode) << std::endl;
	std::cout << "----------------------------------------------\n\n";
	

	std::cout<<"end of the program \n";
	std::cin.get();

}

