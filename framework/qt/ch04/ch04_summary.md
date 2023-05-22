## 4.8 QTableWidget
### 设置表头
```c++
// 设置表头列数
ui->tableWidget->setColumnCount(header.count());
// 设置表头列文字 
QStringList header;
header << "姓名" << "性别" << "出生日期" << "民族" << "是否是党员" << "分数";
// 逐列设置 item
item = new QTableWidgetItem(header.at(i));
ui->tableWidget->setHorizontalHeaderItem(i, item);
```

### 生成多行未初始化数据
```c++
ui->tableWidget->setRowCount(10);                // 设定 10 行数据
```

### 设置底色
```c++
ui->tableWidget->setAlternatingRowColors(true);  // 设定 底色
```

### 修改一行数据
```c++
QTableWidgetItem *item;
item = new QTableWidgetItem(text, CType);       // 设定显示文字, type

item->setData(Qt::UserRole, QVariant(kStuId));  // 设定自定义数据
item->setCheckState(Qt::Checked);               // 设定选择框
item->setBackground(Qt::yellow);                // 设定背景颜色
item->setTextAlignment(Qt::AlignHCenter);       // 设定文字对齐方式
item->setIcon(icon);                            // 设定图标

ui->tableWidget->setItem(row, COLIndex, item);  // 根据行列设定 item
// 如此反复创建一行数据
```

### 新增与删除一行
```c++
// QTableWidget 是 0-index 
ui->tableWidget->insertRow(row_count); // 在 row_count 新增一行
ui->tableWidget->removeRow(cur_row);   // 删除第 row 行数据
```

### 自适应
```c++
ui->tableWidget->resizeRowsToContents();     // 高度自适应 
ui->tableWidget->resizeColumnsToContents();  // 宽度自适应
```

### 读取
```c++
str += " " + ui->tableWidget->item(i, j)->text();
// item(row, column): 按 row, column 返回 item, 非法则返回 nullptr
// itemAt(x, y): 按坐标 x, y 返回 item, 非法或不在可视区域内返回 nullptr
```

### 其他属性
```c++
// 设置可编辑
ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked |
                                 QAbstractItemView::SelectedClicked);
// 设置不可编辑
ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

// 设置列头和行头可见性
ui->tableWidget->horizontalHeader()->setVisible(checked);
ui->tableWidget->verticalHeader()->setVisible(checked);

// 设置选中模式
ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

// 单元格改变信号
void currentCellChanged(int currentRow, int currentColumn,
                        int previousRow, int previousColumn);
```

