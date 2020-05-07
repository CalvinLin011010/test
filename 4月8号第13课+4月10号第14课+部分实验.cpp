
// 4月8号第13课+4月10号第14课+部分实验.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


//————————————25：00——————————————————————
/*5.4.3 构造函数和析构函数的构造规则

1、派生类可以不定义构造函数的情况
当具有下述三种情况之一时，派生类可以不定义构造函数。

  基类没有定义任何构造函数。   //系统会产生无参的构造函数
  基类具有缺省参数的构造函数。 //基类含有无参的构造函数，所有值都按照默认值初始化
  基类具有无参构造函数。       //显式定义无参的构造函数

本质上上面三种情况等价于基类有无参的构造函数

【例5-7】  没有构造函数的派生类。
#include <iostream>
using namespace std;
class A {
public:
    A(){ cout<<"Constructing A"<<endl; }
    //改构造函数满足  在基类A中显式定义无参的构造函数  

    ~A(){ cout<<"Destructing A"<<endl; }
};
class B:public A {    
//派生类B中没有数据成员需要初始化，可以不定义构造函数，
//因为我们去构造派生类B的时候先去构造基类A，
//而基类A有无参的构造函数，所以系统会调用无参的构造函数


public:
   ~B(){ cout<<"Destructing B"<<endl; }
};
int main(){
    B b;
}

//程序执行顺序：先执行A的构造函数，输出Constructing A
                然后B执行默认的构造函数，没有输出内容//这时派生类B构造完了
                最后开始析构，先构造的后析构，B先析构，输出Destructing B
                然后A，输出Destructing A


*/

//—————————————————32：00————————————————
/*
2、派生类必须定义构造函数的情况

  当基类或成员对象所属类只含有带参数的构造函数时，
    //系统不会生成默认的无参的构造函数隐式（自动）初始化，
    //需要被调用才能完成对基类的构造
  即使派生类本身没有数据成员要初始化，它也必须定义构造函数，
  并以构造函数初始化列表的方式向基类和成员对象的构造函数传递参数，
  以实现基类子对象和成员对象的初始化


【例5-8】  派生类构造函数的定义。
#include <iostream>
using namespace std;
class Point{
protected:
    int x,y;
public:
    Point(int a,int b=0) {x=a;  y=b;}
    
    //改构造函数等价于两种情况
    //1.带两个int型形参的构造函数
    //2.带一个int型形参的构造函数，而另一个形参b提供给y的默认的初始化值是0；
    
    //因此基类Point只有带参数的构造函数，没有无参的构造函数
};
class Line:public Point{
public:
    Line(int a, int b):Point(a,b){};

    //派生类没有数据成员要初始化，但是基类Point只有带参数的构造函数，
    //所以派生类的即使自身
    //没有数据成员要初始化=可以调用无参的构造函数=无需显式的初始化
    //我们也需要显式的加一个形参列表去定义派生类的构造函数
    
    //形参的个数就是基类调用构造函数所需要的参数的个数
    //这里是调用基类两个参数的构造函数
    //所以在派生类的形参列表中只有两个int型的形参
    //两个形参a和b就传给基类Point用来构造函数的初始化
    //point是采用初始化列表的形式完成对基类的初始化工作

};
Void main(){Line l1;}


*/


//——————————————37：00————————————————

/*
3、派生类的构造函数只负责直接基类的初始化

C++语言标准有一条规则：如果派生类的基类同时也是另外一个类的派生类，
则每个派生类只负责它的直接基类的构造函数调用。

这条规则表明当派生类的直接基类只有带参数的构造函数，
但没有默认构造函数时（包括缺省参数和无参构造函数），
它必须在构造函数的初始化列表中调用其直接基类的构造函数，
并向基类的构造函数传递参数，以实现派生类对象中的基类子对象的初始化。
//在5.6的虚拟继承是一个例外


#include<iostream>
using namespace std;
class A {
    int x;
public:
    A(int aa) { x = aa; cout << "constructing A" << endl; }
    ~A() { cout << "destructing A" << endl; }
};
class B :public A {
public:
    B(int x) :A(x) { cout << "constucting B" << endl; }
};
class C :public B {
public:
    C(int x) :B(x) { cout << "constructing C" << endl; }
};
void main() {
    C c(1);
}


*/

