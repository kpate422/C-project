#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* -----------------------------------
Program 3: TwentyFour Part Two
Course: CS 211, Spring 2023, UIC
System: VS Code and Replit
Author: Krisha Patel
----------------------------------- */

// function to select numbers to use and add commas and period
void printSelectedPuzzle(int selectedPuzzle[][4]) {
  // initalize variables
  int f = 0;
  // print statement
  printf("The numbers to use are: ");

  // for loop that goes through the numbers
  for (int i = 0; i < 4; i++) {
    // print statement
    printf("%d", selectedPuzzle[f][i]);
    // if statement for checking the spaces
    if (i < 3) {
      // prints comma
      printf(", ");
    } else {
      // prints period
      printf(".");
    }
  }
}

// function to open and read the file
void Fileopen(int puzzle[][4], int *count, char Level[10]) {
  // initalize variables
  char filename[100];
  char choice[100];
  *count = 0;
  // checks the level user inputs
  if (Level[0] == 'M') {
    // opens and stores the text file
    strcpy(filename, "medium.txt");
  } 
  // checks the level
  else if (Level[0] == 'H') {
    // opens and stores the text file
    strcpy(filename, "hard.txt");
  } 
  // otherwise opens and stores easy file
  else {
    strcpy(filename, "easy.txt");
  }
  // checks if the file is able to be opened
  FILE *filePtr = fopen(filename, "r");
  if (filePtr == NULL) {
    printf("Error: could not open %s for reading\n", filename);
    exit(-1);
  }
  // while loop that goes through the numbers in the file
  while (fgets(choice, sizeof(choice), filePtr)) {
    if (choice[0] != '\n') {
      // stores the puzzle in a 2d array
      puzzle[*count][0] = choice[0] - '0';
      puzzle[*count][1] = choice[2] - '0';
      puzzle[*count][2] = choice[4] - '0';
      puzzle[*count][3] = choice[6] - '0';
      // counts each time
      (*count)++;
    }
  }
  //closes the file
  fclose(filePtr);
}

// function to generate a random number to use
void Random(int puzzleList[][4], int count, int selectedPuzzle[0][4]) {
  // initalize the variable to generate random
  int random_index = rand() % count;
  // for loop that goes through the numbers
  for (int i = 0; i < 4; i++) {
    // stores the combination
    selectedPuzzle[0][i] = puzzleList[random_index][i];
  }
}

// stack function and add pop and push functions--> used to do linked list and
// PEMDAS, generate stack(solving/output)
struct node { // operator
  char data;
  struct node *next;
};

struct node2 { // operand
  double data;
  struct node2 *next2;
};

// operator to push operator
void pushOperator(char data, struct node **head) {
  // dynamically allocated
  struct node *newNode = malloc(sizeof(struct node));
  // storing
  newNode->data = data;
  newNode->next = (*head);
  (*head) = newNode;
}

// function for push operand--> add first node
void pushOperand(double val, struct node2 **head) {
  // dynamically allocated
  struct node2 *newNode = malloc(sizeof(struct node2));
  // storing
  newNode->data = val;
  newNode->next2 = (*head);
  (*head) = newNode;
}

// function for pop--> removes the first node
double popOperand(struct node2 **head) {
  struct node2 *temp;
  double val;
  // check if stack is empty
  if (*head == NULL){
    printf("Stack is Empty\n");
  }
  else {
    // storing
    temp = *head;
    val = (*head)->data;
    *head = (*head)->next2;
    // free
    free(temp);
  }

  return val;
}

// function to pop the operator
char popOperator(struct node **head) {
  // initalize
  struct node *temp;
  char val;
  // check if stack is empty
  if (*head == NULL)
    printf("Stack is Empty\n");
  else {
    // storing
    temp = *head;
    val = temp->data;
    *head = (*head)->next;
    // free
    free(temp);
  }
  return val;
}

// function to do calculations
double compute(double num1, double num2, char op) {
  // initalize
  double result;
  // switch cases
  switch (op) {
  // case for adding
  case '+':
    return result = num1 + num2;
  // case for subtracting
  case '-':
    return result = num1 - num2;
  // case for multiplying
  case '*':
    return result = num1 * num2;
    // case for dividing
  case '/':
    return result = num1 / num2;
  }
  //return the claculted result
  return result;
}

