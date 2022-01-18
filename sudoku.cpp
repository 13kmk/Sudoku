#include<iostream>
#include<vector>
#include<unordered_set>

using namespace std;

#define usi unordered_set<int>
#define vui vector<usi>
#define vvc vector<vector<char>>
#define vc vector<char>

void printv(vvc v)
{
    /*
    v - the given valid sudoku
    Prints the input in the form of sudoku.
    */
    int i,j;
    int m=v.size();
    int n=v[0].size();
    cout<<"Solved!\n";
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
            cout<<v[i][j]<<" ";
        cout<<"\n";
    }
}

bool isNotSafe(int i,int box_index,int xpos,int ypos,vui &rows,vui &cols,vui &boxes)
{

    /*
    i           - a number from 1 to 9
    box_index   - index of the box to find i
    rows        - Rows of sudoku
    cols        - Columns of sudoku
    boxes       - Boxes of sudoku
    (xpos,ypos) - Fills a valid number if exists at this index/position
    returns true if it is not possible to fill number i at position (xpos,ypos)
    else returns false
    */

    if(rows[xpos].find(i)!=rows[xpos].end() || cols[ypos].find(i)!=cols[ypos].end())
        return true;
    return boxes[box_index].find(i)!=boxes[box_index].end();
}

bool fillSudoku(vvc &sudoku,vui &rows,vui &cols,vui &boxes, int xpos=0,int ypos=0,int nrow=9,int ncol=9)
{

    /*
    sudoku      - nrow x ncol sudoku
    rows        - Rows of sudoku
    cols        - Columns of sudoku
    boxes       - Boxes of sudoku
    (xpos,ypos) - Fills a valid number if exists at this index/position
    returns false if it is not possible to fill an appropriate value at (xpos,ypos)
    else returns true and fills the sudoku
    */

    int i,j;
    if(xpos>=nrow)
        return true;
    int nx=xpos,ny=ypos+1;
    if(ypos == ncol-1)
    {       
        ny=0;
        nx=xpos+1;
    }
    if(sudoku[xpos][ypos]!='.')
    {
        if(fillSudoku(sudoku,rows,cols,boxes,nx,ny))
            return true;
        return false;
    }
    int box_ind= (xpos/3)*3+(ypos/3);

    //Fills sudoku as row-major order
    for(i=1;i<10;i++)
    {
        //Checks if the number is safe to fill at (xpos,ypos)
        if(isNotSafe(i,box_ind,xpos,ypos,rows,cols,boxes))
            continue;

        //Fill the value and add that value to rows,cols and tiles
        rows[xpos].insert(i);
        cols[ypos].insert(i);
        boxes[box_ind].insert(i);
        sudoku[xpos][ypos]=(i+'0');

        //If a solution is found end process of filling
        if(fillSudoku(sudoku,rows,cols,boxes,nx,ny))
            return true;

        //remove the filled value from rows,cols and tiles as there is no solution by filling it
        sudoku[xpos][ypos]='.';
        rows[xpos].erase(i);
        cols[ypos].erase(i);
        boxes[box_ind].erase(i);
    }
    return false;
}

int main()
{
    int i,j;
    usi num;
    vc r(9,'.');
    vvc sudoku(9,r);

    //Using rows,cols and tiles to keep track of numbers that are already present in corresponding row ,column and tile
    vui rows(9,num);
    vui cols(9,num);
    vui boxes(9,num);

    int box_ind;
    string s;
    cout<<"Please enter your input sudoku : \n";
    cout<<"Input should contain 9 lines each representing one row of sudoku ,each line should contain 9 characters and represent empty character by '.'\n";
    for(i=0;i<9;i++)
    {
        cin>>s;
        for(j=0;j<9;j++)
        {
            sudoku[i][j]=s[j];
            if(s[j]=='.')
                continue;
            box_ind=(i/3)*3 + (j/3);
            rows[i].insert(s[j]-'0');
            cols[j].insert(s[j]-'0');
            boxes[box_ind].insert(s[j]-'0');
        }
    }

    //Outputs solution
    if(!fillSudoku(sudoku,rows,cols,boxes))
        cout<<"Your input has no solution\n";
    printv(sudoku);
    
    return 0;
}