#include <iostream>
#include <fstream>
#include <string>

// 用途:
// - 提取出 markdown 文档的 代码, 供格式转化
// - 恢复原来的 markdown 文档

// 自定义 行注释标记
const std::string &GetMyCommentFlag()
{
  static const std::string kCommentFlag("//+++***");
  return kCommentFlag;
}

// 判断是否是 code_fence
inline bool IsCodeLine(const std::string &line) {
  if (line.size() >= 3 && line[0] == '`' && line[1] == '`' && line[2] == '`') {
    return true;
  } else {
    return false;
  }
}

// 判断是否含有 行注释标记
inline bool HasCommentFlag(std::string &line) {
  if (line.size() >= GetMyCommentFlag().size() &&
      line.substr(0, GetMyCommentFlag().size()) == GetMyCommentFlag()) {
    return true;
  } else {
    return false;
  }
}

// 插入 & 删除 行注释标记
std::string &InsertCommentFlag(std::string &line) {
  return line.insert(0, GetMyCommentFlag());
}
std::string &RemoveCommentFlag(std::string &line) {
  return line.erase(0, GetMyCommentFlag().size());
}

// 恢复 markdown  文档
int RestoreMd() {
  std::string filename;
  std::cout << "Input your file name that to be restored: \n";
  std::cin >> filename;

  std::ifstream ifs(filename);
  if (!ifs) {
    std::cout << "Can't open file!\n";
    return 1;
  }

  std::ofstream ofs("restored.md");
  if (!ofs) {
    std::cout << "Can't create output file!\n";
    return 1;
  }

  std::string line;

  while(getline(ifs, line)) {
    // 将行注释标记删除
    if (HasCommentFlag(line)) {
      ofs << RemoveCommentFlag(line) << "\n";
    } else {
      ofs << line << "\n";
    }
  }
  return 0;
}

int ProcessMd() {
  std::string filename;
  std::cout << "Input your file name that to be processed : \n";
  std::cin >> filename;

  std::ifstream ifs(filename);
  if (!ifs) {
    std::cout << "Can't open file!\n";
    return 1;
  }

  std::ofstream ofs("processed.cc");
  if (!ofs) {
    std::cout << "Can't create output file!\n";
    return 1;
  }

  std::string line;
  bool code_line_flag = false;

  while(getline(ifs, line)) {
    // 如果是 code_fence 内的代码
    if (code_line_flag) {
      // 如果是 code_fence 注释结束符
      if (IsCodeLine(line)) {
        ofs << InsertCommentFlag(line) << "\n";
        code_line_flag = false;
      } else {
        ofs << line << "\n";
      }
    // 如果是正常文本
    } else {
      code_line_flag = IsCodeLine(line);
      ofs << InsertCommentFlag(line) << "\n";
    }
  }
  return 0;
}

void HelpMessage() {
  std::cout << "use `-1` to process markdown file \n"
            << "use `-2` to restore processed file \n";
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    HelpMessage();
  } else {
    if (std::string(argv[1]) == "-1") {
      return ProcessMd();
    } else if (std::string(argv[1]) == "-2") {
      return RestoreMd();
    } else if (std::string(argv[1]) == "-h") {
      HelpMessage();
      return 0;
    } else {
      HelpMessage();
      return 1;
    }
  }
}