// function to store the importance of each operator
int precedence(char c) {
  // parenthsis is done first
  if (c == '(' || c == ')') {
    return 0;
  }
  // adding and subtracting done next
  else if (c == '+' || c == '-') {
    return 1;
  }
  // multiplying and dividing done last
  else if (c == '*' || c == '/') {
    return 2;
  }
  // if nothing is being satisfied, returns -1
  else {
    return -1;
  }
}

// checks if the expression user input has valid expression
int is_operator(char *userexp, int *count) {
  // initializing variables
  int tempArray[100];
  *count = 0;
  int counter = 0;
  // for loop that goes through the length of the expression user inputs
  for (int i = 0; i < strlen(userexp); i++) {
    // checks for space
    if (userexp[i] == ' ') {
      continue;
    }
    // checks if value is a number in the user input
    else if (isdigit(userexp[i])) {
      // stores
      tempArray[counter] = userexp[i] - '0';
      // counts
      counter++;

    }
    // does this instead--> sees if not operator
    else {
      if (userexp[i] != '+' && userexp[i] != '-' && userexp[i] != '/' &&
          userexp[i] != '*' && userexp[i] != '(' && userexp[i] != ')') {
        // print error statement
        printf("Error! Invalid symbol entered. Please try again.\n\n");
        return 1;
        // breaks
        break;
      }

      // checks if the operators are missing parenthesis
      if (userexp[i] != '(' && userexp[i] != ')') {
        *count = *count + 1;
      }
    }
  }
  return 0;
}

// function to check for invalid numbers
bool is_invalidNums(int num[100], int puzzle[0][4]) {
  // initalize
  int match = 0;
  // for loop to go through the numbers
  for (int i = 0; i < 4; i++) {
    // stores
    int x = num[i];
    // for loop to go through puzzle
    for (int j = 0; j < 4; j++) {
      // check if equal
      if (x == puzzle[0][j]) {
        match++;
        num[i] = -1;
        puzzle[0][j] = -1;
        break;
      }
    }
  }
  // print statement
  if (match != 4) {
    printf("Error! You must use all four numbers, and use each one only once. Please try again.\n\n");
    return false;
  }
  return true;
}

// function for checking the parenthesis
bool is_InvalidParetheses(char str[100]) {
  // initilizing
  int open = 0;
  int close = 0;
  // for loop
  for (int i = 0; i < strlen(str); i++) {
    // check to see the starting parenethsis
    if (str[i] == '(') {
      // counts
      open++;
    }
    // check ending parenthsis
    else if (str[i] == ')') {
      // counts
      close++;
    }
  }
  // checks to see if the parenthesis is balanced
  if (open < close) {
    return false;
  }
  return true;
}

// function to do the operations, expression/solution(input)
bool Solutions(int selectedPuzzle[0][4], char userexp[], int *count) {
  // initalizes
  int nums[81];
  char operators[81];
  bool playAgain = true;
  int num[100];
  *count = 0;
  int numCount = 0;
  // print statement
  printf("\nEnter your solution: ");
  fgets(userexp, 81, stdin);
  if (userexp[0] == '\n') {
    fgets(userexp, 81, stdin);
  }
  if (userexp[strlen(userexp) - 1] == '\n') {
    userexp[strlen(userexp) - 1] = '\0';
  }
  // for loop to check length of user input
  for (int i = 0; i < strlen(userexp); i++) {
    //c library declaration
    if (isdigit(userexp[i]) != 0 && userexp[i] != ' ') {
      nums[numCount] = userexp[i] - '0';
      //counts
      numCount++;
    }
  }

  // check operators are correct
  if (is_operator(userexp, count) == 1) {
    return false;
  }
  // check if numbers are valid
  if (is_invalidNums(nums, selectedPuzzle) == false) {
    return false;
  }
  // else do evaluation
  else {
    return true;
  }
}

