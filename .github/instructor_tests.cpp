#define CATCH_CONFIG_MAIN			// this line tells Catch to provide a main() function
#define CATCH_CONFIG_COLOUR_NONE


#include "../catch.hpp"
#include "../prefixTree.h"
#include "../treeNode.h"
#include "../hw4_datarecord.h"


TEST_CASE("Test  TreeNode functions") {



	treeNode myNode0;
	myNode0.setNetId("");
	myNode0.setPort(1);
	CHECK(myNode0.getNetId() == "");
	CHECK(myNode0.getPort() == 1);


	treeNode  myNode = treeNode("0", 1);
	CHECK(myNode.getNetId() == "0");
	CHECK(myNode.getPort() == 1);


	std::shared_ptr<treeNode> nodePtr1 = std::make_shared<treeNode>("0101", 3);

	CHECK(nodePtr1->getNetId() == "0101");
	CHECK(nodePtr1->getPort() == 3);


	std::shared_ptr<treeNode> nodePtr2 = std::make_shared<treeNode>("0", 1);


	nodePtr2->setNetId("0101000");
	nodePtr2->setPort(2);
	CHECK(nodePtr2->getNetId() == "0101000");
	CHECK(nodePtr2->getPort() == 2);



	CHECK(myNode.isLeaf() == true);

	myNode.setLeftChildPtr(nodePtr1);

	CHECK(myNode.isLeaf() == false);
	myNode.setRightChildPtr(nodePtr2);
	CHECK(myNode.isLeaf() == false);

	CHECK(nodePtr1 == myNode.getLeftChildPtr());
	CHECK(nodePtr2 == myNode.getRightChildPtr());

	RoutingEntry rtentry = nodePtr2->getRoutingEntry();
	CHECK(rtentry.netId == "0101000");
	CHECK(rtentry.port == 2);

	CHECK(visitNode(nodePtr1) == "0101:3\n");
	CHECK(visitRoutingEntry(nodePtr1) == "0101:3\n");

	nodePtr1->setPort(-1);
	CHECK(visitNode(nodePtr1) == "0101:-1\n");
	CHECK(visitRoutingEntry(nodePtr1) == "");

}





TEST_CASE("Test constructor functions of prefixTree", "[constructor]") {

	prefixTree myTree;

	CHECK(myTree.isEmpty() == true);

	//return the height of the prefix tree
	CHECK(myTree.getHeight() == 0);

	//return the number of nodes in the prefix tree
	CHECK(myTree.getNumberOfNodes() == 0);


}

TEST_CASE("Test Addition of Root Node to the Prefix Tree", "[Add]") {

	prefixTree myTree;

	REQUIRE(myTree.add("", 0) == true);


	REQUIRE(myTree.isEmpty() == false);
	CHECK(myTree.getHeight() == 1);
	CHECK(myTree.getNumberOfNodes() == 1);
	CHECK(myTree.getRoutingEntry("").netId == "");
	CHECK(myTree.getRoutingEntry("").port == 0);
	std::string str1 = ":0\n";
	CHECK(str1.compare(myTree.postorderTraverse(visitNode)) == 0);

}