//——————————————46：30——————————
/*4、构造函数的调用时间和次序

当派生类具有多个基类和多个对象成员，用初始化列表进行初始化，
它们的构造函数将在创建派生类对象时被调用，调用次序如下：

基类构造函数→对象成员构造函数→派生类构造函数
（继承顺序）    (声明顺序)

析构和构造相反


例：求建立d的对应的类的构造顺序
#include<iostream>
          Class A{int i; 
          public：A(int a){a=I;}  };
          Class B:public A{int j;
          public:  B(int b){b=j;}  };
          Class C:public A{int k;};
          Class D: public B, protected A{
          public: C c1, c2;
          D(int l, int m): A(l), B(m), c2(),c1(){}}；
          void main(){D d;}


基类构造函数→对象成员构造函数→派生类构造函数
（继承顺序）    (声明顺序)

先执行基类构造函数
D有两个基类B和A，执行顺序不是D构造函数的：后面成员初始化列表的先A后B，
执行顺序是继承的顺序（class D：后面的顺序） 先public B后protected A
然后发现B是类A的派生类，所以最开始先是public B的先A后B，再执行protected A的A

之后执行对象成员的构造
对象成员c1,c2 的创建顺序也和在初始化列表中的顺序无关
而是执行顺序是在声明的顺序C c1，c2，所以是先c1再c2
所以是A C A C 

最终是对派生类本身的构造

//综上：顺序：A B A  A C A C  D



#include<iostream>
using namespace std;

//例：对于下面的基类定义
class Base {
public:
    Base(int val) : id(val) {}
protected:
    int id;
};
*/
//解释为什么下述每个构造函数是非法的。
/*
(1)class C1 : public Base {
           C1(int val) : id(val) {}//无法直接调用基类的私有成员
};

class C1 : public Base {
    C1(int val) : Base(val) {}
};*/
/*？？？
class C2 : public C1 {
    C2(int val) : Base(val), C1(val) {}//只需要调用C2的直接基类C1就可以了
};
class C2 : public C1 {
    C2(int val) : C1(val) {}
}:
*/


/*？？？
class C3 : public C1 {
    C3(int val) : Base(val) {}
    //不需要对C3的间接基类Base进行构造，只需要对直接基类C1进行构造即可
};？？？
class C4 : public Base {
    C4(int val) : Base(id + val) {}
};？？？
class C5 : public Base {
    C5() {}
};


*/


//——————————1：05：00————————————————
/*5.5 多重继承

C++允许一个类从一个或多个基类派生。
如果一个类只有一个基类，就称为单一继承。
如果一个类具有两个或两个以上的基类，就称为多重继承。多继承的形式如下：
class 派生类名:[继承方式] 基类名1,[继承方式] 基类名2,//若不写继承方式就是私有继承
 …
{
……
};
其中，继承方式可以是public、protected、private



5.5.3 多继承的构造函数与析构函数

派生类必须负责为每个基类的构造函数提供初始化参数，构造的方法和原则与单继承相同。
构造函数的调用次序仍然是先基类，再对象成员，然后才是派生类的构造函数。
基类构造函数的调用次序与它们在被继承时的声明次序相同，与它们在派生类构造函数的初始化列表中的次序没有关系。
多继承方式下的析构函数调用次序仍然与构造函数的调用次序相反。


class A {…};
class B:public A {…};
class C:public B {…};
class X {…};
class Y {…};
class Z:public X,public Y {…};
class MI :public C,public Z {…};
对于下面的定义，构造函数的执行次序是什么？
MI mi;

A->B->C->X->Y->Z->MI

*/