// function to play game
void eval(char userexp[], struct node2 **operandHead, struct node **operatorHead, int *count) {
  //initalize
  int finalResult;
  int bracketCount = 0;
  // checks the length of user expression
  for (int i = 0; i < strlen(userexp); i++) {
    //check if it is a number user enters
    if (isdigit(userexp[i])) {
      pushOperand(userexp[i] - '0', operandHead);
    }
    // checks opening parenthesis
    else if (userexp[i] == '(') {
      bracketCount++;
      pushOperator(userexp[i], operatorHead);
    }
    // checking closing parenthesis
    else if (userexp[i] == ')') {
      bracketCount--;
      // while loop to check if it is not opening parenthesis
      while ((*operatorHead)->data != '(') {
        if ((*operatorHead)->data == '$') {
          printf("Error! Too many closing parentheses in the expression.\n\n");
          return;
        }
        double num1 = popOperand(operandHead);
        double num2 = popOperand(operandHead);
        char op = popOperator(operatorHead);
        double result = compute(num2, num1, op);
        printf("%d %c %d = %d.\n", (int)num2, op, (int)num1, (int)result);
        pushOperand(result, operandHead);
      }
      //checks for opening parenthesis
      if ((*operatorHead)->data == '(') {
        popOperator(operatorHead);
      }
    } 
      //when it is not a space
    else if (userexp[i] != ' ') {
      while ((*operatorHead)->data != '$' && (precedence((*operatorHead)->data) >= (precedence(userexp[i])))) {
        double num1 = popOperand(operandHead);
        double num2 = popOperand(operandHead);
        char op = popOperator(operatorHead);
        double result = compute(num2, num1, op);
        //claculates the steps
        printf("%d %c %d = %d.\n", (int)num2, op, (int)num1, (int)result);
        pushOperand(result, operandHead);
      }
      pushOperator(userexp[i], operatorHead);
    }
  }
  while ((*operatorHead)->data != '$') { // does not equal null
    double num1 = popOperand(operandHead);
    double num2 = popOperand(operandHead);
    char op = popOperator(operatorHead);
    double result = compute(num2, num1, op);
    // print calculations
    printf("%d %c %d = %d.\n", (int)num2, op, (int)num1, (int)result);
    pushOperand(result, operandHead);
  }
  // check if too many values
  if (*count != 3) {
    printf("Error! Too many values in the expression.\n");
  }
  // checking closing parenthesis
  else if (bracketCount != 0) {
    printf("Error! Too many closing parentheses in the expression/n");
  }
  // checks if its equal to 24
  else if ((*operandHead)->data == 24) {
    printf("Well done! You are a math genius.\n");
  }
  // otherwise prints this
  else {
    printf("Sorry. Your solution did not evaluate to 24.\n");
  }
}

// main function-- call other functions
int main() {
  srand(1);
  // Header with instruction to play game
  printf("Welcome to the game of TwentyFour Part Two!\n");
  printf("Use each of the four numbers shown exactly once, \n");
  printf("combining them somehow with the basic mathematical operators (+,-,*,/) \n");
  printf("to yield the value twenty-four.\n");
  // initalize variables
  int userInput = 2;
  int puzzle[100][4];
  char option[10];

  struct node *operatorHead = (struct node *)malloc(sizeof(struct node));
  operatorHead->next = NULL;
  operatorHead->data = '$';

  struct node2 *operandHead = (struct node2 *)malloc(sizeof(struct node2));
  operandHead->next2 = NULL;
  operandHead->data = -1.0;

  // play agian
  while (userInput != 3) {
    // play again
    if (userInput == 2) {
      // print staements
      printf("Choose your difficulty level: E for easy, M for medium, and H for hard (default is easy).\n");
      printf("Your choice --> ");
      scanf("%s", option);
    }
    int puzzleCount = 0;
    int selectedPuzzle[0][4];
    char userExp[100];
    Fileopen(puzzle, &puzzleCount, &option);
    int count = 0;
    do {
      Random(puzzle, puzzleCount, selectedPuzzle);
      printSelectedPuzzle(selectedPuzzle);
    } while (!Solutions(selectedPuzzle, userExp, &count));
    // evaluate here
    eval(userExp, &operandHead, &operatorHead, &count);

    // menu option
    printf("\nEnter: \t1 to play again,\n");
    printf("\t2 to change the difficulty level and then play again, or\n");
    printf("\t3 to exit the program.\n");
    printf("Your choice --> ");
    scanf("%d", &userInput);
  }
  // exits
  printf("\nThanks for playing!\n");
  printf("Exiting...\n");

  //clear rest of stack
  while (operatorHead != NULL) {
    popOperator(&operatorHead);
  }
  while (operandHead != NULL) {
    popOperand(&operandHead);
  }
  
  return 0;
}