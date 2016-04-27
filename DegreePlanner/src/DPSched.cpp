#include "DPSched.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

ClassTree::ClassTree(){}//ctor

void ClassTree::addClassNode(std::string title, int hours, std::string dept, int courseNumber, std::string satisfies, std::string preReqs, int seats)
{
    ClassNode *classAdd = new ClassNode(title, hours, dept, courseNumber, satisfies, preReqs, seats);
    classAdd->leftChild = NULL;
    classAdd->rightChild = NULL;
    classAdd->parent = NULL;
    ClassNode *tmp = root;
    ClassNode *parent = NULL;

        while (tmp!=NULL)
        {
            parent = tmp;
            if (classAdd->title.compare(tmp->title) < 0)
            {
               tmp = tmp->leftChild;
            }
            else
            {
                tmp = tmp->rightChild;
            }
        }
        if (parent == NULL)
        {
            root = classAdd;
        }
        else if (classAdd->title.compare(parent->title) < 0)
        {
            parent->leftChild = classAdd;
            classAdd->parent = parent;
        }
        else
        {
            parent->rightChild = classAdd;
            classAdd->parent = parent;
        }

}

void ClassTree::numAddClassNode(std::string title, int hours, std::string dept, int courseNumber, std::string satisfies, std::string preReqs, int seats)
{
    ClassNode *classAdd = new ClassNode(title, hours, dept, courseNumber, satisfies, preReqs, seats);
    classAdd->leftChild = NULL;
    classAdd->rightChild = NULL;
    classAdd->parent = NULL;
    ClassNode *tmp = root;
    ClassNode *parent = NULL;

        while (tmp!=NULL)
        {
            parent = tmp;
            if (classAdd->courseNum <tmp->courseNum)
            {
               tmp = tmp->leftChild;
            }
            else
            {
                tmp = tmp->rightChild;
            }
        }
        if (parent == NULL)
        {
            root = classAdd;
        }
        else if (classAdd->courseNum <parent->courseNum)//classAdd->title.compare(parent->title) < 0)
        {
            parent->leftChild = classAdd;
            classAdd->parent = parent;
        }
        else
        {
            parent->rightChild = classAdd;
            classAdd->parent = parent;
        }

}



ClassNode* ClassTree::search(std::string title)
{
    ClassNode *currentRoot = root;
    while (currentRoot != NULL)
    {
        if (currentRoot->title.compare(title) < 0)
        {
            currentRoot = currentRoot->rightChild;
        }
        else if (currentRoot->title.compare(title) > 0)
        {
            currentRoot = currentRoot->leftChild;
        }
        else
        {
            return currentRoot;
        }
    }
        return NULL;
}

void ClassTree::findClass(string title)
{
    ClassNode *foundClass = search(title);
    if (foundClass!=NULL)
    {
    cout << "Class Info:" << endl;
    cout << "===========" << endl;
    cout << "Title:" << foundClass->title << endl;
    cout << "Course ID:" << foundClass->department<<" "<<foundClass->courseNum<< endl;
    cout << "Credit Hours:" << foundClass->credits << endl;
    cout << "Satisfies:" << foundClass->satisfiesTitle << endl;
    cout<< "PreRequisite:"<<foundClass->preReqTitle<<endl;
    }
    else
    {
        cout<<"Class not found."<<endl;
    }
}

ClassNode* ClassTree::searchByNum(int courseNum)
{
    ClassNode *currentRoot = root;
    while (currentRoot != NULL)
    {
        if (currentRoot->courseNum < courseNum)
        {
            currentRoot = currentRoot->rightChild;
        }
        else if (currentRoot->courseNum > courseNum)
        {
            currentRoot = currentRoot->leftChild;
        }
        else
        {
            return currentRoot;
        }
    }
        return NULL;
}

void ClassTree::findClassByNumber(int courseNum)
{
    ClassNode *foundClass = searchByNum(courseNum);
    if (foundClass!=NULL)
    {
    cout << "Class Info:" << endl;
    cout << "===========" << endl;
    cout << "Title:" << foundClass->title << endl;
    cout << "Course ID:" << foundClass->department<<" "<<foundClass->courseNum<< endl;
    cout << "Credit Hours:" << foundClass->credits << endl;
    cout << "Satisfies:" << foundClass->satisfiesTitle << endl;
    cout<< "PreRequisite:"<<foundClass->preReqTitle<<endl;
    }
    else
    {
        cout<<"Class not found."<<endl;
    }
}