/*5.5.2 多继承下的二义性

两种情况：


情况1.在多继承时，基类之间出现同名成员时，将出现访问时的二义性（不确定性）
——采用支配（同名覆盖）原则来解决。
（在派生类和基类之间出现同名函数，派生类覆盖基类）

class A
{
    public:
        void  f（ ）;
};
class B
{
    public:
        void f（ ）;
        void g（ ）;
};
class C: public A, public B
{         public:
           void g（ ）;
           void h（ ）;
};
如果声明：C  c1;
则  c1.f（ ）;  具有二义性

而  c1.g（ ）;  无二义性（同名覆盖）
同名覆盖原则。（在派生类和基类之间出现同名函数，派生类覆盖基类）

1、多继承的基类同名会二义性

2、多继承的基类和派生类同名不会有二义性

解决方法一：用类名来限定c1.A::f（ ）    或    c1.B::f（ ）
解决方法二：同名覆盖在C 中声明一个同名成员函数f（ ），f（ ）再根据需要调用  A::f（ ）  或    B::f（ ）


【例5-12】  类A和类B是MI的基类，它们都有一个成员函数f，
在类MI中就有通过继承而来的两个同名成员函数f。
#include<iostream>
using namespace std;
class A {
public:
voidf(){ cout<<"From  A"<<endl;}
};
class B {
public:
void f() { cout<<"From  B"<<endl;}
};
class MI: public A, public B {
public:
void g(){ cout<<"From  MI"<<endl; }
};
void main(){
    MI mi;
    mi.f();					//错误
    mi.A::f();				//正确
}






情况2.当派生类从多个基类派生，而这些基类又从同一个基类派生，
则在访问此共同基类中的成员时，将产生二义性——采用虚拟继承来解决。

class B
{     public:
            int b;
}
class B1 : public B
{
        public:
            int b1;
}
class B2 : public B
{
        public:
            int b2;
};
class C : public B1,public B2
{
       public:
           int f（ ）;
       private:
           int d;
}
下面的访问是二义性的：
C  c;
c.b
c.B::b

下面是正确的：
c.B1::b
c.B2::b


2、多继承的基类和派生类同名不会有二义性


*/
//—————————————1：28：00————————

