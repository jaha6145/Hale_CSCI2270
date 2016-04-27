#include "DPSched.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

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

void ClassTree::addToCart(std::string title)
{
    ClassNode *addNode = search(title);
    classCart.push_back(addNode);
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
            if (foundClass->preReqTitle == "none")
            {
                cout<<"prereqs = none"<<endl;
                foundClass->seats = foundClass->seats-1;
                addToCart(title);

                cout << "The following class has been added to your schedule: " << endl;
                cout << "===========" << endl;
                cout << "Title:" << foundClass->title << endl;
                cout << "Course ID:" << foundClass->department<<" "<<foundClass->courseNum<< endl;
                cout << "Credit Hours:" << foundClass->credits << endl;
                cout << "Satisfies:" << foundClass->satisfiesTitle << endl;
                cout << "PreRequisite:"<<foundClass->preReqTitle<<endl;
            }
            else
            {
                if (transcript.size()==0)
                {
                    cout<<"Transcript is blank"<<endl;
                    cout<<"PreRequisites not met"<<endl;
                    cout<<"You must first complete "<<foundClass->preReqTitle<<endl;
                }
                else
                {
                    bool found;
                    for (int i = 0; i<transcript.size(); i++)
                    {
                        if (transcript[i]->title == foundClass->preReqTitle)
                        {
                            foundClass->seats = foundClass->seats-1;
                            addToCart(title);
                            found = 1;

                            cout << "The following class has been added to your schedule: " << endl;
                            cout << "===========" << endl;
                            cout << "Title:" << foundClass->title << endl;
                            cout << "Course ID:" << foundClass->department<<" "<<foundClass->courseNum<< endl;
                            cout << "Credit Hours:" << foundClass->credits << endl;
                            cout << "Satisfies:" << foundClass->satisfiesTitle << endl;
                            cout << "PreRequisite:"<<foundClass->preReqTitle<<endl;

                        }
                    }
                    if (!found)
                    {
                        cout<<"PreRequisites not met"<<endl;
                        cout<<"You must first complete "<<foundClass->preReqTitle<<endl;
                    }
                }
            }
        }
    }
}
void ClassTree::printCart()
{
    if (classCart.size() == 0)
    {
        cout<<"Your Cart is Empty"<<endl;
    }
    else
    {
        for (int i =0; i < classCart.size(); i++)
        {
            ClassNode *node =classCart[i];
            cout<<i+1<<". "<<node->department<<" "<<node->courseNum<<": "<<node->title<<": "<<node->credits<<" Hrs; "<<node->seats<<" seats remaining"<<endl;
        }
    }
}

void ClassTree::printTranscript()
{
    if (transcript.size() == 0)
    {
        cout<<"Your Transcript is Blank"<<endl;
    }
    else
    {
        for (int i =0; i < transcript.size(); i++)
        {
            ClassNode *node =transcript[i];
            cout<<i+1<<". "<<node->department<<" "<<node->courseNum<<": "<<node->title<<": "<<node->credits<<" Hrs; "<<node->seats<<" seats remaining"<<endl;
        }
    }
}

void ClassTree::simSemester()
{
    while (!classCart.empty())
    {

        transcript.push_back(classCart[0]);
        classCart.erase(classCart.begin());
    }
    for (int i = 0; i<transcript.size(); i++)
    {
        cout<<transcript[i]->title<<" has been completed and added to transcript"<<endl;
    }
}

void ClassTree::printClassInventory(ClassNode *node)
{
    if (node->leftChild!=NULL)
    {
        printClassInventory(node->leftChild);
    }
    cout<<node->department<<" "<<node->courseNum<<": "<<node->title<<": "<<node->credits<<" Hrs; "<<node->seats<<" seats remaining;"<<endl<<"PreReq: "<<node->preReqTitle<<endl;
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
    //cout<<"Deleting: "<<node->title<<endl;
    delete node;
}

void ClassTree::deleteFromCart(std::string title)
{
    bool foundAndErased;
    for (int i =0; i < classCart.size(); i++)
    {
        ClassNode *node =classCart[i];
        if (node->title == title)
        {
            classCart.erase(classCart.begin()+i);
            foundAndErased = 1;
            cout<<node->title<<" has been removed from schedule"<<endl;
            break;
        }
    }
    if(!foundAndErased) cout<<"Course not scheduled"<<endl;
}

ClassTree::~ClassTree()
{
    //dtor
    DeleteAll(root);
}
