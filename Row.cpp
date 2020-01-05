#include <string>
#include <vector>
#include <iostream>

class RowElement
{

public:
    enum Color
    {
        ORANGE,
        RED,
        BLACK,
        BLUE,
        JOKER
    };

    RowElement::Color &getColor()
    {
        return color;
    }

    int getNumber()
    {
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
    number = newNumber;
    color = newColor;
}

bool checkElementsHaveSameColor(std::vector<RowElement> row)
{
    RowElement::color color;
    bool allElementsHaveSameColor = true;
    for (std::vector::iterator it = row.begin(); it != row.end(); it++)
    {
        if (it == row.begin())
        {
            color = it.getColor());
        }
        else
        {
            if (color != it.getColor())
            {
                allElementsHaveSameColor = false;
                break;
            }
        }
    }
    return allElementsHaveSameColor;
}

std::vector<Token> searchForGroups(std::vector<std::vector> field)
{
    Token::color color;
    for (int i = 0; i < field.size(); i++)
    {
        std::map<int, Token::Color> indexWithColor;
        for (int j = 0; j < colorsize; j++)
        {
            if ((field[i][j].location == "playground")) //|| (field[i][j].location == "HandToPlayground"))
            {
                indexWithColor[j] = field.getColor; //increase number of fields with same color
            }
        }

        for (std::map<Token::Color, int>::iterator it = indexWithColor.begin(); it != indexWithColor.end(); ++it)
        {
            std::map<Token::Color, int> repeated;
            repeated[it->first] = repeated[it->first]++;
        }

        if (repeated.size > 2)
        {
            std::vector<Token> newGroup;
            for (std::map<Token::Color, int>::iterator it = repeated.begin(); it != repeated.end(); ++it)
            {
                if (it->second > 1)
                {
                    //find out repeated keys to add
                    for(std::map<int, Token::Color>::iterator iter = indexWithColor.begin(); iter != indexWithColor.end(); ++it){
                        if (repeated[iter->second]==it->first)
                        {
                            newGroup.push_back(iter->first);
                            repeated[iter->second]--;
                            break;
                        }
                    }
                }
                
            }

        }
    }
}

bool checkElementsAreInRow(std::vector<RowElement> row)
{
    bool elementsAreInRow = true;
    for (int i = 1; i < row.size(); ++i)
    {
        if (row.at(i - 1).getNumber() != row.at(i).getNumber())
        {
            elementsAreInRow = false;
        }
    }
    return elementsAreInRow;
}

bool checkIntegrityAfterChange(std::vector<RowElement> row)
{
    if((checkElementsHaveSameColor(row) && checkElementsAreInRow(row)){
        return true;
    }
    else
    {
        return false;
        //idea: throw back only result of all operations that fail
    }
}