TEST_CASE("Test Addition of Multiple Entries to the Prefix Tree", "[Add]") {

	prefixTree myTree;

	REQUIRE(myTree.add("", 0) == true);


	REQUIRE(myTree.isEmpty() == false);
	CHECK(myTree.getHeight() == 1);
	CHECK(myTree.getNumberOfNodes() == 1);

	REQUIRE(myTree.add("011", 2) == true);
	REQUIRE(myTree.add("1", 3) == true);


	CHECK(myTree.getHeight() == 2);
	CHECK(myTree.getNumberOfNodes() == 3);

	std::string str1 = "011:2\n1:3\n:0\n";
	CHECK(str1.compare(myTree.postorderTraverse(visitNode)) == 0);

	REQUIRE(myTree.add("011", 4) == true);
	str1 = "011:4\n1:3\n:0\n";
	CHECK(str1.compare(myTree.postorderTraverse(visitNode)) == 0);

	REQUIRE(myTree.add("0001", 5) == true);
	CHECK(myTree.getHeight() == 3);
	CHECK(myTree.getNumberOfNodes() == 5);

	str1 = "0001:5\n011:4\n0:-1\n1:3\n:0\n";
	CHECK(str1.compare(myTree.postorderTraverse(visitNode)) == 0);
	str1 = "0001:5\n011:4\n1:3\n:0\n";
	CHECK(str1.compare(myTree.postorderTraverse(visitRoutingEntry)) == 0);

	REQUIRE(myTree.add("0", 1) == true);
	CHECK(myTree.getHeight() == 3);
	CHECK(myTree.getNumberOfNodes() == 5);

	str1 = "0001:5\n011:4\n0:1\n1:3\n:0\n";
	CHECK(str1.compare(myTree.postorderTraverse(visitNode)) == 0);

}




TEST_CASE("Test Removing a routing entry stored at a leaf node from the Prefix Tree", "[Remove]") {

	prefixTree myTree;

	REQUIRE(myTree.add("", 0) == true);
	REQUIRE(myTree.add("0", 1) == true);;
	REQUIRE(myTree.add("011", 2) == true);;
	REQUIRE(myTree.add("1", 3) == true);;

	CHECK(myTree.getHeight() == 3);
	CHECK(myTree.getNumberOfNodes() == 4);

	REQUIRE(myTree.remove("011") == true);;
	CHECK(myTree.getHeight() == 2);
	CHECK(myTree.getNumberOfNodes() == 3);

	std::string str1 = "0:1\n1:3\n:0\n";
	CHECK(str1.compare(myTree.postorderTraverse(visitNode)) == 0);

}


TEST_CASE("Test Removing a routing entry stored at an internal node from the Prefix Tree", "[Remove]") {

	prefixTree myTree;

	REQUIRE(myTree.add("", 0) == true);
	REQUIRE(myTree.add("0", 1) == true);
	REQUIRE(myTree.add("011", 2) == true);
	REQUIRE(myTree.add("1", 3) == true);
	REQUIRE(myTree.add("0001", 4) == true);

	CHECK(myTree.getHeight() == 3);
	CHECK(myTree.getNumberOfNodes() == 5);

	std::string str1 = "0001:4\n011:2\n0:1\n1:3\n:0\n";
	CHECK(str1.compare(myTree.postorderTraverse(visitNode)) == 0);


	CHECK(myTree.remove("0") == true);
	CHECK(myTree.getHeight() == 3);
	CHECK(myTree.getNumberOfNodes() == 5);

	str1 = "0001:4\n011:2\n0:-1\n1:3\n:0\n";
	CHECK(str1.compare(myTree.postorderTraverse(visitNode)) == 0);

	str1 = "0001:4\n011:2\n1:3\n:0\n";
	CHECK(str1.compare(myTree.postorderTraverse(visitRoutingEntry)) == 0);


	myTree.clear();
	myTree.add("0", 1);
	myTree.add("00", 2);
	CHECK(myTree.remove("0") == true);
	CHECK(myTree.getHeight() == 1);
	CHECK(myTree.getNumberOfNodes() == 1);
	str1 = "00:2\n";
	CHECK(str1.compare(myTree.postorderTraverse(visitNode)) == 0);

	myTree.clear();
	myTree.add("0", 1);
	myTree.add("01", 2);
	CHECK(myTree.remove("0") == true);
	CHECK(myTree.getHeight() == 1);
	CHECK(myTree.getNumberOfNodes() == 1);
	str1 = "01:2\n";
	CHECK(str1.compare(myTree.postorderTraverse(visitNode)) == 0);


	myTree.clear();
	myTree.add("0", 1);
	myTree.add("01", 2);
	CHECK(myTree.remove("1") == false);
	CHECK(myTree.getHeight() == 2);
	CHECK(myTree.getNumberOfNodes() == 2);



}


