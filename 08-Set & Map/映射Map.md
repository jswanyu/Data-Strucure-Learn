# 映射Map

存储键值对的数据结构，根据键key寻找值value，有的语言中也称为字典，例如Python

其常用的操作有

```Java
public interface Map<K, V> {
    void add(K key, V value);
    V remove(K key);
    boolean contains(K key);
    V get(K key);
    void set(K key, V newValue);
    int getSize();
    boolean isEmpty();
}
```



## 自己实现Map

与集合类似的，可以使用链表和二分搜索树作为底层实现Map



### 基于二分搜索树实现Map

和Set实现的不同之处在于，之前树的节点上只有一个value，现在Map需要两个值，key和value，因此在构造、增删改查等操作上，需要考虑怎么用这两个值

也可以基于AVL树实现，平衡性更好，当然了树的结构里也要有键值对

```Java
public class BSTMap<K extends Comparable<K>, V> implements Map<K, V> {
    private class Node{
        public K key;
        public V value;
        public Node left, right;

        public Node(K key, V value){
            this.key = key;
            this.value = value;
            left = null;
            right = null;
        }
    }

    private Node root;
    private int size;

    public BSTMap(){
        root = null;
        size = 0;
    }

    // 向二分搜索树中添加新的元素(key, value)
    @Override
    public void add(K key, V value) {
        root = add(root,key,value);
    }

    // 向以node为根的二分搜索树中插入元素(key, value)，递归算法，返回新插入节点后二分搜索树的根
    private Node add(Node node, K key, V value){
        if(node == null){
            size++;
            return new Node(key,value);
        }

        if (key.compareTo(node.key)<0)
            node.left = add(node.left,key,value);
        else if(key.compareTo(node.key)>0)
            node.right = add(node.right,key,value);
        else  // key.compareTo(node.key)=0
            node.value = value;

        return node;
    }

    // 返回以node为根节点的二分搜索树中，key所在的节点
    private Node getNode(Node node, K key){
        if(node == null) return null;
        if(key.compareTo(node.key)==0)
            return node;
        else if (key.compareTo(node.key)<0)
            return getNode(node.left, key);
        else
            return getNode(node.right, key);
    }

    // 返回以node为根的二分搜索树的最小值所在的节点
    private Node minimum(Node node){
        if (node.left == null)
            return node;
        return minimum(node.left);
    }

    // 删除掉以node为根的二分搜索树中的最小节点
    // 返回删除节点后新二分搜索树的根
    private Node removeMin(Node node){
        if (node.left == null){
            Node rightNode = node.right;
            node.right = null;
            size--;
            return rightNode;
        }
        node.left = removeMin(node.left);
        return node;
    }


    @Override
    public V remove(K key) {
        Node node = getNode(root,key);
        if (node!=null){
            root = remove(root,key);
            return node.value;
        }
        return null;
    }

    // 删除以node为根的二分搜索树中值为e的节点，递归实现
    // 返回删除节点后新二分搜索树的根
    private Node remove(Node node, K key){
        if (node == null)
            return null;
        if (key.compareTo(node.key)<0){
            node.left = remove(node.left,key);
            return node;
        }
        else if (key.compareTo(node.key)>0){
            node.right = remove(node.right,key);
            return node;
        }
        else{ // key.compareTo(node.key)==0
            // 待删除节点的左子节点为空
            if (node.left == null){
                Node rightNode = node.right;
                node.right = null;
                size --;
                return rightNode;
            }

            // 待删除节点的右子节点为空
            if (node.right == null){
                Node leftNode = node.left;
                node.left = null;
                size --;
                return leftNode;
            }

            // 待删除节点的左右子树都不为空
            // 思路：找到比待删除节点大的最小节点，即待删除节点右子树的最小节点，用这个节点顶替待删除的节点的位置
            // 对照视频里的图片
            Node successor = minimum(node.right);
            successor.right = removeMin(node.right);  //removeMin中已经将size--了
            successor.left = node.left;
            // 将待删除节点置空
            node.left = node.right = null;

            return successor;
        }
    }

    @Override
    public boolean contains(K key) {
        return getNode(root,key)!=null;
    }

    @Override
    public V get(K key) {
        Node node = getNode(root,key);
        return node == null ? null : node.value;
    }

    @Override
    public void set(K key, V newValue) {
        Node node = getNode(root,key);
        if(node == null) throw new IllegalArgumentException(key + "doesn't exist!");
        node.value = newValue;
    }

    @Override
    public int getSize() {
        return size;
    }

    @Override
    public boolean isEmpty() {
        return size==0;
    }
}

```





