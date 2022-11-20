#include<iostream>
#include<fstream>

using namespace std;

class Suduko{

    public :

        int sudukoBoxes[9][9];

        void menu();

        bool validateSuduko(int ,int ,int );

        bool solveSuduko();

        void print();

        void takeInputManually();

        void takeInputFromFile();


};

bool Suduko::validateSuduko(int row ,int column ,int value){

    for(int i = 0;i < 9;i++){

        if(sudukoBoxes[row][i] == value){
            return false;
        }

        if(sudukoBoxes[i][column] == value){
            return false;
        }

        if(sudukoBoxes[( (row/3)*3 + i/3 )][( (column/3)*3 + i%3 )] == value){
            return false;
        }

    }
    return true;
}

bool Suduko::solveSuduko(){

    for(int row = 0;row < 9;row++){

        for(int column = 0;column < 9;column++){

            if(sudukoBoxes[row][column] == 0){

                for(int value = 1;value <= 9;value++){

                    if(validateSuduko(row ,column ,value) == true){

                        sudukoBoxes[row][column] = value;

                        if(solveSuduko() == true){
                            return true;
                        }
                        else{
                            sudukoBoxes[row][column] = 0;
                        }
                    }
               }
               return false;
            }
        }
    }

    return true;

}

void Suduko::print(){

    for(int row = 0;row < 9;row++){

        cout<<"\t\t";

        for(int i = 0;i < 9;i++){

            cout<<"----";

        }

        cout<<endl<<"\t\t"<<"| ";

        for(int column = 0;column < 9;column++){

           cout<< sudukoBoxes[row][column]<<" | ";
        }

        cout<<endl;
    }

    cout<<"\t\t";

    for(int i = 0;i < 9;i++){

        cout<<"----";

    }
}

void Suduko::takeInputFromFile(){

    char filename[20];

    cout<<endl<<"Enter the name of the file containing the Suduko puzzle."<<endl;
    cout<<"\t    -->";
    cin>>filename;

    ifstream sudukoFile;
    sudukoFile.open(filename,ios::in);

    for(int row = 0; row < 9; row++){

        for(int column = 0; column < 9; column++){

            int value;
            sudukoFile>>value;

            while(!(value >=0 && value <= 9)){

                cout<<"The value in the row "<<row + 1<<" and in the cloumn ";
                cout<<column<<" seems to be wrong."<<endl;
                cout<<"correct the value and try again."<<endl;
                exit(EXIT_FAILURE);

            }

            sudukoBoxes[row][column] = value;

        }

    }

    sudukoFile.close();

}

void Suduko::takeInputManually(){

    for(int row = 0;row < 9;row++){

        for(int column = 0;column < 9;column++){

            int enteredValue;
            cout<<"Enter the value for cell["<<row + 1<<"]["<<column + 1<<"] : ";
            cin>>enteredValue;

            while(!(enteredValue >= 0 && enteredValue <= 9)){

                cout<<"Oops! You seem to have entered a wrong value! Try again.\n";
                cout<<"Enter value for cell ["<<row+1<<"]["<<column+1<<"] --> ";
                cin>>enteredValue;

            }

            sudukoBoxes[row][column] = enteredValue;
            cout<<endl;
        }
    }

}

void Suduko::menu(){

    cout<<"\n======================"<<endl;
    cout<<"    Sudoku Solver"<<endl;
    cout<<"======================"<<endl<<endl;

    cout<<"Welcome to Sudoku Solver!"<<endl<<endl;
    cout<<"Before we start, you will have to input the puzzle into this program."<<endl<<endl;
    cout<<"\t1. Input the puzzle by entering the values manually. (Enter 1)\n";
    cout<<"\t2. Input the puzzle by reading a file with values in it. (Enter 2)\n";

    cout<<"\t   The file must not have a name > 20 characters.\n";
    cout<<"\t   The file must be in the same directory as this C++ file.\n";
    cout<<"\t   The file must have all 81 values seperated with spaces.\n";
    cout<<"\t   Empty cells must be filled in as 0.\n";
    cout<<"\t   --> ";

    int option;
    cin>>option;

    while(!(option == 1 || option == 2)){

        cout<<endl<<"You seem to have entered an invalid option. Try again."<<endl;
        cout<<"\t   -->";
        cin>>option;

    }

        cout<<"========================================================="<<endl<<endl;

    if(option == 1){

        takeInputManually();

    }
    else if(option == 2){

        takeInputFromFile();

    }

    cout<<endl<<endl;

    cout<<"Calculating possibilities..."<<endl;
    cout<<"Backtracking across puzzle...."<<endl;
    cout<<"Validating cells and values..."<<endl<<endl;

    if(solveSuduko() == false){

        cout<<"The Given Suduko is not a valid one."<<endl;

    }
    else{

        cout<<"Hurrah!, Your Suduko has been Solved"<<endl<<endl;

        print();

    }

}

int main(){

    Suduko puzzle;

    puzzle.menu();

    return 0;

}
