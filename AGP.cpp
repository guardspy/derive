#pragma once
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include "DOMTree.h"

using namespace std;

int main(void)
{
	DOMTree DOM = DOMTree();
	stack<string> HTMLTags;   //HTML 태그들을 저장하는 스택
	string tagString;   //HTML 태그
	int DOMDepth = 0;
	string input_eff = string("");
	string line;
	int line_len;
	vector<HTMLTagNode*>* tagList = new vector<HTMLTagNode*>;
	vector<HTMLTagNode*> tagDir;
	HTMLTagNode* prev;
	int request;
	string tagName = string("");
	int order;

	//HTML 코드 공백 제거
	do
	{
		getline(cin, line);
		line_len = line.length();
		for (int i = 0; i < line_len; i++)
		{
			if (line[i] == '\t' || line[i] == '\n')
			{
				line.erase(line.begin() + i);
				i--;
				line_len--;
			}
		}

		input_eff += line;
	} while (!line.empty());
	//cout << input_eff;

	for (int i = 0; i < input_eff.length();)
	{
		tagString = string("");
		switch (input_eff[i])
		{
		case '<':
			while (input_eff[i] != '>')
			{
				if (i == input_eff.length())
				{
					cout << "Error Code 3: Invalid Input" << endl;
					goto exit;
				}
				tagString += input_eff[i];
				i++;
			}
			tagString += '>';
			i++;
			break;
		default:
			while (input_eff[i] != '<')
			{
				if (i == input_eff.length())
				{
					cout << "Error Code 3: Invalid Input" << endl;
					goto exit;
				}
				tagString += input_eff[i];
				i++;
			}
			break;
		}

		if (HTMLTags.empty())
		{
			DOM.append(new HTMLTagNode(tagString));
			HTMLTags.push(tagString);
		}
		else
		{
			if (tagString[0] == '<')
			{
				if (tagString[1] == '/')   //</?>꼴
				{
					string par = HTMLTags.top();
					string text = string("");
					if (par[0] != '<')
					{
						text = par;
						HTMLTags.pop();
						par = HTMLTags.top();
					}

					//</?> 꼴의 태그를 <?> 꼴의 태그로 변환
					string tag_origin = string("");
					tag_origin += tagString[0];
					tag_origin += string(tagString.begin() + 2, tagString.end());

					if (tag_origin == par)
					{
						DOM.indicator->textContent = text;
						if (DOM.indicator!=DOM.root) DOM.parentNode();
						HTMLTags.pop();
					}
					else
					{
						cout << "Error Code 3: Invalid Input" << endl;
						goto exit;
					}
				}
				else   //<?>꼴
				{
					DOM.append(new HTMLTagNode(tagString));
					HTMLTags.push(tagString);
				}
			}
			else   //문자열
			{
				HTMLTags.push(tagString);
			}
		}
	}
	if (!HTMLTags.empty())
	{
		cout << "Error Code 3: Invalid Input" << endl;
		goto exit;
	}
	DOM.indicator = DOM.root;

	do
	{
		cout << "-------------------------------------" << endl;
		DOM.printDOM_preorder(DOM.root, 0, DOM.indicator);
		cout << "Get Elements By Tag Name: 1\nMove To Parent Node: 2\nMove To First Child: 3\nMove To Last Child: 4\nMove To Previous Sibling: 5\nMove To Next Sibling: 6\nGet Text Content: 7\nExit: 0\n";
		cin >> request;

		switch (request)
		{
		case 1: 
			cin >> tagName;
			DOM.getElementsByTagName(tagName, DOM.root, tagList);
			for (int i = 0; i < tagList->size(); i++)
			{
				tagDir.clear();
				prev = (*tagList)[i];
				while (prev != DOM.root)
				{
					prev = prev->parent;
					tagDir.push_back(prev);
				}
				for (int i = tagDir.size() - 1; i >= 0; i--) cout << tagDir[i]->tagName << "-";
				cout << (*tagList)[i]->tagName << ": ";
			cout << (i + 1) << endl;
			}
			cin >> order;
			DOM.indicator = (*tagList)[order - 1];
			break;
		case 2:
			DOM.parentNode();
			break;
		case 3:
			DOM.firstChild();
			break;
		case 4:
			DOM.lastChild();
			break;
		case 5:
			DOM.previousSibling();
			break;
		case 6:
			DOM.nextSibling();
			break;
		case 7:
			cout << DOM.indicator->textContent << endl;
			break;
		default:
			break;
		};

	} while (request != 0);

	return 0;

exit:
	return ERRORCODE3;
}