/*5.6 虚拟继承

5.6.1 引入的原因--重复基类
     派生类间接继承同一基类使得间接基类（Person）在派生类中有多份拷贝，
     引发二义性。
     （多份备份导致的二义性问题）

虽然使用指明成员函数调用所属的类的方法可以解决二义性命名冲突的问题。
但是它并未解决本质问题，在同一个对象中存在多份相同数据成员，
不仅浪费存储空间，而且还容易产生数据的不一致性。
为了解决这类问题，C++引用了虚拟继承。


//5.6.2 虚拟继承的实现


1、虚拟继承virtual inheritance的定义
语法
class derived_class : virtual […] base_class
虚基类virtual base class
被虚拟继承的基类
在其所有的派生类中，仅出现一次

利用C++提供的关键字virtual限定继承方式，
将公共基类指定为虚基类，就可以使该类的成员在派生类中只有一份备份。


【例5-14】  类A是类B、C的基类，类D从类B、C继承，
在类D中调用基类A的成员会产生二义性。
class A {
public:
    void vf() {
        cout<<"I come from class A"<<endl;	}
};
class B: public A{};
class C: public A{};
class D: public B, public C{};

int main()
{
    D d;
    d.vf ();	// error
}

将【例5-14】  改为虚拟继承不会产生二义性。
class A {
public:
    void vf() {
        cout<<"I come from class A"<<endl;	}
};
class B: virtual public A{};
class C: virtual public A{};
class D: public B, public C{};

int main()
{
    D d;
    d.vf();	// okay



2、虚拟继承的构造次序
虚基类的初始化与一般的多重继承的初始化在语法上是一样的，
但构造函数的调用顺序不同；

若基类由虚基类派生而来，则派生类必须提供对间接基类的构造
（即在构造函数初始列表中构造虚基类，无论此虚基类是直接还是间接基类）

调用顺序的规定：
先调用虚基类的构造函数，再调用非虚基类的构造函数
若同一层次中包含多个虚基类,这些虚基类的构造函数按它们的说明的次序调用
若虚基类由非虚基类派生而来,则仍然先调用基类构造函数,
再调用派生类构造函数


【例5-15】  虚基类的执行次序分析。
#include <iostream>
using namespace std;
class A {
    int a;
public:
    A(){ cout<<"Constructing A"<<endl; }
};
class B {
int b;
public:
    B(){ cout<<"Constructing B"<<endl;}
    B(int i){b=i;}
};
class B1:virtual public B ,virtual public A{
public:
    B1(int i){ cout<<"Constructing B1"<<endl; }
};
class B2:public A,virtual public B {
public:
    B2(int j){ cout<<"Constructing B2"<<endl; }
};
class D: public B1, public B2 {
public:
    D(int m,int n): B1(m),B2(n){ cout<<"Constructing D"<<endl; }
    A a;
};

int main(){
    D d(1,2);
}
  

  B  A  B1  A  B2  A  D
  
  Constructing B
Constructing A
Constructing B1
Constructing A
Constructing B2
Constructing A
Constructing D

  继承层次结构示意图，
  图中左上部分有阴影的B和A表示虚基类。派生类D从B1、B2派生，
  由于都不是虚拟派生，所以按继承次序应先构造B1，
  再构造B2.由于B1从B、A虚拟派生，将以此调用B和A的构造函数，
  完成后才能调用B1的构造函数，这个次序就成了B->A->B1。
  程序运行结果的前三行就是这样来的。
当D的B1基类构造完成后，按次序应该构造B2基类。
由于B2从A、B派生的，而B是虚基类，所以先调用B的构造函数。
但是作为虚基类的B在构造D的B1虚基类时就已经被构造了，所以就不再构造。
按构造次序，接下来就构造B2的基类A，由于A不是B2的虚基类，
所以就直接调用它的构造函数，与A以前是否被构造无关，输出结果的第4行就来源于此。
如果A是B2的虚基类，就不会调用A的构造函数，也就不会有第4行输出结果，
因为作为虚基类的A在构造B1时已经被构造了。
B2的基类构造完成后，就应该调用B2的构造函数了，这就是输出结果的第5行。
D的基类构造完成后，接下来就应该构造它的成员对象a，最后再构造D自己。
这就是输出结果的第6、7行。


3、虚基类由最终派生类初始化
在没有虚拟继承的情况下，每个派生类的构造函数只负责其直接基类的初始化。但在虚拟继承方式下，虚基类则由最终派生类的构造函数负责初始化。
在虚拟继承方式下，若最终派生类的构造函数没有明确调用虚基类的构造函数，编译器就会尝试调用虚基类不需要参数的构造函数（包括缺省、无参和缺省参数的构造函数），如果没找到就会产生编译错误。
#include <iostream>
#include <iomanip>
class A {
int a;
public:
A(int i) { a = i; }
};
class B :virtual public A {
public:
B(int j) :A(j) {}
};
class C :public B {
public:
C(int j) :B(j),A(j) {}
};
void main() {
C c(1);
}


【例5-16】  类A是类B、C的虚基类，类ABC从B、C派生，是继承结构中的最终派生类，
它负责虚基类A的初始化。

#include <iostream>
class A {
    int a;
public:
    A(int x) {
        a=x;
        cout<<"Virtual Bass A..."<<endl;
    }
};
class B:virtual public A {
public:
    B(int i):A(i){ cout<<"Virtual Bass B..."<<endl; }
};
class C:virtual public A{
    int x;
public:
    C(int i):A(i){
        cout<<"Constructing C..."<<endl;
        x=i;
    }
};
class ABC:public C, public B {
public:
    ABC(int i,int j,int k):C(i),B(j),A(i) //L1，这里必须对A进行初始化
        { cout<<"Constructing ABC..."<<endl; }
};
int main(){
    ABC obj(1,2,3);
}

ACBABC

Virtual Bass A…
Constructing C…
Virtual Bass B…
Constructing ABC…

虽然A是ABC的间接基类，但它是虚基类，而且没有默认构造函数，
所以ABC必须采用语句L1的方式对A进行初始化。
如果B和C从A采用普通而非虚拟继承的方式派生，
则在L1中对A的构造函数调用是不必要的，而且会产生编译错误。


*/


//————————————————————————————
//————————————————————————————————————————
//————————————————————————————————————————————————————————
//————————4月10号第1节课——————————————

//—————————————————41：00——————————

