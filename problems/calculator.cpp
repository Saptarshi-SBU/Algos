/*---------------------------------------------------------------------------------
 * Copyright(C) 2017 by Saptarshi Sen
 *
 * Calculator. Computes expressions. Supports braces, signed integers.
 * Probably can act as the backend calculator of any GUI
 *
 * Algorithm :
 *    +)Convert to Postfix, easy to evaluate operands using binary operator
 *    +)Take care of operator precedence, order manifested through operator stack.
 *      For higher order, update operator stack immediately; otherwise reduce
 *      current expression and then update operator stack with current operator.
 *    +)Always, Bottom up. (prevent stack overflow, otherwise for large
 *      expressions can end up with large expression trees). So Reduce as soon
 *      as witnessed higher order and go.
 *
 * Complexity : O(n)
 *
 * Basic Calculator : https://leetcode.com/submissions/detail/132635910/
 *
 * Basic Calculator II : https://leetcode.com/submissions/detail/132547243/
 * ------------------------------------------------------------------------------*/

#include <stack>
#include <string>
#include <cassert>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <unordered_set>

#define CPPUNIT_ASSERT_MESSAGE(message, condition) \
   do { \
      assert(condition); \
      std::cout << message << std::endl; \
   } while (0);

#define LOGOPREATION(op, op1, op2, out) \
   do { \
        printf("%f %c %f = %f\n", op1, op, op2, out); \
   } while (0);

using namespace std;

class Calculator {
private:
     stack<string> compute_stack, operator_stack;

     // static const gives error, violates C++ Standard
     const unordered_set<char> operators = { '+', '-', '*', '/' };

public:
     Calculator() {}
    ~Calculator() {}

     // valid for signed integers
     inline bool isSignedOp(const char input) {
       return (input == '+' || input == '-');
     }

     // Checks if operand in compute stack is a valid integer
     bool isNumeric(const std::string& input) {
       // does not allow non const iterator
       std::string::const_iterator it = input.begin();
       if (isSignedOp(*it)) { it++; }
       return (it == input.end()) ? false :
           std::all_of(it, input.end(), ::isdigit);
     }

     // Checks if operator in operator stack is a valid operator
     bool isOperator(const char input) {
       return operators.find(input) != operators.end();
     }

     // if 'to' has higher precedence than 'with', return true
     bool Order(char to, char with)
     {
         bool addOperator = false;

         if (to == with) {
            addOperator = false;
         } else if (to == '/') {
            addOperator = (with != '*') ? true : false;
         } else if (to == '*') {
            addOperator = (with != '/') ? true : false;
         } else if ((to == '+') || (to == '-')) {
            addOperator = false;
         }
         return addOperator;
     }

     // Does not handle overflow conditions.
     double Compute(double op1, double op2, char op)
     {
        double result = 0;
        if (op == '+') {
           result = op1 + op2;
        } else if (op == '-') {
           result = op2 - op1;
        } else if (op == '*') {
           result = op1 * op2;
        } else if (op == '/') {
           result = op2 / op1;
           #ifdef LEETCODE
           result = trunc(result);
           #endif
        } else {
           throw std::invalid_argument(string("invalid operator"));
        }
        //LOGOPREATION(op, op1, op2, result);
        return result;
     }

     void ReduceSingle(void)
     {
        double result;
        string op = operator_stack.top();
        operator_stack.pop();
        if (compute_stack.size() < 2) {
           throw std::logic_error("expected at least 2 operands");
        }
        string op1 = compute_stack.top();
        compute_stack.pop();
        string op2 = compute_stack.top();
        compute_stack.pop();
        result = Compute(atof(op1.c_str()), atof(op2.c_str()), *op.c_str());
        compute_stack.push(std::to_string(result));
     }

     void ReduceAll(void)
     {
	    while (!operator_stack.empty()) {
            ReduceSingle();
        }
     }

     void AddOperand(string &op, string &signedop)
     {
        if (op.length()) {
           if (signedop.size()) {
              op = signedop + op;
              signedop.clear();
           }
           compute_stack.push(op);
           op.clear();
        }
     }

     double Calculate(string exp)
     {
        double result = 0;
	    string op, signedop;
        bool backingoperator = false; // for signed integers(TBD improve)

        if (!exp.length()) {
           throw std::invalid_argument(string("expression empty"));
        }

        for (auto &i : exp) {
           // empty space
           if ((i == ' ') || (i == '\n') || (i == '\t')) {
              continue;
           // operand
           } else if (isdigit(i)) {
              op.append(1, i);
              backingoperator = false;
           // operator
           } else {
              // push outstanding operand to compute stack
              AddOperand(op, signedop);

              // logic for detecting signed operands
              if ((backingoperator || compute_stack.empty()) && isSignedOp(i)) {
                 assert(signedop.empty());
                 signedop = i;
                 continue;
              }

              backingoperator = true;

              // Special case
              if ((operator_stack.empty() || operator_stack.top() == "(")
                 && isOperator(i)) {
                 operator_stack.push(string(1, i));
              // regular case
              } else {
                 if (i == '(') {
                    operator_stack.push(string(1, i));
                 } else if (i == ')') {
                    backingoperator = false;
                    while (operator_stack.top() != "(") {
                       ReduceSingle();
                       if (operator_stack.empty()) {
                          throw std::invalid_argument("found unpaired braces");
                       }
                    }
                    operator_stack.pop();
                 } else {
                    assert(isOperator(i));
                    while (!operator_stack.empty()) {
                       string optor = operator_stack.top();
                       // Check precedence
                       if (Order(i, *optor.c_str()) || (optor.compare("(") == 0)) {
                          break;
                       }
                       ReduceSingle();
                    }
                    operator_stack.push(string(1, i));
                 }
              }
           }
        }

        AddOperand(op, signedop);
        ReduceAll();
        evalString = compute_stack.top();
        result = atof(evalString.c_str());
        compute_stack.pop();
        assert(compute_stack.empty());
        return result;
     }