### 基于链表实现Map

和Set实现的不同之处在于，之前链表的节点上只有一个value，现在Map需要两个值，key和value，因此在构造、增删改查等操作上，需要考虑怎么用这两个值

```Java
public class LinkedListMap<K, V> implements Map<K, V> {
    private class Node{
        public K key;
        public V value;
        public Node next;

        public Node(K key, V value, Node next){
            this.key = key;
            this.value = value;
            this.next = next;
        }

        public Node(K key){
            this(key,null,null);
        }

        public Node(){
            this(null,null,null);
        }

        @Override
        public String toString(){
            return key.toString() + ":" + value.toString();
        }
    }

    private Node dummyHead;
    private int size;

    public LinkedListMap(){
        dummyHead = new Node();
        size = 0;
    }

    private Node getNode(K key){
        Node cur = dummyHead.next;
        while(cur!=null){
            if (cur.key.equals(key)) return cur;
            cur = cur.next;
        }
        return null;
    }

    @Override
    public void add(K key, V value) {
        Node node = getNode(key);
        if(node == null){
            dummyHead.next = new Node(key,value,dummyHead.next);
            size++;
        } else{
            node.value = value;
        }
    }

    @Override
    public V remove(K key) {
        Node prev = dummyHead;
        while(prev.next != null){
            if (prev.next.key.equals(key)) break;
            prev = prev.next;
        }
        if(prev.next != null){
            Node delNode = prev.next;
            prev.next = delNode.next;
            delNode.next = null;
            return delNode.value;
        }

        return null;
    }

    @Override
    public boolean contains(K key) {
        return getNode(key)!=null;
    }

    @Override
    public V get(K key) {
        Node node = getNode(key);
        return node == null? null : node.value;
    }

    @Override
    public void set(K key, V newValue) {
        Node node = getNode(key);
        if (node==null) throw new IllegalArgumentException(key + "doesn't exist!");
        node.value = newValue;
    }

    @Override
    public int getSize() {
        return size;
    }

    @Override
    public boolean isEmpty() {
        return size==0;
    }
}

```





### 性能比较

在算法与数据结构体系课程-第8周-第2章-2-8视频中，作者读取了大文本的所有单词，将单词放到Map中，统计词频，也获得”傲慢“与”偏见“这两个词在整个大文本中出现了多少次，对于不同底层结构实现的Map来讲，完成的时间也不同。BST为底层的Map只用了0.74s，链表为底层的Map用了32.27s

集合主要操作的平均时间复杂度分析

|              | 链表 | BST                 |
| ------------ | ---- | ------------------- |
| 添加add      | O(n) | O(logn)，最差是O(n) |
| 删除remove   | O(n) | O(logn)，最差是O(n) |
| 修改set      | O(n) | O(logn)，最差是O(n) |
| 查找get      | O(n) | O(logn)，最差是O(n) |
| 查找contains | O(n) | O(logn)，最差是O(n) |

二分搜索树最差情况同样是O(n)级别



## Java标准库的Map

![image-20220405151252060](https://jswanyu-1309100582.cos.ap-shanghai.myqcloud.com/picgo/Java/Java%20SE/Java%E9%9B%86%E5%90%88-Map%E7%BB%A7%E6%89%BF%E5%9B%BE.png)

Map：双列数据，存储key-value对的数据。其组织框架为

*   HashMap：作为Map的主要实现类；线程不安全的，效率高；可以存储null的key和value
    *   LinkedHashMap：保证在遍历map元素时，可以按照添加的顺序实现遍历。因为使用了链表，对于频繁的遍历操作，效率高于HashMap
*   TreeMap：将key-value对进行排序，实现排序遍历。此时考虑key的自然排序或定制排序，底层使用红黑树
*   Hashtable：作为古老的实现类；线程安全的，效率低；不能存储null的key和value
    *   Properties：常用来处理配置文件。key和value都是String类型





## 多重映射

有时候也希望映射中的key是可以重复的，这种映射被称为多重映射

暂时只作了解





# 集合和映射的关系

由于映射的Key是不可以重复的，这和集合是一致的，所以我们通常使用映射去构建集合

**Set其实就是Map中所有key对应的value都为null**
