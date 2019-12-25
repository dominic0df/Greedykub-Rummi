#include <string>
#include <vector>
#include <iostream>

class RowElement
{

public:

    enum Color{ORANGE, RED, BLACK, BLUE, JOKER};

    RowElement::Color &getColor(){
        return color;
    }

    int getNumber(){
        return number;
    }

    RowElement(int newNumber, RowElement::Color newColor);

private:

    int number;
    RowElement::Color color;

};

RowElement::RowElement(
    int newNumber, RowElement::Color newColor)
{
    number=newNumber;
    color=newColor;
}

bool checkElementsHaveSameColor(std::vector<RowElement> row){
    RowElement::color color;
    bool allElementsHaveSameColor=true;
    for (std::vector::iterator it = row.begin(); it != row.end(); it++)
    {
        if (it==row.begin())
        {
            color = it.getColor());
        }
        else
        {
            if (color!=it.getColor())
            {
                allElementsHaveSameColor=false;
                break;
            }
            
        }
    }
    return allElementsHaveSameColor;
}

bool checkElementsAreInRow(std::vector<RowElement> row){
    bool elementsAreInRow=true;
    for (int i=1;i<row.size();++i){
        if (row.at(i-1).getNumber()!=row.at(i).getNumber())
        {
            elementsAreInRow=false;
        }
    }
}

bool checkIntegrityAfterChange(std::vector<RowElement> row){
    if((checkElementsHaveSameColor(row) && checkElementsAreInRow(row)){
        return true;
    }
    else
    {
        return false;
        //idea: throw back only result of all operations that fail
    }
    
}