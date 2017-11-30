#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;


void getDimensions(int&, int&, char&);

void populateMatrix(int, int, vector<vector<double> >&, char);

void outputMatrix(int, int, vector<vector<double> >&);

void rowSwap(int, int, vector<vector<double> >&, int, int);

void pivot(int, int, vector<vector<double> >&);

void gaussElimination(int, int, vector<vector<double> >&);

bool checkSolution(int, int, vector<vector<double> >&);

void preNewSystem(int, int, vector<vector<double> >&);

void outputNewSystem(int, int, vector<vector<double> >&);

void backSubstitution(int, int, vector<vector<double> >&);




int main()
{
    char choice;

    do
    {
        int rows, columns;
        char homogeneous;
        bool solution = true;


        getDimensions(rows, columns, homogeneous);

        vector<vector<double> >matrix((columns + 1), vector<double>(rows));

        populateMatrix(columns, rows, matrix, homogeneous);

        cout << "This is your initial ";
        outputMatrix(columns, rows, matrix);

        pivot(columns, rows, matrix);

        outputMatrix(columns, rows, matrix);

        gaussElimination(columns, rows, matrix);

        pivot(columns, rows, matrix);



        if(homogeneous == 'n' || homogeneous == 'N')
            solution = checkSolution(columns, rows, matrix);

        if(homogeneous == 'n' || homogeneous == 'N' && solution == true)
        {
            outputNewSystem(columns, rows, matrix);

            preNewSystem(columns, rows, matrix);

            //backSubstitution(columns, rows, matrix);

        }




        matrix.clear();

        cout << "Would you like to enter another matrix?" << endl;
        cout << "Enter y|Y for yes, and n|N for no" << endl;

        cin >> choice;


    }while(choice != 'n' && choice != 'N');

    return 0;
}


void getDimensions(int& rows, int& columns, char& homogeneous)
{
    cout << "Hello user.  Enter the number of vectors, and vector size"
         << " you would like your matrix to have." << endl;
    cout << "\nvectors:  ";
    cin  >> columns;
    cout << "\nvector size:   ";
    cin  >> rows;
    cout << "\nIs this a homogeneous system of equations (enter y |Y for yes, n|N for no):    ";
    cin >> homogeneous;
}


void populateMatrix(int columns, int rows, vector<vector<double> >& matrix, char homogeneous)
{


    for(int i = 0; i < columns; i++)
    {
        cout << "Enter your values for vector #" << (i+1) << "  " << endl;

        for(int a = 0; a < rows; a++)
            cin >> matrix[i][a];
    }

    if(homogeneous == 'n' || homogeneous == 'N')
    {
        cout << "Enter your values for the solution vector    " << endl;

        for(int a = 0; a < rows; a++)
            cin >> matrix[columns][a];
    }
    else
        for(int a = 0; a < rows; a++)
            matrix[columns][a] = 0;
}


void outputMatrix(int columns, int rows, vector<vector<double> >& matrix)
{
    cout << "matrix:\n\n\n";
    int variable = 1;
    int answerSpacing = columns * 4;

    for(int i = 0; i < rows; i++)
    {
        cout << "|    ";
        for(int a = 0; a < columns; a++)
            cout << setw(6) << setprecision(3) <<left << matrix[a][i];
        cout << "|";

        if(i < columns)
            cout << "     |  x" << variable << "  |";

        if(i == columns/2)
        {
            cout << "   == " << setw(answerSpacing - 4) << right << "|   " << matrix[columns][i];
            cout << setw(4) << "|";
        }
        else
        {
            if(i >= columns)
            {
                cout << setw(answerSpacing + 16) << right << "      |   " << matrix[columns][i];
                cout << setw(4) << right << "|";
            }
            else
            {
                cout << setw(answerSpacing + 2) << "          |   " << matrix[columns][i];
                cout << setw(4) << right  << "|";
            }
        }
        variable++;

        cout << "\n\n\n";
    }
}


void rowSwap(int columns, int rows, vector<vector<double> >& matrix, int row1, int row2)
{
    vector<double> temp (columns + 1);

    for(int i = 0; i < columns+1; i++ )
    {
        temp[i] = matrix[i][row1];
        matrix[i][row1] = matrix[i][row2];
        matrix[i][row2] = temp[i];
    }

    temp.clear();
}


void pivot(int columns, int rows, vector<vector<double> >& matrix)
{
    int row1, row2;
    int count = 0;


    for(int i = 0; i < columns+1; i++)
        for(int a = i + 1; a < rows; a++)
            if(matrix[i][i] < matrix[i][a])
            {
                row1 = i;
                row2 = a;

                rowSwap(columns, rows, matrix, row1, row2);
            }
}


void gaussElimination(int columns, int rows, vector<vector<double> >& matrix)
{
    double epsilon = 0.000000000008;


    for(int i = 0; i < columns+1; i++)
        for(int a = i + 1; a < rows; a++)
        {
            if(matrix[i][a] != 0 && matrix[i][i] != 0)
            {
                double coefficient = matrix[i][a]/matrix[i][i];

                for(int k = 0; k < columns+1; k++)
                {
                    matrix[k][a] -= coefficient * matrix[k][i];

                    if(matrix[k][a] > 0 - epsilon && matrix[k][a] < 0 + epsilon)
                        matrix[k][a] = 0;
                }
            }
            outputMatrix(columns, rows, matrix);
        }
}


bool checkSolution(int columns, int rows, vector<vector<double> >& matrix)
{
    int solution = 0;

    for(int i = 0; i < columns; i++)
        solution += matrix[i][columns - 1];

        if(matrix[columns][rows - 1] != 0 && solution == 0)
        {
            cout << "\n\n*** There is no solution to this system **\n\n\n";
            return false;
        }

    cout << "\n\n\n";
}


void preNewSystem(int columns, int rows, vector<vector<double> >&matrix)
{
    double coefficient;

    for(int i = 0; i < rows; i++)
    {
        bool first = false;

        for(int a = 0; a < columns + 1; a++)
        {
            if(matrix[a][i] != 0 && first == false)
            {
                coefficient = matrix[a][i];
                first = true;
            }

            if(matrix[a][i] != 0)
                matrix[a][i] /= coefficient;
        }
    }

    cout << "\n\n\n";

    outputNewSystem(columns, rows, matrix);
}


void outputNewSystem(int columns, int rows, vector<vector<double> >& matrix)
{
    cout << "Below is the solution set to the matrix\n\n";

    for(int i = 0; i < rows; i++)
    {
        int varNum = 1;

        for(int a = 0; a < columns + 1; a++)
            {
                if(matrix[a][i] != 0 && a < columns)
                {
                    if(matrix[a][i] == 1)
                        cout << "X" << varNum << "     ";
                    else
                        cout << matrix[a][i] << "X" << varNum << "    ";
                }
                else if(matrix[a][i] != 0)
                    cout << "=    " << matrix[a][i];

                varNum++;
            }
            cout << endl << endl;
    }
}


void backSubstitution(int columns, int rows, vector<vector<double> >& matrix)
{

    //takes reflection of the matrix

    double tempMatrix[columns][rows];

    double answers[columns];


    for(int a = columns - 1; a >= 0; a--)
    {
        for(int i = rows; i >= 0; i--)
        {
            cout << matrix[i][a] << "    ";

        }

            cout << endl;
    }

        cout << endl;

        for(int a = columns - 1; a >= 0; a--)
        {

        }




}



