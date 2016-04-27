#ifndef DPSCHED_H
#define DPSCHED_H
#include<string>
#include<queue>
#include<cstdlib>

using namespace std;

struct ClassNode{
    std::string title;//same
    int credits;//int ranking;
    std::string department;//int year;
    int courseNum;//int quantity;
    std::string satisfiesTitle;
    std::string preReqTitle;
    int seats;
    ClassNode *parent;
    ClassNode *leftChild;
    ClassNode *rightChild;

    ClassNode(){};
    ClassNode(std::string in_title, int in_credits, std::string in_department, int in_courseNum, std::string in_satisfiesTitle, std::string in_preReqTitle, int in_seats)
    {
        title = in_title;
        credits = in_credits;
        department = in_department;
        courseNum = in_courseNum;
        satisfiesTitle = in_satisfiesTitle;
        preReqTitle = in_preReqTitle;
        seats = in_seats;
    }

};

class ClassTree
{

    public:
        ClassTree();
        ~ClassTree();
        void printClassInventory();
        int countClassNodes();
        void deleteClassNode(std::string title);
        void addClassNode(std::string title, int hours, std::string dept, int courseNumber, std::string satisfies, std::string preReqs, int seats);
        void numAddClassNode(std::string title, int hours, std::string dept, int courseNumber, std::string satisfies, std::string preReqs, int seats);
        void findClass(std::string title);
        void findClassByNumber(int courseNum);
        void takeClass(std::string title);

        vector<ClassNode> transcript();
        vector<ClassNode> classCart();
        int creditCount();
        int degreeProgress();


    protected:

    private:
        void DeleteAll(ClassNode * node); //use this for the post-order traversal deletion of the tree
        void printClassInventory(ClassNode * node);
        void countClassNodes(ClassNode *node, int *c);
        string matchNum2Title(ClassNode *node, int in_num);
        ClassNode* searchByNum(int courseNum);
        ClassNode* search(std::string title);
        ClassNode* treeMinimum(ClassNode *node);
        ClassNode* treeMaximum(ClassNode *node);
        ClassNode *root=NULL;
};

#endif // MOVIETREE_H
