#ifndef CH09_SIMPLE_EXPRESSION_H
#define CH09_SIMPLE_EXPRESSION_H

#include <string>
#include <stack>
#include <map>
#include <vector>
#include <cctype>

class SimpleExpression {
 public:
  using PosType = std::string::size_type;
  /**
   * 读取表达式文件 和 表达式优先级文件
   */
  SimpleExpression(const std::string &expression_filename, 
                   const std::string &operation_priority_filename);
  /**
   * 读取指定字符位置的数字, 包括浮点数
   */
  PosType ReadNumber(const std::string &number_str, PosType start_pos,
                            std::stack<double, std::vector<double>> &opn);
  /**
   * 读取指定字符位置的操作符, 并进行处理
   */
  PosType ReadOperation(
      const std::string &expression_str, PosType start_pos,
      std::stack<std::string, std::vector<std::string>> &operations,
      std::stack<double, std::vector<double>> &numbers);
  /**
   * 解析
   */
  double Parse();
  /**
   *  计算结果 一元操作符
   */
  double Calc(std::string &op, double number);
  /**
   *  计算结果 二元操作符
   */
  double Calc(double number1, std::string &op, double number2);
  /**
   * 打印优先级表
   */
  void ShowPriorityTable();

  const std::string &get_expression_str() { return expression_str_; }
  /**
   * 可解析操作符的个数
   */
  static const int OperationSize = 9;
  /**
   * 判断 栈顶 和 当前运算符的优先级 表
   */
  std::map<std::string, std::map<std::string, std::string>> PriorityBetween;

 private: 
  std::string expression_str_;
};

#endif