void ClassTree::takeClass(string title)
{
    ClassNode *foundClass = search(title);
    if (foundClass==NULL)
    {
        cout << "Class not found." << endl;
    }
    else
    {
        if (foundClass->seats==0)
        {
            cout << "Class full." << endl;
        }
        if (foundClass->seats!=0)
        {
            foundClass->seats = foundClass->seats-1;

            cout << "Class has been added to schedule." << endl;
            cout << "Class Info:" << endl;
            cout << "===========" << endl;
            cout << "Title:" << foundClass->title << endl;
            cout << "Course ID:" << foundClass->department<<" "<<foundClass->courseNum<< endl;
            cout << "Credit Hours:" << foundClass->credits << endl;
            cout << "Satisfies:" << foundClass->satisfiesTitle << endl;
            cout << "PreRequisite:"<<foundClass->preReqTitle<<endl;
        }
    }
}

void ClassTree::printClassInventory(ClassNode *node)
{
    if (node->leftChild!=NULL)
    {
        printClassInventory(node->leftChild);
    }
    cout<<node->department<<" "<<node->courseNum<<": "<<node->title<<": "<<node->credits<<" Hrs; "<<node->seats<<" seats remaining"<<endl;
    if (node->rightChild!=NULL)
    {
        printClassInventory(node->rightChild);
    }
}

void ClassTree::printClassInventory()
{
    ClassTree::printClassInventory(root);
}



ClassNode* ClassTree::treeMinimum(ClassNode *node)
{
    while (node->leftChild != NULL)
    {
        node=node->leftChild;
    }
    return node;
}

ClassNode* ClassTree::treeMaximum(ClassNode *node)
{
    while (node->rightChild != NULL)
    {
        node=node->rightChild;
    }
    return node;
}


void ClassTree::deleteClassNode(std::string title)
{
    ClassNode *node = search(title);
    if (node == NULL)
    {
        cout << "Class not found." << endl;
    }
    else
    {
        if (node->leftChild == NULL && node->rightChild == NULL)
        {
            if (node->parent->leftChild == node)
            {
                node->parent->leftChild = NULL;
            }
            else
            {
                node->parent->rightChild = NULL;
            }
        }
        else if (node->leftChild != NULL && node->rightChild == NULL)
        {
                ClassNode * x = treeMaximum(node->leftChild);
                x->parent = node->parent;
                //node->parent->leftChild = x;
                //x->leftChild = node->leftChild;
                if (node->parent->leftChild == node)
                {
                node->parent->leftChild = x;
                }
                else
                {
                node->parent->rightChild = x;
                }
        }
        else if (node->leftChild == NULL && node->rightChild != NULL)
        {

                ClassNode * x = treeMinimum(node->rightChild);

                node->title = x->title;
                node->credits = x->credits;
                node->department = x->department;
                node->courseNum = x->courseNum;
                node->satisfiesTitle = x->satisfiesTitle;
                node->preReqTitle = x->preReqTitle;

                x->parent->leftChild = NULL;

        }
        else
        {
            ClassNode *Min = treeMinimum(node->rightChild);
            if (Min == node->rightChild)
            {
                if (node->parent->leftChild==node)
                {
                    Min->leftChild = node->leftChild;
                    node->parent->leftChild = Min;
                    Min->parent = node->parent;
                }
                else
                {
                    Min->leftChild = node->leftChild;
                    node->parent->rightChild = Min;
                    Min->parent = node->parent;
                }
            }
            else
            {
                Min->parent->leftChild = Min->rightChild;
                if (Min->rightChild != NULL)
                {
                    Min->rightChild->parent = Min->parent;
                }
                if (node->parent!= NULL)
                {
                    Min->parent = node->parent;
                    node->parent->leftChild = Min;
                }
                else
                {
                    Min->parent = NULL;
                    root = Min;
                }
                Min->leftChild = node->leftChild;
                Min->rightChild = node->rightChild;
                node->rightChild->parent = Min;
                node->leftChild->parent = Min;
            }
        }
    delete node;
    }
}

void ClassTree::countClassNodes(ClassNode *node, int *c)
{

        if (node->leftChild != NULL)
        {
            *c = *c +1;
            countClassNodes (node->leftChild, c);
        }
        if (node->rightChild != NULL)
        {
            *c = *c+1;
            countClassNodes (node->rightChild, c);
        }
}


int ClassTree::countClassNodes()
{

    int *countInt = new int;
    ClassTree::countClassNodes(root, countInt);
    return *countInt;
}

void ClassTree::DeleteAll(ClassNode *node)
{
    if (node->leftChild != NULL)
    {
        DeleteAll(node->leftChild);
    }
    if (node->rightChild != NULL)
    {
        DeleteAll(node->rightChild);
    }
    cout<<"Deleting: "<<node->title<<endl;
    delete node;
}









ClassTree::~ClassTree()
{
    //dtor
    DeleteAll(root);
}
