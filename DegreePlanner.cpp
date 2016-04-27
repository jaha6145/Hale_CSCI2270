/*James Hale    Final Project    Instructor:Hoenigman    /  TA:Sabnis */

#include <iostream>
#include "DPSched.h"
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

int menu(){
cout << "======Main Menu======" << endl;
cout << "1. Search Class By Name" << endl;
cout << "2. Search Class By Number" << endl;
cout << "3. Enroll in a Class" << endl;
cout << "4. Print Classes By Name" << endl;
cout << "5. Print Classes By Number" << endl;
cout << "6. Drop Class" << endl;
cout << "7. View Schedule" << endl;
cout << "8. Simulate Semester" << endl;
cout << "9. Print Transcript" << endl;
cout << "10. Quit" << endl;


}

int main(/*int argc, char*argv[]*/)
{
    ClassTree tree=ClassTree();
    ClassTree numTree=ClassTree();
    int numCourse, creditHr;
    string classTitle, deptTitle, satTitle, prqTitle, line, word;

    ifstream inFile;
    inFile.open(/*argv[1]*/"Courses.txt");
    if(inFile.good())
    {
        while(getline(inFile,line)){
            stringstream ss(line);
            int getlCounter=0;
            while (getline(ss, word, ',')){
                if(getlCounter==0){
                    classTitle = word;
                    getlCounter++;
                    //cout<<numRank<<" ";
                }
                else if (getlCounter==1){
                    creditHr=atoi(word.c_str());
                    getlCounter++;
                    //cout<<stringTitle<<" ";
                }
                else if (getlCounter==2){
                    deptTitle = word;
                    getlCounter++;
                    //cout<<yr<<" ";
                }
                else if (getlCounter==3){
                    numCourse=atoi(word.c_str());
                    getlCounter++;
                    //cout<<yr<<" ";
                }
                else if (getlCounter==4){
                    satTitle = word;
                    getlCounter++;
                    //cout<<yr<<" ";
                }
                else if (getlCounter==5){
                    prqTitle = word;
                    //cout<< qty << endl;
                    getlCounter++;
                }
                else getlCounter=0;
            }
            int randSeats = rand() % 25;
            tree.addClassNode(classTitle, creditHr, deptTitle, numCourse, satTitle, prqTitle, randSeats);
            numTree.numAddClassNode(classTitle, creditHr, deptTitle, numCourse, satTitle, prqTitle, randSeats);
        }
    }
    menu();
    int userInput;
    cin>>userInput;
    while(userInput!=10){
        cin.ignore();
        if(userInput==1){
            cout << "Enter course title:" << endl;
            string titleIn;
            getline(cin,titleIn);
            tree.findClass(titleIn);
        }
        else if (userInput==2){
            cout << "Enter course number:" << endl;
            int classNumIn;
            cin>>classNumIn;
            numTree.findClassByNumber(classNumIn);
        }
        else if (userInput==3){
            cout << "Enter title:" << endl;
            string classTitleIn;
            getline(cin,classTitleIn);
            tree.takeClass(classTitleIn);
        }
        else if (userInput==4){
            tree.printClassInventory();
        }
        else if (userInput==5){
            numTree.printClassInventory();
        }
        else if (userInput==6){
            cout << "Enter title:" << endl;
            string deleteTitleIn;
            getline(cin,deleteTitleIn);
            tree.deleteFromCart(deleteTitleIn);
        }
         else if (userInput==7){
            tree.printCart();
        }
        else if (userInput==8){
            tree.simSemester();
        }
        else if (userInput==9){
            tree.printTranscript();
        }
        menu();
        cin>>userInput;
    }
    cout<<"Goodbye!"<<endl;
    return 0;
}