TEST_CASE("Test Removing a non-existent routing entry from the Prefix Tree", "[Remove]") {

	prefixTree myTree;

	REQUIRE(myTree.add("", 0) == true);
	REQUIRE(myTree.add("0", 1) == true);
	REQUIRE(myTree.add("011", 2) == true);
	REQUIRE(myTree.add("1", 3) == true);
	REQUIRE(myTree.add("0001", 4) == true);

	CHECK(myTree.remove("111") == false);
	REQUIRE(myTree.remove("0") == true);
	CHECK(myTree.remove("0") == false);
}

TEST_CASE("Test Creating a PrefixTree from an input file", "[constructor]") {

	prefixTree myTree("./routing_table.txt");

	CHECK(myTree.getHeight() == 5);
	CHECK(myTree.getNumberOfNodes() == 12);

	std::string str1 = "0100001:1\n0101:2\n010:-1\n01:2\n0:12\n1011110:15\n1011111:16\n101111:-1\n101:1\n11:3\n1:-1\n:0\n";
	//std::cout << myTree.postorderTraverse(visitNode);
	CHECK(str1.compare(myTree.postorderTraverse(visitNode)) == 0);

	std::string str2 = "0100001:1\n0101:2\n01:2\n0:12\n1011110:15\n1011111:16\n101:1\n11:3\n:0\n";
	CHECK(str2.compare(myTree.postorderTraverse(visitRoutingEntry)) == 0);

}


TEST_CASE("Test searching for port number based on IP address", "[search]") {
	using Catch::Matchers::Contains;
	prefixTree myTree1;

	CHECK(myTree1.findPort("01100110011001100110011001100110") == -1);


	REQUIRE(myTree1.add("0", 1) == true);
	REQUIRE(myTree1.add("011", 2) == true);


	CHECK(myTree1.findPort("01100110011001100110011001100110") == 2);
	CHECK(myTree1.findPort("11100110011001100110011001100110") == -1);

	prefixTree myTree("./routing_table.txt");
	CHECK(myTree.findPort("01100110011001100110011001100110") == 2);
	CHECK(myTree.findPort("11100110011001100110011001100110") == 3);





}

TEST_CASE("Test searching for routing entry based on network id", "[search]") {
	using Catch::Matchers::Contains;
	prefixTree myTree;

	REQUIRE(myTree.add("", 0) == true);
	REQUIRE(myTree.add("0", 1) == true);
	REQUIRE(myTree.add("011", 2) == true);
	REQUIRE(myTree.add("1", 3) == true);

	CHECK(myTree.getRoutingEntry("0").netId == "0");
	CHECK(myTree.getRoutingEntry("0").port == 1);

	try {
		myTree.getRoutingEntry("00");
		CHECK(false);
	}
	catch (TargetNotFoundException& e) {
		std::string str = e.what();
		REQUIRE_THAT(str, Contains("Target not found:"));
	}


	myTree.clear();
	REQUIRE(myTree.add("0", 1) == true);
	REQUIRE(myTree.add("011", 2) == true);
	try {
		myTree.getRoutingEntry("1");
		CHECK(false);
	}
	catch (TargetNotFoundException& e) {
		std::string str = e.what();
		REQUIRE_THAT(str, Contains("Target not found:"));
	}


}


TEST_CASE("Test clear the prefix tree", "[clear]") {



	prefixTree myTree;
	REQUIRE(myTree.add("", 0) == true);
	REQUIRE(myTree.add("0", 1) == true);
	REQUIRE(myTree.add("011", 2) == true);
	REQUIRE(myTree.add("1", 3) == true);
	REQUIRE(myTree.add("0001", 4) == true);

	REQUIRE(myTree.getHeight() == 3);
	REQUIRE(myTree.getNumberOfNodes() == 5);

	myTree.clear();

	REQUIRE(myTree.getHeight() == 0);
	REQUIRE(myTree.getNumberOfNodes() == 0);

	CHECK(myTree.isEmpty() == true);


}

