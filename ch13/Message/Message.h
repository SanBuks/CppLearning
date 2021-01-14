#pragma once
#include <string>
#include <set>
class Folder;
class Message{
	friend class Folder;
	friend void swap(Message &, Message &);
private:
	std::string contents;       // 内容
	std::set<Folder*> folders;  // 包含所有存有本消息的文件夹
	
	// 拷贝构造 和 拷贝赋值 所需的公共操作
	void add_to_Folders(const Message &); // 将本信息添加到包含另外信息的所有文件夹中
	void remove_from_Folders();  // 将本信息从所有文件夹中删除
	void move_Folders(Message *);  // 移动folders 更新folder对象可能会抛出异常
public:
	Message(const std::string &str=""):contents(str){}
	~Message();  // 三个拷贝控制
	Message(const Message &);
	Message(Message &&);
	Message &operator=(const Message &);
	Message &operator=(Message &&);

	void save(Folder &);  // 将本信息添加到指定文件夹中
	void remove(Folder &); // 将本信息从指定文件夹中删除
	void print();
};
