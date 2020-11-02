#include "DOMTree.h"

using namespace std;

HTMLTagNode::HTMLTagNode(){}
HTMLTagNode::HTMLTagNode(string name)
{
	this->tagName = name;
}

void DOMTree::setRoot(HTMLTagNode* node)
{
	root = node;
	indicator = root;
	size++;
}
void DOMTree::append(HTMLTagNode* node)
{
	if (size == 0) setRoot(node);
	else
	{
		node->parent = indicator;
		indicator->children.push_back(node);
		indicator = node;
		size++;
	}
}
int DOMTree::moveTo(HTMLTagNode* node, HTMLTagNode* origin)
{
	if (node == NULL)
	{
		cout << "Error Code 1: No such tag" << endl;
		indicator = origin;
		return ERRORCODE1;
	}
	else
	{
		indicator = node;
		return OK;
	}
}
void DOMTree::getElementsByTagName(string tagName, HTMLTagNode* now, vector<HTMLTagNode*>* elements)   //TODO 잘 구현했나..?확인 필요
{
	if (tagName == now->tagName) elements->push_back(now);
	for (HTMLTagNode* child : now->children) getElementsByTagName(tagName, child, elements);
}
int DOMTree::parentNode(void)
{
	return moveTo(indicator->parent, indicator);
}
int DOMTree::firstChild(void)
{
	return moveTo(indicator->children[0], indicator);
}
int DOMTree::lastChild(void)
{
	return moveTo(indicator->children[indicator->children.size() - 1], indicator);
}
int DOMTree::previousSibling(void)
{
	HTMLTagNode* self = indicator;
	int selfi;
	if (parentNode() == OK)
	{
		for (int i = 0; i < indicator->children.size(); i++)
		{
			if (indicator->children[i] == self)
				selfi = i;
		}
		if (selfi == 0)
		{
			cout << "Error Code 1: No such tag" << endl;
			indicator = self;
			return ERRORCODE1;
		}
		else return moveTo(indicator->children[selfi - 1], self);
	}
	else
	{
		cout << "Error Code 2: No parent" << endl;
		indicator = self;
		return ERRORCODE2;
	}
}
int DOMTree::nextSibling(void)
{
	HTMLTagNode* self = indicator;
	int selfi;
	if (parentNode() == OK)
	{
		for (int i = 0; i < indicator->children.size(); i++)
		{
			if (indicator->children[i] == self)
				selfi = i;
		}
		if (selfi == indicator->children.size() - 1)
		{
			cout << "Error Code 1: No such tag" << endl;
			indicator = self;
			return ERRORCODE1;
		}
		else return moveTo(indicator->children[selfi + 1], self);
	}
	else
	{
		cout << "Error Code 2: No parent" << endl;
		indicator = self;
		return ERRORCODE2;
	}
}
void DOMTree::printDOM_preorder(HTMLTagNode* now, int depth, HTMLTagNode* target)
{
	for (int i = 0; i < depth; i++) cout << '\t';
	cout << now->tagName;
	cout << (now == target ? "(now)" : "") << endl;
	for (HTMLTagNode* child : now->children) printDOM_preorder(child, depth + 1, target);
}