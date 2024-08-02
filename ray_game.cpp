#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <queue>
#include <string>
#include <iostream>
#include <vector>
#include "Inventory.hpp"

using namespace std;

int main(void)
{
   const int screenWidth = 800;
   const int screenHeight = 450;

   // Inventory
   Inventory playerInventory;
   Inventory answerInventory;

   // Answers
   answerInventory.addItem("C");
   answerInventory.addItem("C");
   answerInventory.addItem("A");
   answerInventory.addItem("D");
   answerInventory.addItem("B");

   // Create some Custom colors
   Color depauwBlack = Color{35, 31, 32, 255};
   Color depauwGold = Color{253, 221, 6, 255};

   // create some game objects
   float x = screenWidth / 2;
   float y = screenHeight / 2;

   // Answer Buttons
   Vector2 answerA = {150, 350};
   Vector2 answerB = {250, 350};
   Vector2 answerC = {350, 350};
   Vector2 answerD = {450, 350};

   // Question Pop-ups
   bool popupVisible1 = false;
   Vector2 popupPosition1 = {200, 200};
   bool popupVisible2 = false;
   Vector2 popupPosition2 = {200, 200};
   bool popupVisible3 = false;
   Vector2 popupPosition3 = {200, 200};
   bool popupVisible4 = false;
   Vector2 popupPosition4 = {200, 200};
   bool popupVisible5 = false;
   Vector2 popupPosition5 = {200, 200};

   // Player + Questions Vectors
   Vector2 player = {250, 250};
   Vector2 q1 = {100, 60};
   Vector2 q2 = {200, 60};
   Vector2 q3 = {300, 60};
   Vector2 q4 = {400, 60};
   Vector2 q5 = {500, 60};

   // Exit Door
   Vector2 door = {675, 300};

   // Initialize window and set the screen title
   InitWindow(screenWidth, screenHeight, "Escape East College");

   SetTargetFPS(90);
   double time = GetTime();
   bool isGameOver = false;
   
    ///--------------------------------------------------------------------------------------

   // Main game loop, Draw loop
   while (!WindowShouldClose()) // Detect window close button or ESC key
   {
      
      // ***** Processing and updates *****
      // Get the change in time since last frame.
      double lastTime = time;
      time = GetTime();
      double deltaTime = time - lastTime;

      // Movement
      if (IsKeyDown(KEY_LEFT)) { player.x -= 4.0f; }
      if (IsKeyDown(KEY_RIGHT)) { player.x += 4.0f; }
      if (IsKeyDown(KEY_UP)) { player.y -= 4.0f; }
      if (IsKeyDown(KEY_DOWN)) { player.y += 4.0f; }
      
      /* Interaction with Question */
      if (CheckCollisionCircles(player, 10, q1, 10))
      { DrawText("Question 1", q1.x - 25, q1.y - 50, 10, BLACK);
      if (IsKeyPressed(KEY_E)) { popupVisible1 = !popupVisible1; }
      } else { popupVisible1 = false; }

      if (CheckCollisionCircles(player, 10, q2, 10))
      { DrawText("Question 2", q2.x - 25, q2.y - 50, 10, BLACK);
      if (IsKeyPressed(KEY_E)) { popupVisible2 = !popupVisible2; }
      } else { popupVisible2 = false; }

      if (CheckCollisionCircles(player, 10, q3, 10))
      { DrawText("Question 3", q3.x - 25, q3.y - 50, 10, BLACK);
      if (IsKeyPressed(KEY_E)) { popupVisible3 = !popupVisible3; }
      } else { popupVisible3 = false; }

      if (CheckCollisionCircles(player, 10, q4, 10))
      { DrawText("Question 4", q4.x - 25, q4.y - 50, 10, BLACK);
      if (IsKeyPressed(KEY_E)) { popupVisible4 = !popupVisible4; }
      } else { popupVisible4 = false; }

      if (CheckCollisionCircles(player, 10, q5, 10))
      { DrawText("Question 5", q5.x - 25, q5.y - 50, 10, BLACK);
      if (IsKeyPressed(KEY_E)) { popupVisible5 = !popupVisible5; }
      } else { popupVisible5 = false; }

      /* Adding Key to Inventory */
      if (CheckCollisionCircles(player, 10, answerA, 10)) {
          if (IsKeyPressed(KEY_E)) { playerInventory.addItem("A"); }
      }
      if (CheckCollisionCircles(player, 10, answerB, 10)) {
          if (IsKeyPressed(KEY_E)) { playerInventory.addItem("B"); }
      }
      if (CheckCollisionCircles(player, 10, answerC, 10)) {
          if (IsKeyPressed(KEY_E)) { playerInventory.addItem("C"); }
      }
      if (CheckCollisionCircles(player, 10, answerD, 10)) {
          if (IsKeyPressed(KEY_E)) { playerInventory.addItem("D"); }
      }

      // Inventory Pop-up
      if (IsKeyPressed(KEY_R)) { playerInventory.removeItem(); }
      
      // ***** Draw ***** //
      if(!isGameOver) {
         BeginDrawing();
         ClearBackground(RAYWHITE);

         playerInventory.displayInventory();
         DrawText("Press I for controls", 685, 10, 10, DARKGRAY);

         DrawCircleV(player, 20, depauwBlack);
         DrawRectangleV(door, {50, 75}, depauwGold);
         DrawText("Attempt to escape...", door.x - 25, door.y + 90, 10, BLACK);

         // Drawing the Questions
         DrawCircleV(q1, 25, depauwGold);
         DrawCircleV(q2, 25, depauwGold);
         DrawCircleV(q3, 25, depauwGold);
         DrawCircleV(q4, 25, depauwGold);
         DrawCircleV(q5, 25, depauwGold);

         DrawCircleV(answerA, 20, DARKGRAY);
         DrawText("Answer A", answerA.x - 25, answerA.y + 40, 10, BLACK);
         DrawCircleV(answerB, 20, DARKGRAY);
         DrawText("Answer B", answerB.x - 25, answerB.y + 40, 10, BLACK);
         DrawCircleV(answerC, 20, DARKGRAY);
         DrawText("Answer C", answerC.x - 25, answerC.y + 40, 10, BLACK);
         DrawCircleV(answerD, 20, DARKGRAY);
         DrawText("Answer D", answerD.x - 25, answerD.y + 40, 10, BLACK);

         // Drawing Question Pop-ups
         if (popupVisible1) { // Get position to follow
            DrawRectangle(popupPosition1.x - 80, popupPosition1.y - 100, 350, 200, GRAY);
            
            // Questions
            DrawText("Q1", popupPosition1.x - 70, popupPosition1.y - 90, 20, DARKGRAY);
            DrawText("Which is the largest freshwater lake in the world?", popupPosition1.x - 70, popupPosition1.y - 60, 13, BLACK);

            // Answer Options
            DrawText("A. Great Bear Lake", 
            popupPosition1.x - 70, popupPosition1.y - 30, 20, BLACK);
            DrawText("B. Great Slave Lake", 
            popupPosition1.x - 70, popupPosition1.y, 20, BLACK);
            DrawText("C. Lake Baikal", 
            popupPosition1.x - 70, popupPosition1.y + 30, 20, BLACK);
            DrawText("D. Erie Lake", 
            popupPosition1.x - 70, popupPosition1.y + 60, 20, BLACK);

         } 

         if (popupVisible2) { // Get position to follow
            DrawRectangle(popupPosition2.x - 80, popupPosition2.y - 100, 350, 200, GRAY);
            
            // Questions
            DrawText("Q2", popupPosition2.x - 70, popupPosition2.y - 90, 20, DARKGRAY);
            DrawText("Which color of visible light travels the fastest in crown glass?", popupPosition2.x - 70, popupPosition2.y - 60, 10, BLACK);

            // Answer Options
            DrawText("A. Violet", 
            popupPosition2.x - 70, popupPosition2.y - 30, 20, BLACK);
            DrawText("B. Yellow", 
            popupPosition2.x - 70, popupPosition2.y, 20, BLACK);
            DrawText("C. Red", 
            popupPosition2.x - 70, popupPosition2.y + 30, 20, BLACK);
            DrawText("D. Blue", 
            popupPosition2.x - 70, popupPosition2.y + 60, 20, BLACK);

         } 

         if (popupVisible3) { // Get position to follow
            DrawRectangle(popupPosition3.x - 80, popupPosition3.y - 100, 350, 200, GRAY);
            
            // Questions
            DrawText("Q3", popupPosition3.x - 70, popupPosition3.y - 90, 20, DARKGRAY);
            DrawText("In what decade was Madonnna born?", popupPosition3.x - 70, popupPosition3.y - 60, 15, BLACK);

            // Answer Options
            DrawText("A. 1950s", 
            popupPosition3.x - 70, popupPosition3.y - 30, 20, BLACK);
            DrawText("B. 1960s", 
            popupPosition3.x - 70, popupPosition3.y, 20, BLACK);
            DrawText("C. 1970s", 
            popupPosition3.x - 70, popupPosition3.y + 30, 20, BLACK);
            DrawText("D. 1980s", 
            popupPosition3.x - 70, popupPosition3.y + 60, 20, BLACK);
         } 

         if (popupVisible4) { // Get position to follow
            DrawRectangle(popupPosition4.x - 80, popupPosition4.y - 100, 350, 200, GRAY);
            
            // Questions
            DrawText("Q4", popupPosition4.x - 70, popupPosition4.y - 90, 20, DARKGRAY);
            DrawText("Which animal can be seen on the Porsche logo?", popupPosition4.x - 70, popupPosition4.y - 60, 13, BLACK);

            // Answer Options
            DrawText("A. Cheetah", 
            popupPosition4.x - 70, popupPosition4.y - 30, 20, BLACK);
            DrawText("B. Cougar", 
            popupPosition4.x - 70, popupPosition4.y, 20, BLACK);
            DrawText("C. Dog", 
            popupPosition4.x - 70, popupPosition4.y + 30, 20, BLACK);
            DrawText("D. Horse", 
            popupPosition4.x - 70, popupPosition4.y + 60, 20, BLACK);

         } 

         if (popupVisible5) { // Get position to follow
            DrawRectangle(popupPosition5.x - 80, popupPosition5.y - 100, 350, 200, GRAY);
            
            // Questions
            DrawText("Q5", popupPosition5.x - 70, popupPosition5.y - 90, 20, DARKGRAY);
            DrawText("What type of scientist studies living plants?", popupPosition5.x - 70, popupPosition5.y - 60, 15, BLACK);

            // Answer Options
            DrawText("A. Geologist", 
            popupPosition5.x - 70, popupPosition5.y - 30, 20, BLACK);
            DrawText("B. Botanist", 
            popupPosition5.x - 70, popupPosition5.y, 20, BLACK);
            DrawText("C. Paleontologist", 
            popupPosition5.x - 70, popupPosition5.y + 30, 20, BLACK);
            DrawText("D. Entomologist", 
            popupPosition5.x - 70, popupPosition5.y + 60, 20, BLACK);
         } 

         // Instructions
         if (IsKeyDown(KEY_I)) {
            DrawText("Use the arrow keys to move around", 200, 160, 10, DARKGRAY);
            DrawText("E: Interact", 200, 180, 20, DARKGRAY);
            DrawText("R: Reset your answers", 200, 200, 20, DARKGRAY);
         }

         // Ending of game
         if (CheckCollisionCircles(player, 30, door, 30)) {
            if (IsKeyDown(KEY_E)) { 
               if (playerInventory.answerChecker(answerInventory)) {
                  isGameOver = true;
               } else {
                  DrawText("Try Again!", 100, 150, 60, DARKGRAY);
               }
            }
         }

      // Call this at the end of your drawing.
      EndDrawing();

      } else { // Ending of game
         BeginDrawing();
         ClearBackground(RAYWHITE);

         string message = "You Escaped East College!";
         DrawText(message.c_str(), 100, 300, 40, DARKGRAY);

         EndDrawing();
      }
   }
   
   CloseWindow(); 
   return 0;
}