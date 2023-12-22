# 1. 标准对话框
## 1.1 QFileDialog
### 过滤格式
```c++
// 字符为提示字符
// ;; 作为分割 
// () 内为过滤格式
QString filter = "文本文件(*.txt);;所有图片(*.png *.jpg);;所有文件(*.*)";
```

### 获取当前目录
```c++
auto dir = QDir::currentPath();
auto dir = QApplication::applicationDirPath();
```

### 相关函数
```c++
// 获取文件, 多个文件, 保存文件路径:
// this 表示父对象
// title 对话框标题, dir 当前目录, filter 过滤格式
auto file_name = QFileDialog::getOpenFileName(this, title, dir, filter);
auto file_names = QFileDialog::getOpenFileNames(this, title, dir, filter);
auto file_name = QFileDialog::getSaveFileName(this, title, dir, filter);

// 仅获取目录路径
auto dir_name = QFileDialog::getExistingDirectory(this, title, dir, 
                                                  QFileDialog::ShowDirsOnly);
```

## 1.2 QColorDialog
### 获取颜色
```c++
// 设定获取颜色的来源
QPalette::ColorRole color_role = QPalette::Text;  // 文字
QPalette::ColorRole color_role = QPalette::Base;  // 背景

auto palette = ui->plainTextEdit->palette();
auto init_color = palette.color(color_role);
auto color = QColorDialog::getColor(init_color, this, "选择颜色");
if (color.isValid()) {
  palette.setColor(color_role, color);
  ui->plainTextEdit->setPalette(palette);         // 设定输入框的字体颜色
}
```

## 1.3 QFontDialog
### 获取字体
```c++
bool ok = false;
auto init_font = ui->plainTextEdit->font();
auto font = QFontDialog::getFont(&ok, init_font);
if (ok) {
  ui->plainTextEdit->setFont(font);               // 设定输入框的字体颜色
}
```