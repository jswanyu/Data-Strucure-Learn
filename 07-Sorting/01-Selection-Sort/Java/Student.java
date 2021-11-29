/**
 * @author wanyu
 * @Classname Student
 * @Date 2021/11/2 10:51
 */
public class Student implements Comparable<Student>{

    private String name;
    private int score;

    public Student(String name,int score){
        this.name = name;
        this.score = score;
    }

    @Override
    public int compareTo(Student another) {
//        if (this.score < another.score)
//            return -1;
//        else if (this.score == another.score)
//            return 0;
//        else
//            return 1;
        //上面几句可以用以下替换
        //return this.score - another.score;//从大到小排序
        return another.score - this.score;//从小到大排序
    }

    @Override
    public String toString(){
        return String.format("Student(name:%s,score:%d)",name,score);
    }
}
