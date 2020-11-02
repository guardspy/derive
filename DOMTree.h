#ifndef HTMLDOMTREE
#define HTMLDOMTREE
#include <iostream>
#include <string>
#include <vector>
#define OK 0
#define ERRORCODE1 1
#define ERRORCODE2 2
#define ERRORCODE3 3

class HTMLTagNode
{
public:
	std::string tagName;
	HTMLTagNode* parent = NULL;
	std::vector<HTMLTagNode*> children;
	std::string textContent = std::string("");

	HTMLTagNode();
	HTMLTagNode(std::string name);
};

class DOMTree
{
public:
	HTMLTagNode* root = new HTMLTagNode();
	HTMLTagNode* indicator = root;
	int size = 0;
	void setRoot(HTMLTagNode* node);
	void append(HTMLTagNode* node);
	int moveTo(HTMLTagNode* node, HTMLTagNode* origin);
	void getElementsByTagName(std::string tagName, HTMLTagNode* start, std::vector<HTMLTagNode*>* elements);
	int parentNode(void);
	int firstChild(void);
	int lastChild(void);
	int previousSibling(void);
	int nextSibling(void);
	void printDOM_preorder(HTMLTagNode* now, int depth, HTMLTagNode* target);

	DOMTree() {}
};
#endif
