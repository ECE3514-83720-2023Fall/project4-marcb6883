
#ifndef PREFIX_TREE_
#define PREFIX_TREE_

#include "treeNode.h"
#include <memory>
#include <stdexcept>
#include <string>


class TargetNotFoundException : public std::exception
{
	std::string msg;
public:
	TargetNotFoundException(const std::string& message = "") : std::exception()
	{
		msg = "Target not found: " + message;

	} // end constructor
	const char* what() { return msg.c_str(); }
}; // end TargetNotFoundException





class prefixTree
{
private:
   std::shared_ptr<treeNode> rootPtr; // root pointer to the root of the prefix tree
   
protected:
   //------------------------------------------------------------
   // Protected Utility Methods Section:
   // Recursive helper methods for the public methods. 
   //These are just suggested helper methods. You may delete them and define and implement your own helper methods.
   // The autograder will not call these methods directly. Hence, you are free to develop any protected methods as you like.
   //------------------------------------------------------------
   int getHeightHelper(std::shared_ptr<treeNode> subTreePtr) const;
   
   int getNumberOfNodesHelper(std::shared_ptr<treeNode> subTreePtr) const;
 
   
  std::string postorderTraverseHelper(std::string visit(std::shared_ptr<treeNode> NodePtr), std::shared_ptr<treeNode> treePtr) const;

   
public:
	//All the public methods listed in the starter code must be implemented by you.  
	// You must not change the definitions of these public methods. 
	
	//------------------------------------------------------------
   // Constructor and Destructor Section.
   //------------------------------------------------------------

   //Constructor function, creating an empty prefixTree
   prefixTree();

   //Constructor function, creating a prefixTree based on the routing table information in the provided textfile name "filename"
   prefixTree(std::string filename);

   
   //destructor function. Deallocate all memory allocated to the prefix Tree
   virtual ~prefixTree();
   
   //------------------------------------------------------------
   // Public prefixTree Interface Methods Section.
   //------------------------------------------------------------
   
   //return true if the prefixTree is empty
   bool isEmpty() const;

   //return the height of the prefix tree
   int getHeight() const;

   //return the number of nodes in the prefix tree
   int getNumberOfNodes() const;
   

   // Add a new routing entry (netid, port) to the prefixTree.  
   //Return true if the addition is successful.
	//If a node with the same netid already exists in the prefixTree, 
   // update the port field of routing entry and return true;
   bool add(const std::string netid, const  int port); 
   
  // Given an IP address ipaddr, search the prefixTree to find the valid routing 
   //entry whose network id is the longest matching prefix of the ipaddr.  
   //Return the corresponding port value in the routing entry.
   //If the method cannot find such a routing entry, return -1.
  //Notice that invalid routing entry (i.e. rtEntry.port<0) should not be considered 
   //for longest prefix matching
   int findPort(std::string ipaddr) const;


   // Removes the targeted routing entry from the prefixTree.  
   //The routing entry's network id netid is given.
   //Return true if the removal is successful.  Return false otherwise.

  bool remove(const std::string netId); 

  //deallocate the memory allocated to the prefixTree. Reset the tree to an empty tree;
  void clear();
   
  
  // Search the prefixTree to find a valid routing entry with the target network id (netId) 
  //If the routing entry is found, return the routing entry value 
  // If the routing entry cannot be found, throw TargetNotFoundException;

  RoutingEntry getRoutingEntry(const std::string netId) const;


  //Traverse the prefixTree using postorder traveral method.  For every node it visit, let the 
  //function visit process the node. The function visit is a user defined function that is
  //passed as a parameter to this function.
  std::string postorderTraverse(std::string visit(std::shared_ptr<treeNode> NodePtr)) const;

}; 


#endif

