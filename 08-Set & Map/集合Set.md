# 集合

集合（set）是由一个或数个形态各异的大小整体组成的，构成集合的事物或对象称作元素或是成员。

基本功能：

```Java
public interface Set<E> {
    void add(E e);
    void remove(E e);
    boolean contains(E e);
    int getSize();
    boolean isEmpty();
}
```





## 自己实现集合

### 基于二分搜索树实现集合

前面实现的二分搜索树（不带重复元素）其实天然的具备集合的功能，可以基于二分搜索树实现集合

```Java
// 基于二分搜索树的集合类
public class BSTSet <E extends  Comparable<E>> implements Set<E>{
    private BinarySearchTree<E> bst;

    public BSTSet() {
        bst = new BinarySearchTree<>();
    }

    @Override
    public void add(E e) {
        bst.add(e);
    }

    @Override
    public void remove(E e) {
        bst.remove(e);
    }

    @Override
    public boolean contains(E e) {
        return bst.contains(e);
    }

    @Override
    public int getSize() {
        return bst.size();
    }

    @Override
    public boolean isEmpty() {
        return bst.isEmpty();
    }
}
```





### 基于链表实现集合

BST和链表都属于动态数据结构，链表也可以实现集合类

```Java
public class LinkedListSet<E> implements Set<E>{
    private LinkedList<E> list;

    public LinkedListSet() {
        list = new LinkedList<>();
    }

    @Override
    public void add(E e) {
        if(!contains(e))
            list.addFirst(e); // 链表头添加元素复杂度为O(1)
    }

    @Override
    public void remove(E e) {
        list.removeElement(e);
    }

    @Override
    public boolean contains(E e) {
        return list.contains(e);
    }

    @Override
    public int getSize() {
        return list.getsize();
    }

    @Override
    public boolean isEmpty() {
        return list.isEmpty();
    }
}
```





### 基于哈希表实现集合

暂时略



### 性能对比

在算法与数据结构体系课程-第8周-第2章-2-2视频中，作者读取了大文本的所有单词，将单词放到集合中，统计词频，对于不同底层结构实现的集合来讲，完成的时间也不同。BST为底层的集合只用了0.66s，链表为底层的集合用了5.24s

集合主要操作的平均时间复杂度分析

|      | 链表 | BST     |
| ---- | ---- | ------- |
| 添加 | O(n) | O(logn) |
| 查找 | O(n) | O(logn) |
| 删除 | O(n) | O(logn) |

其中，链表虽然是在头添加，但要先遍历一遍链表确保没有重复元素，所以其实也是O(n)，查找删除也是O(n)

BST由于其二叉树的结构，让这三个操作的复杂度都是  O(h)，h即为二叉树的高度，logn级别

值得一提的是，二分搜索树最差的情况其实也是一个链表，那样的话各种操作的时间复杂度也是  O(n)

![image-20220427123633151](https://jswanyu-1309100582.cos.ap-shanghai.myqcloud.com/picgo/DataStructure%20and%20Algorithm/%E4%BA%8C%E5%8F%89%E6%A0%91-%E4%BA%8C%E5%88%86%E6%90%9C%E7%B4%A2%E6%A0%91%E7%9A%84%E6%9C%80%E5%9D%8F%E6%83%85%E5%86%B5.png)







## Java标准库的集合

<img src="https://jswanyu-1309100582.cos.ap-shanghai.myqcloud.com/picgo/Java/Java%20SE/Java%E9%9B%86%E5%90%88-Collection%E7%BB%A7%E6%89%BF%E5%9B%BE.png" alt="Java集合-Collection继承图" style="zoom:150%;" />

Java标准库也有实现Set的类，分别为

* HashSet：作为Set接口的主要实现类；线程不安全的；可以存储null值，存入的元素是无序的（底层是哈希表，哈希表保证了元素的唯一性）
    * LinkedHashSet：作为HashSet的子类，元素严格按照放入的顺序排列，**对于频繁的遍历操作，LinkedHashSet效率高于HashSet，添加、删除操作时间复杂度都是O(1).**（底层数据结构由哈希表和链表组成，链表保证了元素的有序即存储和取出一致，哈希表保证了元素的唯一性）
* TreeSet：TreeSet中不能有相同元素，不可以有Null元素，根据元素的自然顺序进行排序或者按照添加对象的指定属性进行排序，非线程安全。添加、删除操作时间复杂度都是O(logn)，而不像用二分搜索树那样最坏到O(n)的情况（底层的数据结构是红黑树）





## 多重集合

有时候也希望集合中的元素是可以重复的，这种集合被称为多重集合

暂时只作了解



