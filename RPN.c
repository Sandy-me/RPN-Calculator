#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct Node{
    char data;
    struct Node* next;
};

struct Stack{
    struct Node* top;
};
//initialize a new node
struct Node* new_node(char my_character){
   struct Node* node = (struct Node*)malloc(sizeof(struct Node));
        node -> data = my_character;
        node -> next = NULL;

        return node;
}
struct Stack* create_mystack(){
  struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));

  stack -> top = NULL;
  return stack;
}

int isEmpty(struct Stack* stack){
    return stack -> top == NULL;
}
void push(struct Stack* stack, char my_character){
    struct Node* node = new_node(my_character);

    node -> next = stack -> top;
    stack -> top = node;
}
char pop(struct Stack* stack){
    if(isEmpty(stack)){
        printf("Stack is empty\n");

        return "\0";
    }
    char data = stack -> top -> data;
    struct Node* temp = stack -> top;

    stack -> top = stack -> top -> next;
    free(temp);

    return data;
}
char peek(struct Stack* stack){
    if(isEmpty(stack)){
        printf("Stack is Empty.");
        return "\0";// returns a NULL character
    }
    return stack -> top -> data;
}
int is_operator(char the_operator){
    return the_operator == '+' || the_operator == '-' || the_operator == '*' || the_operator == '/' || the_operator == '%';

}
int get_precedence(char the_operator){
    switch(the_operator){
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        default:
            return -1;//invalid operator
    }
}
void infix_to_postfix(char* infix, char* postfix){
    struct Stack* stack = create_mystack();

    int i, k;

    for(i = 0, k = -1; infix[i]; ++i){
        if(isalnum(infix[i])){
            postfix[++k] = infix[i];
        }else if(infix[i] == '('){
            push(stack, infix[i]);
        }else if(infix[i] == ')'){
            while (!isEmpty(stack) && peek(stack) != '('){
                postfix[++k] = pop(stack);
            }
            if (!isEmpty(stack) && peek(stack) == '('){
                pop(stack);
            }else{
                printf("Invalid Expression\n");
                return;
            }
        }else if(is_operator(infix[i])){
            while(!isEmpty(stack) && get_precedence(infix[i]) <= get_precedence(stack)){
                postfix[++k] = pop(stack);
            }
            push(stack, infix[i]);
        }
    }
    while(!isEmpty(stack)){
        if(peek(stack) == '('){
            printf("Invalid Expression\n");
            return;
        }
        postfix[++k] = pop(stack);
    }
    postfix[++k] = '\0';
}
int main(){
    char infix[100];
    char postfix[100];

    printf("Enter an infix expression: ");
    fgets(infix, sizeof(infix), stdin);
    infix[strlen(infix) - 1] = '\0';

    infix_to_postfix(infix, postfix);
    if(strcmp(postfix, "") != 0){
        printf("Postfix expression: %s\n", postfix);
    }
    return 0;
}
