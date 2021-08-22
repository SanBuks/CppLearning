#include "simple_expression.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <exception>
#include <memory>
#include <cstdio>
#include <cmath>

#include "common.h"

SimpleExpression::SimpleExpression(
    const std::string &expression_filename, 
    const std::string &operation_priority_filename) : PriorityBetween() {
  // 获取表达式
  std::ifstream ifs(expression_filename);
  if (ifs) {
    getline(ifs, expression_str_);
    expression_str_.append(1, '#');
  } else {
    ifs.close();
    throw std::runtime_error("[SimpleExpression] : "
                             "Can't Read Expression File!");
  }
  // 获取优先级表
  ifs.close();
  ifs.open(operation_priority_filename);
  try {
    std::string operation;
    std::vector<std::string> expr_operations;
    for (int i = 0; i < OperationSize; ++i) {
      ifs >> operation;
      expr_operations.push_back(operation);
      PriorityBetween.insert({operation, std::map<std::string, std::string>()});
    }
    std::string priority;
    for (int i = 0; i < OperationSize; ++i) {
      // stack operation
      ifs >> operation;
      for (int j = 0; j < OperationSize; ++j) {
        ifs >> priority;
        if (PriorityBetween.find(operation) != PriorityBetween.end()) {
          PriorityBetween[operation][expr_operations[j]] = priority;
        } else {
          throw std::runtime_error("[SimpleExpression] : "
                                   "Not Correct Priority File");
        }
      }
    }
  } catch (std::exception &ex) {
    ifs.close();
    std::cout << ex.what() << "\n";
    throw std::runtime_error("[SimpleExpression] : Can't Read Priority File!");
  }
}

SimpleExpression::PosType SimpleExpression::ReadNumber(
    const std::string &number_str, 
    PosType start_pos,
    std::stack<double, std::vector<double>> &opn) {
  PosType pos = start_pos;
  opn.emplace(0.0);
  // 处理 整数 部分
  PosType end_pos = number_str.size();
  while (pos < end_pos && std::isdigit(number_str[pos])) {
    opn.top() *= 10.0F;
    opn.top() += number_str[pos] - '0';
    ++pos;
  }
  // 处理 小数 部分
  if (pos < end_pos && number_str[pos] == '.') {
    if (pos + 1 < end_pos && std::isdigit(number_str[pos + 1])) {
      double weight = 0.1;
      while (pos < end_pos && std::isdigit(number_str[++pos])) {
        opn.top() += weight * (number_str[pos] - '0');
        weight *= 0.1;
      }
    } else {
      auto error_msg = cpp_primer::string_format(
        "[ReadNumber] : Can't Read Float Number!\nAt [%d] Position\n", 
        pos);
      throw std::runtime_error(error_msg);
    }
  }
  return pos;
}

SimpleExpression::PosType SimpleExpression::ReadOperation(
    const std::string &expression_str, PosType start_pos,
    std::stack<std::string, std::vector<std::string>> &operations,
    std::stack<double, std::vector<double>> &numbers) {
  PosType pos = start_pos;
  // 获取当前操作符
  std::string current_operation;
  std::string valid_operation;
  while (!std::isdigit(expression_str[pos]) && 
         !std::isblank(expression_str[pos])) {
    current_operation.append(1, expression_str[pos++]);
    if (PriorityBetween.find(current_operation) != PriorityBetween.end()) {
      valid_operation = current_operation;
    }
  }
  pos -= current_operation.size() - valid_operation.size();
  current_operation = valid_operation;
  if (PriorityBetween.find(current_operation) != PriorityBetween.end()) {
    std::string &stack_operation = operations.top();
    if (PriorityBetween[stack_operation][current_operation] == "<") {
      operations.push(current_operation);
    } else if (PriorityBetween[stack_operation][current_operation] == "=") {
      operations.pop();
    } else if (PriorityBetween[stack_operation][current_operation] == ">") {
      if (stack_operation == "!") {
        double number = numbers.top(); numbers.pop();
        double result = Calc(stack_operation, number);
        numbers.push(result);
      } else {
        double number2 = numbers.top(); numbers.pop();
        double number1 = numbers.top(); numbers.pop();
        double result = Calc(number1, stack_operation, number2);
        numbers.push(result);
      }
        operations.pop();
        --pos;
    } else {
      auto error_msg = cpp_primer::string_format(
        "[ReadOperation] : Error Operation!\nAt [%d] Position\n", pos);
      throw std::runtime_error(error_msg);
    }
  } else {
    auto error_msg = cpp_primer::string_format(
      "[ReadOperation] : Error Operation!\nAt [%d] Position\n", pos);
    throw std::runtime_error(error_msg);
  }
  return pos;
}

void SimpleExpression::ShowPriorityTable() {
  for (auto it = PriorityBetween.begin(); it != PriorityBetween.end(); ++it) {
    for (auto jt = it->second.begin(); jt != it->second.end(); ++jt) {
      std::cout << it->first << " - " << jt->first 
                             << " : " << jt->second << "\n";
    }
    std::cout << "-----------\n";
  }
}

double SimpleExpression::Parse() {
  std::stack<double, std::vector<double>> number_stack;
  std::stack<std::string, std::vector<std::string>> operation_stack;
  operation_stack.push("#");
  PosType pos = 0; 
  while (pos < expression_str_.size()) {
    // 忽略空白符
    while (std::isblank(expression_str_[pos])) {
      ++pos;
    }
    // 处理数字
    if (std::isdigit(expression_str_[pos])) {
      pos = ReadNumber(expression_str_, pos, number_stack);
    // 处理操作符
    } else {
      pos = ReadOperation(expression_str_, pos, operation_stack, number_stack);
    }
  }
  if (operation_stack.empty() && number_stack.size() == 1) {
    return number_stack.top();
  } else {
    throw std::runtime_error("[Parse] : Wrong Parsing!");
  }
}

double SimpleExpression::Calc(std::string &op, double number) {
  double result = 0.0F; 
  if (op == "!") {
    result = 1.0F;
    if (std::fmod(number, 1.0F) == 0.0F) {
      while (number > 0.0) {
        result *= number--; 
      } 
      return result;
    } else {
      throw std::runtime_error("[Clac] : Factorial Should Be An Integer!");
    }
  } else {
    throw std::runtime_error("[Clac] : Unknown Operation!");
  }
}

double SimpleExpression::Calc(double number1, std::string &op, double number2) {
  if (op == "+") {
    return number1 + number2;
  } else if (op == "-") {
    return number1 - number2;
  } else if (op == "*") {
    return number1 * number2;
  } else if (op == "/") {
    if (std::abs(number2 - 0) < 0.00000000001F) {
      throw std::runtime_error("[Clac] : Denominator Should Not Be Zero!");
    }
    return number1 / number2;
  } else if (op == "^") {
    return std::pow(number1, number2);
  } else {
    throw std::runtime_error("[Clac] : Unknown Operation!");
  }
}

int main () {
  std::string expression_filename = "../ch09_data/expression.txt"; 
  std::string priority_filename = "../ch09_data/operation_priority.txt";
  try {
    SimpleExpression expr(expression_filename, priority_filename);
    std::cout << expr.get_expression_str() << "\n";
    std::cout << expr.Parse() << "\n";
  } catch (std::exception &ex) {
    std::cout << ex.what();
  }
  return 0;
}