// include guards
#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <queue>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Inventory {
    private:
        queue<string> items;
        int capacity;
        int size;

    public:
        // Constructor
        Inventory() {
        capacity = 5;
        size = 0;
        }

        // Destructor
        ~Inventory() {}

        // Add an item to the inventory
        void addItem(const string& item) {
            if (size < capacity) { 
                items.push(item);
                size += 1;
            }
            else { cout << "You can't have more than 5 answers." << endl; }
        }

        void removeItem() {
            while (!items.empty()) {
                items.pop();
                size -= 1;
            }
        }

    bool answerChecker(const Inventory& other) { // check to see if the player's array and the answer's array the SAME amount, SAME element, and in the SAME order
        if (items.size() != other.items.size()) { 
            return false; 
        }

        // different size = not the same
        queue<string> temp1 = items; // create two temporary arrays for playerInventory and answerInventory
        queue<string> temp2 = other.items;
        while (!temp1.empty()) {
            if (temp1.front() != temp2.front()) {
                return false; 
            }
            temp1.pop();
            temp2.pop();
        } 
        cout << "All answers are correct!" << endl; // Checking to see if it works
        return true; 
    }


        // Print all items in the inventory
        void displayInventory() {
            DrawText("Your Answers:", 600, 75, 20, BLACK);
            if (!items.empty()) {
                queue<string> tempQueue = items;
                int yPos = 100;
                int questionNumber = 1;
                while (!tempQueue.empty()) {
                    DrawText(tempQueue.front().c_str(), 620, yPos, 20, BLACK);
                    std::string strNumber = std::to_string(questionNumber); // to have a numbered bullet list
                    
                    const char* text = strNumber.c_str();
                    DrawText(text, 600, yPos, 20, BLACK);
                    
                    yPos += 20;
                    questionNumber += 1;
                    tempQueue.pop();
                }
            } 
        }
};

#endif