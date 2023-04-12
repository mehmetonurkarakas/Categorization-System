#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
using namespace std;


struct secondaryNode
{
    string data;
    string type;
    secondaryNode *leftNode = NULL;
    secondaryNode *rightNode = NULL;
    int height;
    bool color;

};

struct primaryNode{
    string category;
    secondaryNode *secondaryPointer = NULL;
    primaryNode *leftNode = NULL;
    primaryNode *rightNode = NULL;
};

int height(secondaryNode *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

secondaryNode *rightRotate(secondaryNode *y)
{
    secondaryNode *x = y->leftNode;
    secondaryNode *T2 = x->rightNode;
 
    x->rightNode = y;
    y->leftNode = T2;
    //change heights and update
    y->height = max(height(y->leftNode),
                    height(y->rightNode)) + 1;
    x->height = max(height(x->leftNode),
                    height(x->rightNode)) + 1;
 
    return x;
    // root node
}
// rotate for balance
secondaryNode *leftRotate(secondaryNode *x)
{
    secondaryNode *y = x->rightNode;
    secondaryNode *T2 = y->leftNode;
 
    y->leftNode = x;
    x->rightNode = T2;
 
    //again updating heights
    x->height = max(height(x->leftNode),   
                    height(x->rightNode)) + 1;
    y->height = max(height(y->leftNode),
                    height(y->rightNode)) + 1;
 
    return y;
    // again return with root node
}
 
// I check heights of nodes
int getBalance(secondaryNode *N)
{
    if (N == NULL)
        return 0;
    return height(N->leftNode) - height(N->rightNode);
}
 
// insert secondary node(AVL TREE)
secondaryNode* insertSec(secondaryNode* node, vector<string>commands)
{
    if (node == NULL){// If node is null creating new node
      secondaryNode *newnode = new secondaryNode;
      newnode->data = commands[3];
      newnode->height = 1;
      newnode->type = commands[2];
      return newnode;
    }

    if (commands[2] < node->type&&commands[2]!= node->type)
        node->leftNode = insertSec(node->leftNode,commands);

    else if (commands[2]!= node->type)
        node->rightNode = insertSec(node->rightNode, commands);

    else 
        return node;
 
    
    node->height = 1 + max(height(node->leftNode),// Update height of node
                        height(node->rightNode));
 

    int balance = getBalance(node);// I check balance factor If not balanced gonna do rotate 4 type
 

    if (balance > 1 && commands[2] < node->leftNode->type)// Left Left situation
        return rightRotate(node);
 
    
    if (balance < -1 && commands[2] > node->rightNode->type)// Right Right situation
        return leftRotate(node);
 
    
    if (balance > 1 && commands[2] > node->leftNode->type)//Left Right situation
    {
        node->leftNode = leftRotate(node->leftNode);
        return rightRotate(node);
    }
 
    
    if (balance < -1 && commands[2] < node->rightNode->type)//Right Left sitation
    {
        node->rightNode = rightRotate(node->rightNode);
        return leftRotate(node);
    }
 
    return node;
}
// Insert main tree(Binary Search Tree)
primaryNode* insert(primaryNode* root, vector<string>commands) {
        if(root == NULL){// If root is null create new node
            primaryNode *prim = new primaryNode;
            prim->category = commands[1];
            prim->secondaryPointer = insertSec(prim->secondaryPointer,commands);
            return prim;
        }

     else{// If not null traverse tree
            primaryNode* cur;
            if(commands[1] <= root->category) {
                cur = insert(root->leftNode, commands);
                root->leftNode = cur;
            }
            else {
                cur = insert(root->rightNode, commands);
                root->rightNode = cur;
            }
        return root;// return root node
     }
   }
// My search function for secondary tree(AVL Tree)
secondaryNode* searchSec(secondaryNode* root, vector<string>commands) {
        if(root == NULL || root->type == commands[2])   // If this root null or equals what we want, return this node     
            return root;

        //  lexicographical ordering 
        if(root->type < commands[2]) 
            return searchSec(root->rightNode,commands);

        // lexicographical ordering 
        return searchSec(root->leftNode,commands);
     }
// My search function for primary tree(Binary Seatch Tree)
primaryNode* search(primaryNode* root, vector<string>commands) {
        if(root == NULL || root->category == commands[1])        
            return root;

        //  lexicographical ordering 
        if(root->category < commands[1]) 
            return search(root->rightNode,commands);

        //  lexicographical ordering 
        return search(root->leftNode,commands);
     }

// This method prints level by level AVL Tree
void printLevelOrderAVL(secondaryNode* root,string output1)
{
    ofstream outputfile;
    outputfile.open(output1.c_str(),ios::app);
    // Base Case
    if (root == NULL)
        return;
 
    queue<secondaryNode*> q;// For printing create queue
    q.push(root);
 
    while (q.empty() == false) {// Add node to queue after dequque all elements

        int nodeCount = q.size();

        int k = 0;
        while (nodeCount > 0) {
            secondaryNode* node = q.front();
            
            if (k==0)// For comma situation
            {
                k++;
                outputfile <<"\t"<<"\""<< node->type << "\":\"" << node->data << "\"";
            }
            else{
                outputfile <<",\""<< node->type << "\":\"" << node->data << "\"";
            }
            
            
            q.pop();
            if (node->leftNode != NULL)
                q.push(node->leftNode);
            if (node->rightNode != NULL)
                q.push(node->rightNode);
            nodeCount--;
        }
        outputfile << endl;
    }
}

// This method prints level by level Red Black Tree
void printLevelOrderLLRBT(secondaryNode* root,string output2)// Same as upper method
{
    ofstream outputfile2;
    outputfile2.open(output2.c_str(),ios::app);
    
    if (root == NULL)// Base case
        return;
 
    queue<secondaryNode*> q;
    q.push(root);
 
    while (q.empty() == false) {

        int nodeCount = q.size();

        int k = 0;
        while (nodeCount > 0) {
            secondaryNode* node = q.front();
            
            if (k==0)
            {
                k++;
                outputfile2 <<"\t"<<"\""<< node->type << "\":\"" << node->data << "\"";
            }
            else{
                outputfile2 <<",\""<< node->type << "\":\"" << node->data << "\"";
            }
            
            
            q.pop();
            if (node->leftNode != NULL)
                q.push(node->leftNode);
            if (node->rightNode != NULL)
                q.push(node->rightNode);
            nodeCount--;
        }
        outputfile2 << endl;
    }
}
// This method prints level by level Binary Search Tree for part1
void printLevelOrderPARTONE(primaryNode* root,string output1)// Same as upper method
{
    ofstream outputfile;
    outputfile.open(output1.c_str(),ios::app);
    // Base Case
    if (root == NULL)
        return;
 
    queue<primaryNode*> q;
    q.push(root);
 
    while (q.empty() == false) {

        int nodeCount = q.size();

        while (nodeCount > 0) {
            primaryNode* node = q.front();
            if (node->secondaryPointer==NULL)
            {
                outputfile <<"\""<< node->category << "\":"<<"{}" <<  endl;
            }
            else{
                outputfile <<"\""<< node->category << "\":"<< endl;
                printLevelOrderAVL(node->secondaryPointer,output1);
            }
            
            
            q.pop();
            if (node->leftNode != NULL)
                q.push(node->leftNode);
            if (node->rightNode != NULL)
                q.push(node->rightNode);
            nodeCount--;
        }
    }
}
// This method prints level by level Binary Search Tree for part2
void printLevelOrderPARTTWO(primaryNode* root,string output2)
{
    ofstream outputfile2;
    outputfile2.open(output2.c_str(),ios::app);
    if (root == NULL)
        return;
 
    queue<primaryNode*> q;
    q.push(root);
 
    while (q.empty() == false) {

        int nodeCount = q.size();
 

        while (nodeCount > 0) {
            primaryNode* node = q.front();
            if (node->secondaryPointer==NULL)
            {
                outputfile2 <<"\""<< node->category << "\":"<<"{}" <<  endl;
            }
            else{
                outputfile2 <<"\""<< node->category << "\":"<< endl;
                printLevelOrderLLRBT(node->secondaryPointer,output2);
            }
            
            
            q.pop();
            if (node->leftNode != NULL)
                q.push(node->leftNode);
            if (node->rightNode != NULL)
                q.push(node->rightNode);
            nodeCount--;
        }
    }
}

secondaryNode * minValueNode(secondaryNode* node) 
{ 
    secondaryNode* current = node; 
    // find smallest leaf
    while (current->leftNode != NULL) 
        current = current->leftNode; 
  
    return current; 
} 

secondaryNode* deleteNode(secondaryNode* root, vector<string> commands) // delete method
{ 
      
    if (root == NULL) // Base Case
        return root; 
  
            // lexicographical ordering 
    if ( commands[2] < root->type) 
        root->leftNode = deleteNode(root->leftNode, commands); 
  
        // lexicographical ordering  
    else if( commands[2] > root->type ) 
        root->rightNode = deleteNode(root->rightNode, commands); 
  
    // if key is same as root's key, then 
    // This is the node to be deleted 
    else
    { 
        // node with only one child or no child 
        if( (root->leftNode == NULL) ||
            (root->rightNode == NULL) ) 
        { 
            secondaryNode *temp = root->leftNode ? 
                         root->leftNode: 
                         root->rightNode; 
  
            // No child case 
            if (temp == NULL) 
            { 
                temp = root; 
                root = NULL; 
            } 
            else // One child case 
            *root = *temp; // Copy the contents of 
                           // the non-empty child 
            
            delete temp;
            
        } 
        else
        { 
            // node with two children: Get the inorder 
            // successor (smallest in the right subtree) 
            secondaryNode* temp = minValueNode(root->rightNode); 
  
            // Copy the inorder successor's 
            // data to this node 
            root->type = temp->type; 
  
            // Delete the inorder successor 
            root->rightNode = deleteNode(root->rightNode, 
                                     commands); 
        } 
    } 
  
    // If the tree had only one node
    // then return 
    if (root == NULL) 
    return root; 
  
    // UPDATE HEIGHT OF THE CURRENT NODE 
    root->height = 1 + max(height(root->leftNode), 
                           height(root->rightNode)); 
  
    // Chechk balance factor
    int balance = getBalance(root); 
  
    // If this node becomes unbalanced, 
    // then there are 4 cases 
  
    // Left Left Case 
    if (balance > 1 && 
        getBalance(root->leftNode) >= 0) 
        return rightRotate(root); 
  
    // Left Right Case 
    if (balance > 1 && 
        getBalance(root->leftNode) < 0) 
    { 
        root->leftNode = leftRotate(root->leftNode); 
        return rightRotate(root); 
    } 
  
    // Right Right Case 
    if (balance < -1 && 
        getBalance(root->rightNode) <= 0) 
        return leftRotate(root); 
  
    // Right Left Case 
    if (balance < -1 && 
        getBalance(root->rightNode) > 0) 
    { 
        root->rightNode = rightRotate(root->rightNode); 
        return leftRotate(root); 
    } 
  
    return root; 
} 

// part 2 codes ######################################
secondaryNode* rotateLeft(secondaryNode* myNode)
{
    secondaryNode *child = myNode -> rightNode;
    secondaryNode *childLeft = child -> leftNode;
 
    child -> leftNode = myNode;
    myNode -> rightNode = childLeft;
 
    return child;
}
 
// Rotate function for LLRBT
secondaryNode* rotateRight(secondaryNode* myNode)
{
    secondaryNode *child = myNode -> leftNode;
    secondaryNode *childRight =  child -> rightNode;
 
    child -> rightNode = myNode;
    myNode -> leftNode = childRight;
     
    return child;
}
 
// Control function to check whether secondaryNode is red in color or not.
int isRed(secondaryNode *myNode)
{
    if (myNode == NULL)
       return 0;
        
    return (myNode -> color == true);
}
 
//Swap colors for balance
void swapColors(secondaryNode *node1, secondaryNode *node2)
{
    bool temp = node1 -> color;
    node1 -> color = node2 -> color;
    node2 -> color = temp;
}
 
// Insertion into Left Leaning Red Black Tree.
secondaryNode* insertRed(secondaryNode* myNode, vector<string> commands)
{
    if (myNode == NULL){// Base case if node is null create new node
        secondaryNode *myNode = new secondaryNode();
        myNode -> leftNode = myNode -> rightNode = NULL;
        myNode ->type = commands[2];
        myNode->data = commands[3];
 
//new node is red(true)
        myNode -> color = true;
    return myNode;
    }
        
 
    if (commands[2] < myNode -> type)
        myNode -> leftNode = insertRed(myNode -> leftNode, commands);
 
    else if (commands[2] > myNode -> type)
        myNode -> rightNode = insertRed(myNode -> rightNode, commands);
 
    else   
        return myNode;
         
    // when rightNode child is Red but leftNode child is Black or doesn't exist.
    if (isRed(myNode -> rightNode) &&
       !isRed(myNode -> leftNode))
    {
         
        // Left rotate the secondaryNode to make it into valid structure.
        myNode = rotateLeft(myNode);
 
        // Swap the colors as the child secondaryNode should always be red
        swapColors(myNode, myNode -> leftNode);
    }
     
    // when leftNode child as well as leftNode grand child in Red
    if (isRed(myNode -> leftNode) &&
        isRed(myNode -> leftNode -> leftNode))
    {  
         
        // Right rotate the current secondaryNode to make it into a valid structure.
        myNode = rotateRight(myNode);
        swapColors(myNode, myNode -> rightNode);
    }
     
    // when both leftNode and rightNode child are Red in color.
    if (isRed(myNode -> leftNode) && isRed(myNode -> rightNode))
    {
         
        // Invert the color of secondaryNode as well
        // it's leftNode and rightNode child.
        myNode -> color = !myNode -> color;
 
        // Change the color to black.
        myNode -> leftNode -> color = false;
        myNode -> rightNode -> color = false;
    }
    return myNode;
}

//DELETIONN

secondaryNode* deletion(secondaryNode* root, vector<string>commands)
{
    // Search for the secondaryNode to be deleted
    if (root == NULL)
        return NULL;
    if (commands[2] < root->type)
        root->leftNode = deletion(root->leftNode, commands);
    else if (commands[2] > root->type)
        root->rightNode = deletion(root->rightNode, commands);
    else // found the secondaryNode to be deleted
    {
        // case 1: secondaryNode has no children or only one child
        if (root->leftNode == NULL || root->rightNode == NULL)
        {
            secondaryNode* child = (root->leftNode == NULL) ? root->rightNode : root->leftNode;
            if (child != NULL)
                child->color = root->color;
            return child;
        }
        // case 2: secondaryNode has two child
        else
        {
            // Find the successor of the secondaryNode (next largest value)
            secondaryNode* successor = root->rightNode;
            while (successor->leftNode != NULL)
                successor = successor->leftNode;
            // Replace the value of the secondaryNode to be deleted with the value of the successor
            root->data = successor->data;
            // Delete the successor secondaryNode, which will have at most one child
            root->rightNode = deletion(root->rightNode, commands);
        }
    }

    // After deletion operation, check if the tree is still a leftNode-leaning red-black tree
    // If not, fix any violations of the leftNode-leaning red-black tree properties
    // by performing rotations and color swaps
    if (isRed(root->rightNode) && !isRed(root->leftNode))
        root = rotateLeft(root);
    if (isRed(root->leftNode) && isRed(root->leftNode->leftNode))
        root = rotateRight(root);
    if (isRed(root->leftNode) && isRed(root->rightNode))
    {
        root->color = !root->color;
        root->leftNode->color = false;
        root->rightNode->color = false;
    }

    return root;
}




void fileOperationSec(string file2,string output2){// split input file and put into tokens vector and control first element 
    ifstream file;
    file.open(file2.c_str());
    ofstream outputfile2;
    outputfile2.open(output2.c_str(),ios::app);
    string line;
    primaryNode *root = NULL;
    while(getline(file, line)) {     // '\n' is the default delimiter
        vector<string> tokens;
        istringstream iss(line);
        string token;
        while(getline(iss, token, '\t')) {
            tokens.push_back(token);
        }
        if (tokens[0]=="insert")//search for first input node if it's null add bst and LLRBT if not null just insert secondary node
        { 
          primaryNode *temp = NULL;
          temp = search(root,tokens);    
          if (temp==NULL)
          {
            root = insert(root,tokens);
          }
          else{
            temp->secondaryPointer = insertRed(temp->secondaryPointer,tokens);
          }
        }
        else if (tokens[0]=="printAllItems")
        {
            outputfile2 << "command:printAllItems"<< endl << "{" << endl;
            printLevelOrderPARTTWO(root,output2);
            outputfile2 << "}" << endl;
        }
        else if (tokens[0]== "updateData")// find first,second node and update
        {
            primaryNode * tempr = NULL;
            tempr = search(root,tokens);
            secondaryNode *tempSec = NULL;
            tempSec = searchSec(tempr->secondaryPointer,tokens);
            tempSec->data = tokens[3]; 
        }
        else if (tokens[0]== "printItem")
        {
            primaryNode * tempr = NULL;
            tempr = search(root,tokens);
            secondaryNode *tempSec = NULL;
            tempSec = searchSec(tempr->secondaryPointer,tokens);
            if (tempSec==NULL)
            {
                outputfile2 << "command:printItem\t"<< tokens[1] << "\t"<< tokens[2] << endl << "{}" << endl;
            }
            else{
                 outputfile2 << "command:printItem\t"	<< tokens[1] << "\t" << tokens[2] << endl << "{" << endl << "\"" << tokens[1] << "\":" << endl;
                outputfile2 << "\t\"" << tokens[2] << "\":\"" << tempSec->data << "\"" << endl;
                outputfile2 << "}" << endl;
            }
            
        }
        else if (tokens[0] == "remove")// first find true node after that delete this
        {
            primaryNode *tempprim = NULL;
            tempprim = search(root,tokens);
            tempprim->secondaryPointer = deletion(tempprim->secondaryPointer,tokens);
        }
        else if(tokens[0] == "printAllItemsInCategory")
        {
            outputfile2 << "command:printAllItemsInCategory\t"<< tokens[1]<<endl << "{" << endl;
            primaryNode * temp = NULL;
            temp = search(root,tokens);
            if (temp->secondaryPointer==NULL)
            {
                outputfile2 << "\"" << tokens[1] <<"\":" <<"{}"<< endl;
            }
            else{
                outputfile2 << "\"" << tokens[1] <<"\":" << endl;
                printLevelOrderLLRBT(temp->secondaryPointer,output2);
            }
            
            
            outputfile2 << "}" << endl;
        }
        else if (tokens[0] == "find")
        {
            primaryNode * temp = NULL;
            temp = search(root,tokens);

            if (temp ==NULL)
            {
                outputfile2 << "command:find\t"<< tokens[1] << "\t"<< tokens[2] << endl << "{}" << endl;
            }
            else{
                secondaryNode *tempSec = NULL;
                tempSec = searchSec(temp->secondaryPointer,tokens);
                if (tempSec==NULL)
                {
                    outputfile2 << "command:find\t"<< tokens[1] << "\t"<< tokens[2] << endl << "{}" << endl;
                }
                else{
                    outputfile2 << "command:find\t"<< tokens[1] << "\t"<< tokens[2] << endl << "{" << endl<< "\""<<tokens[1] << "\":" << endl;
                    printLevelOrderLLRBT(tempSec,output2);
                    outputfile2 << "}" << endl;
                }
            }
            
            
        }
    }

}
void fileOperation(string file1,string output1){// split input file and put into tokens vector and control first element 
    ifstream file;
    file.open(file1.c_str());
    ofstream outputfile;
    outputfile.open(output1.c_str(),ios::app);
    string line;
    primaryNode *root = NULL;
    while(getline(file, line)) {     // '\n' is the default delimiter
        vector<string> tokens;
        istringstream iss(line);
        string token;
        while(getline(iss, token, '\t')) {
            tokens.push_back(token);
        }
        if (tokens[0]=="insert")//search for first input node if it's null add bst and AVL if not null just insert secondary node
        { 
          primaryNode *temp = NULL;
          temp = search(root,tokens);   
          if (temp==NULL)
          {
            root = insert(root,tokens);
          }
          else{
            temp->secondaryPointer = insertSec(temp->secondaryPointer,tokens);
          }
        }
        else if (tokens[0]=="printAllItems")
        { 
            outputfile << "command:printAllItems"<< endl << "{" << endl;
            printLevelOrderPARTONE(root,output1);
            outputfile << "}" << endl;

        }
        else if (tokens[0]== "updateData")// find first,second node and update
        {

            primaryNode * tempr = NULL;
            tempr = search(root,tokens);
            secondaryNode *tempSec = NULL;
            tempSec = searchSec(tempr->secondaryPointer,tokens);
            tempSec->data = tokens[3]; 

        }
        else if (tokens[0]== "printItem")
        {

            primaryNode * tempr = NULL;
            tempr = search(root,tokens);
            secondaryNode *tempSec = NULL;
            tempSec = searchSec(tempr->secondaryPointer,tokens);
            if (tempSec==NULL)
            {
                outputfile << "command:printItem\t"<< tokens[1] << "\t"<< tokens[2] << endl << "{}" << endl;
            }
            else{
                 outputfile << "command:printItem\t"	<< tokens[1] << "\t" << tokens[2] << endl << "{" << endl << "\"" << tokens[1] << "\":" << endl;
                outputfile << "\t\"" << tokens[2] << "\":\"" << tempSec->data << "\"" << endl;
                outputfile << "}" << endl;
            }

            
        }
        else if (tokens[0] == "remove")// first find true node after that delete this
        {
            primaryNode *tempprim = NULL;
            tempprim = search(root,tokens);
            tempprim->secondaryPointer = deleteNode(tempprim->secondaryPointer,tokens);

        }
        else if(tokens[0] == "printAllItemsInCategory")
        {

            outputfile << "command:printAllItemsInCategory\t"<< tokens[1]<<endl << "{" << endl;
            primaryNode * temp = NULL;
            temp = search(root,tokens);
            if (temp->secondaryPointer==NULL)
            {
                outputfile << "\"" << tokens[1] <<"\":" <<"{}"<< endl;
            }
            else{
                outputfile << "\"" << tokens[1] <<"\":" << endl;
                printLevelOrderAVL(temp->secondaryPointer,output1);
            }
            
            
            outputfile << "}" << endl;
            
        }
        else if (tokens[0] == "find")
        {

            primaryNode * temp = NULL;
            temp = search(root,tokens);
            if (temp ==NULL)
            {
                outputfile << "command:find\t"<< tokens[1] << "\t"<< tokens[2] << endl << "{}" << endl;
            }
            else{
                secondaryNode *tempSec = NULL;
                tempSec = searchSec(temp->secondaryPointer,tokens);

                if (tempSec==NULL)
                {
                    outputfile << "command:find\t"<< tokens[1] << "\t"<< tokens[2] << endl << "{}" << endl;
                }
                else{
                    outputfile << "command:find\t"<< tokens[1] << "\t"<< tokens[2] << endl << "{" << endl<< "\""<<tokens[1] << "\":" << endl;
                    printLevelOrderAVL(tempSec,output1);
                    outputfile << "}" << endl;
                }
            }
            
            

        }
    }
}

int main(int argc, char* argv[]){ 
    string file = argv[1];
    string output1 = argv[2];
    string output2 = argv[3];

    fileOperation(file,output1);//Part1
    fileOperationSec(file,output2);//Part2

    
    return 0;
}