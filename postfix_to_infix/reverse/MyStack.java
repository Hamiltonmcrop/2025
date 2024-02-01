// MyStack.java

import java.util.Stack;

public class MyStack {
    private Node top;

    private static class Node {
        String expression;
        Node next;

        Node(String expression) {
            this.expression = expression;
            this.next = null;
        }
    }

    MyStack() {
        top = null;
    }

    void infixToPostfix(String infix) {
        StringBuilder postfix = new StringBuilder();
        Stack<String> operators = new Stack<>();

        for (int i = 0; i < infix.length(); i++) {
            char currentChar = infix.charAt(i);

            if (Character.isAlphabetic(currentChar)) {
                postfix.append(currentChar);
            } else if (currentChar == '(') {
                operators.push("(");
            } else if (currentChar == ')') {
                while (!operators.isEmpty() && !operators.peek().equals("(")) {
                    postfix.append(" ").append(operators.pop());
                }
                operators.pop();
            } else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
                while (!operators.isEmpty() && !operators.peek().equals("(") &&
                        hasHigherOrEqualPrecedence(operators.peek(), currentChar)) {
                    postfix.append(" ").append(operators.pop());
                }
                operators.push(String.valueOf(currentChar));
            }
        }

        while (!operators.isEmpty()) {
            postfix.append(" ").append(operators.pop());
        }

        System.out.println(postfix);
    }

    String first() {
        if (top == null) {
            System.out.println("no expressions in stack");
            System.exit(-1);
        }
        return top.expression;
    }

    void pop() {
        if (top == null) {
            System.out.println("too many operators");
            return;
        }
        Node temp = top;
        top = top.next;
        temp.next = null;
    }

    void push(String s) {
        Node temp = new Node(s);
        temp.next = top;
        top = temp;
    }

    void print() {
        if (top.next != null) {
            System.out.println("too many operands");
            return;
        }
        System.out.println(top.expression);
    }

    private boolean hasHigherOrEqualPrecedence(String op1, char op2) {
        int precedenceOp1 = getOperatorPrecedence(op1.charAt(0));
        int precedenceOp2 = getOperatorPrecedence(op2);

        return (precedenceOp1 >= precedenceOp2);
    }

    private int getOperatorPrecedence(char op) {
        if (op == '+' || op == '-') {
            return 1;
        } else if (op == '*' || op == '/') {
            return 2;
        }
        return 0;
    }

    public static void main(String[] args) {
        String infix = "";
        String answer = "y";
        MyStack s = new MyStack();

        do {
            System.out.println("Please enter an infix expression: ");
            infix = System.console().readLine();
            s.infixToPostfix(infix);
            System.out.print("Enter another expression? (y/n): ");
            answer = System.console().readLine();
        } while (answer.equalsIgnoreCase("y"));
    }
}