/*5.7基类与派生类对象的关系 

//在继承方式下，派生类获得了基类成员的一份备份，
这份备份构成了派生类对象内部的一个基类子对象
即派生类对象中存在一个基类子对象
即派生类对象比基类子对象所包含的内容更多

基类对象与派生类对象之间存在赋值相容性。

赋值相容性是指在公有派生的方式下，凡是需要基类对象的地方，都可以使用派生类对象

包括以下几种情况：

把派生类对象赋值给基类对象。
把派生类对象的地址赋值给基类指针。
用派生类对象初始化基类对象的引用。

反之则不行，
即不能把基类对象赋值给派生类对象；
    //派生类也是一种基类（别人的基类），且基类对象中并不包含派生类定义的内容
不能把基类对象的地址赋值给派生类对象的指针；
也不能把基类对象作为派生对象的引用。

//综上，只能从派生类向基类赋值


#include <iostream>
using namespace std;
class A {
int a;
public:
void setA(int x) { a = x; }
int getA() { return a; }
};
class B :public A {
int b;
public:
void setB(int x) { b = x; }
int getB() { return b; }
};

void f1(A a, int x) { a.setA(x); }
//f1的参数是基类对象（完成实参b1向形参a的赋值）（隐含的赋值a=b1）
//(满足赋值相容性第一条)

void f2(A *pA, int x) { pA->setA(x); }
//f2的参数是基类指针（获取pA的地址，传给指针pA）(满足赋值相容性第二条)
//（在函数调用时，为指针pA开辟了空间，里面存放b1子对象的地址）
//我们通过形参pA所能访问到的b1里面的内容，也只包含基类的部分

void f3(A &rA, int x) { rA.setA(x); }
//f3的参数是基类对象的引用（实际上传的参数是b1
//(满足赋值相容性第三条)用派生类对象初始化基类对象的引用。

int main() {
A a1, *pA;
B b1, *pB;
a1.setA(1);
b1.setA(2);

a1 = b1;//赋值相容性 第一条：把派生类对象赋值给基类对象。
        //（按值传递，将一个派生类的对象b1的子对象中的a的值复制给基类的对象a1，
        //  之后二者就无关了，二者是两个单独的内存空间）
cout << a1.getA() << endl;
cout << b1.getA() << endl;

a1.setA(10);
cout << a1.getA() << endl;
cout << b1.getA() << endl;

pA = &b1;//赋值相容性 第二条：把派生类对象的地址赋值给基类指针。
          //（可以通过pA这个基类的指针，去访问b1里面属于基类子对象的部分
          //  虽然我们将b1的地址赋值给基类的指针pA，
          //  但是我们无法通过pA去访问b1里的setB，getB，b属于派生类的这一部分

pA->setA(20);
cout << pA->getA() << endl;    cout << b1.getA() << endl;    

A &ra = b1;//赋值相容性 第三条：用派生类对象初始化基类对象的引用。
           //（把引用指向一个派生类对象b1，使得ra可以像一个普通变量一样
           //  去访问b1中的基类子对象的部分）

ra.setA(30);

////以上为显式使用赋值相容性

////下面是隐式使用赋值相容性

cout << pA->getA() << endl;
cout << b1.getA() << endl;    b1.setA(7);
cout << b1.getA() << endl;    f1(b1, 100);//f1的参数是基类对象
cout << b1.getA() << endl;    f2(&b1, 200);//f2的参数是基类指针
cout << b1.getA() << endl;    f3(b1, 300);//f3的参数是基类对象的引用。
cout << b1.getA() << endl;
}


例子中基类对象a1和派生类对象b1的基本结构如下图：
（1）赋值语句a1=b1；以按值传递的方式把派生对象b1内的子对象复制给a1对象，
     复制完成后，a1与b1就没有关系了。语句L3和L4的输出结果说明了这个问题。
（2）赋值语句pA=&b1；是把b1对象中基类子对象的地址赋值给pA指针，
     所以通过pA能够访问b1中的基类子对象。语句L5和L6说明了这个问题。
（3）赋值语句A &ra=b1；把ra作为b1中基类子对象的别名，
     所以通过ra能够访问b1中的基类子对象。语句L7和L8的输出结果说明了这个问题。

在函数中，如果形式参数是基类对象，也可以用派生类对象作为实参。
    概括而言，有一下三种传递对象参数的方式。
（1）形参是基类对象。如果形式参数是基类对象，在调用该函数时，
     可以用派生类对象作为实参调用该函数，如本程序中的函数f1()。
     这种参数传递方式是把派生类中的基类子对象的对应数据复制给函数形参，
     所以它不能修改实参（即派生类对象）的数据成员值。
     L9和L10的输出解雇说明了这个问题。
（2）形参是指向基类对象的指针。如果函数的形参是基类对象的指针，
     在函数调用时，可以把派生类对象的地址传递给它。f2()就是这种类型的函数，
     这种方式能够访问派生类中的基类子对象，L11的输出结果就是一个例证。
（3）形参是基类对象的引用。如果函数的参数是基类对象引用，
     可以把派生类对象作为调用参数，f3()就是这样的例子。
     这种参数参数传递方式能够访问派生类对象中的基类子对象，
     L12的输出结果就是一个证明。





*/