     void DumpStack(stack<string> stack)
     {
        std::cout << "postfix notation" << std::endl;
        while (!stack.empty()) {
           std::cout << stack.top() << " ";
           stack.pop();
        }
        std::cout << std::endl;
     }
};

void TestA(void)
{
   Calculator sol;
   const std::string exp("1+2");
   long ans = static_cast<long>(round(sol.Calculate(exp)));
   CPPUNIT_ASSERT_MESSAGE("TestA passed", (ans == 3));
}

void TestB(void)
{
   Calculator sol;
   const std::string exp("1+2-3");
   long ans = static_cast<long>(round(sol.Calculate(exp)));
   CPPUNIT_ASSERT_MESSAGE("TestB passed", (ans == 0));
}

void TestC(void)
{
   Calculator sol;
   const std::string exp("1+2*3");
   long ans = static_cast<long>(round(sol.Calculate(exp)));
   CPPUNIT_ASSERT_MESSAGE("TestC passed", (ans == 7));
}

void TestD(void)
{
   Calculator sol;
   const std::string exp("(1+2)*3");
   long ans = static_cast<long>(round(sol.Calculate(exp)));
   CPPUNIT_ASSERT_MESSAGE("TestD passed", (ans == 9));
}

void TestE(void)
{
   Calculator sol;
   const std::string exp("(1+2)*(3+2)");
   long ans = static_cast<long>(round(sol.Calculate(exp)));
   CPPUNIT_ASSERT_MESSAGE("TestE passed", (ans == 15));
}

void TestF(void)
{
   Calculator sol;
   const std::string exp("(((1+2)*3)+2)");
   long ans = static_cast<long>(round(sol.Calculate(exp)));
   CPPUNIT_ASSERT_MESSAGE("TestF passed", (ans == 11));
}

void TestG(void)
{
   Calculator sol;
   const std::string exp("(((1+20)*3)+2)");
   long ans = static_cast<long>(round(sol.Calculate(exp)));
   CPPUNIT_ASSERT_MESSAGE("TestG passed", (ans == 65));
}

void TestH(void)
{
   long ans;
   Calculator sol;
   ans = sol.Calculate("(((-1+20)*3)+2)");
   CPPUNIT_ASSERT_MESSAGE("TestH passed", (ans == 59));
}

void TestI(void)
{
   Calculator sol;
   const std::string exp("-5*-2");
   long ans = static_cast<long>(round(sol.Calculate(exp)));
   CPPUNIT_ASSERT_MESSAGE("TestI passed", (ans == 10));
}

void TestJ(void)
{
   Calculator sol;
   const std::string exp("-5*(-2)");
   long ans = static_cast<long>(round(sol.Calculate(exp)));
   CPPUNIT_ASSERT_MESSAGE("TestJ passed", (ans == 10));
}

void TestK(void)
{
   Calculator sol;
   const std::string exp("-5*(-2 + 1)");
   long ans = static_cast<long>(round(sol.Calculate(exp)));
   CPPUNIT_ASSERT_MESSAGE("TestK passed", (ans == 5));
}

void TestL(void)
{
   Calculator sol;
   const std::string exp("(17*15)/18");
   long ans = static_cast<long>(round(sol.Calculate(exp)));
   CPPUNIT_ASSERT_MESSAGE("TestL passed", (ans == 14));
}

void TestM(void)
{
   Calculator sol;
   const std::string exp("(((17*-15)/18+36)*18) + 5");
   long ans = static_cast<long>(round(sol.Calculate(exp)));
   CPPUNIT_ASSERT_MESSAGE("TestM passed", (ans == 398));
}

void TestN(void)
{
   Calculator sol;
   const std::string exp("17*-15/18");
   long ans = static_cast<long>(round(sol.Calculate(exp)));
   CPPUNIT_ASSERT_MESSAGE("TestN passed", (ans == -14));
}

void TestO(void)
{
   Calculator sol;
   const std::string exp("1-3");
   long ans = static_cast<long>(round(sol.Calculate(exp)));
   CPPUNIT_ASSERT_MESSAGE("TestO passed", (ans == -2));
}

void TestP(void)
{
   Calculator sol;
   const std::string exp("1-1+1");
   long ans = static_cast<long>(round(sol.Calculate(exp)));
   CPPUNIT_ASSERT_MESSAGE("TestP passed", (ans == 1));
}

void TestQ(void)
{
   string s, exp;
   Calculator sol;
   ifstream ifile("load.txt");
   while (ifile >> s) { exp.append(s); }
   long ans = static_cast<long>(round(sol.Calculate(exp)));
   CPPUNIT_ASSERT_MESSAGE("TestQ passed", (ans == 202));
}

void TestR(void)
{
   Calculator sol;
   const std::string exp("2-4-(8+2-6+(8+4-(1)+8-10))");
   long ans = static_cast<long>(round(sol.Calculate(exp)));
   CPPUNIT_ASSERT_MESSAGE("TestR passed", (ans == -15));
}

void TestS(void)
{
   Calculator sol;
   const std::string exp("2-4-(8+2-6)");
   long ans = static_cast<long>(round(sol.Calculate(exp)));
   CPPUNIT_ASSERT_MESSAGE("TestS passed", (ans == -6));
}

int main(void) {
   TestA();
   TestB();
   TestC();
   TestD();
   TestE();
   TestF();
   TestG();
   TestH();
   TestI();
   TestJ();
   TestK();
   TestL();
   TestM();
   TestN();
   TestO();
   TestP();
   TestQ();
   TestR();
   TestS();
   return 0;
}
