

#ifndef TREE_NODE_
#define TREE_NODE_

#include <string>
#include <memory>

struct RoutingEntry {
	std::string  netId;       //network id    
	int port;  // port number 
};

class treeNode
{
private:
   RoutingEntry rtEntry; //routing entry 
   std::shared_ptr<treeNode> leftChildPtr;  // Pointer to left child
   std::shared_ptr<treeNode> rightChildPtr; // Pointer to right child
   
public:

	//constructor that creates a new TreeNode where the network id is "" and the port number is -1; The leftChildPtr and rightChildPtr need to be initialized to nullptr.
   treeNode(); // constructor

   //parameterized constructor that initializes the routing entry based on the parameters passed to the constructor.   The leftChildPtr and rightChildPtr need to be initialized to nullptr.
   treeNode(const std::string netId_in, int port_in); 

   //set the netId field of the routing entry to netId_in
   void setNetId(const std::string netId_in);


   //set the port field of the routing entry to port_in
   void setPort(const int port_in);


   //returns the netId the routing entry 
   std::string getNetId() const;

   //returns the port field of the routing entry
   int getPort() const;

   //return the routing entry stored in this treeNode
   RoutingEntry getRoutingEntry() const;

   //check if the node is a leaf node
   bool isLeaf() const;
   
   //return the leftChildPtr of  of this treeNode object
   std::shared_ptr<treeNode>  getLeftChildPtr() const;

   //return the rightChildPtr of  of this treeNode object
   std::shared_ptr<treeNode>  getRightChildPtr() const;
   

   //set the leftChildPtr of  of this treeNode object to leftPtr
   void setLeftChildPtr(std::shared_ptr<treeNode> leftPtr);

   //set the rightChildPtr of  of this treeNode object to rightPtr
   void setRightChildPtr(std::shared_ptr<treeNode> rightPtr);
}; // end treeNodeNode

#endif 
