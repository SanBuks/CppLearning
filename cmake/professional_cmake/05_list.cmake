set(myList a b c)

list(LENGTH myList len)
message("length = ${len}")

list(GET myList 2 1 letters)
message("letters = ${letters}")

list(INSERT myList 2 X Y Z)
message("myList = ${myList}")

list(APPEND myList d e f f)
message("myList = ${myList}")

list(PREPEND myList P Q R)
message("myList = ${myList}")

list(FIND myList f index)
message("index = ${index}")

list(REMOVE_ITEM myList X Y)
message("myList = ${myList}")

list(REMOVE_AT myList 0 1)
message("myList = ${myList}")

list(REMOVE_DUPLICATES myList)
message("myList = ${myList}")

list(POP_FRONT myList first second third)
message("first = ${first} " "second = ${second} " "third = ${third} ")
list(POP_BACK myList first second third)
message("first = ${first} " "second = ${second} " "third = ${third} ")

list(REVERSE myList)
message("myList = ${myList}")

set(myList 1 a b c 3 z f 0 7 9)
list(SORT myList
  COMPARE NATURAL
  CASE INSENSITIVE
  ORDER ASCENDING
)
message("myList = ${myList}")

#COMPARE
  #STRING 按字母顺序排序
  #FILE_BASENAME 排序方法是假设每个项都是路径，并且应该只根据路径的文件名 (去除目录) 来排序。
  #NATURAL 类似于 STRING，除了一个项中的连续数字是按数字排序的
#CASE 关键字表示对大小写 SENSITIVE 或 INSENSITIVE(敏感或不敏感)
#ORDER 关键字表示是 ASCENDING 或 DESCENDING