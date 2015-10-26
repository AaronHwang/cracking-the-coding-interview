//http://www.hawstein.com/posts/1.1.html
#include <iostream>
#include <cstring>
using namespace std;

bool isUnique1(string s)
{
    bool a[256];//假设字符集是ASCII字符，开一个大小为256的bool数组来表征每个字符的出现
    memset(a, 0, sizeof(a));//作用是在一段内存块中填充某个给定的值，它是对较大的结构体或数组进行清零操作的一种最快方法。这里是将a全部清零并返回a
    //要注意的是，memset是对字节进行操作,所以用memset对非字符型数组赋初值是不可取的！
    //question：可不可以写为memset(a,0,256*sizeof(bool))，考虑到如果是char型最后一位是'\0'
    //数组初始化为false，遍历一遍字符串中的字符，当bool数组对应位置的值为真， 表明该字符在之前已经出现过，即可得出该字符串中有重复字符。否则将该位置的bool数组值置为true。
    int len = s.length();
    for(int i=0; i<len; ++i)
    {
        int v = (int)s[i];
        if(a[v]) return false;
        a[v] = true;
    }
    return true;
}


//该算法的时间复杂度为O(n)。我们还可以通过位运算来减少空间的使用量。 用每一位表征相应位置字符的出现。对于ASCII字符，我们需要256位，即一个长度为8的int数组a即可。这里的关键是要把字符对应的数字，映射到正确的位上去。比如字符'b'对应的代码是98，那么我们应该将数组中的哪一位置为1呢？用98除以32，得到对应数组a的下标： 3。98对32取模得到相应的位
//两个算法的本质其实是一样的，只不过一个用bool单元来表征字符出现，一个用位来表征。
bool isUnique2(string s)
{
    int a[8];
    memset(a, 0, sizeof(a));
    int len = s.length();
    for(int i=0; i<len; ++i)
    {
        int v = (int)s[i];
        int idx = v/32, shift=v%32;
        if(a[idx] & (1<<shift)) return false;
        a[idx] |= (1<<shift);
    }
    return true;
}

//如果字符集只是a－z(或是A－Z)，那就更好办了，用位运算只需要一个整型数即可。
bool isUnique3(string s)
{
    int check = 0;
    int len = s.length();
    for(int i=0; i<len; ++i)
    {
        int v = (int)(s[i]-'a');
        if(check & (1<<v)) return false;
        check |= (1<<v);
    }
    return true;
}
int main()
{
    string s1 = "i am hawstein.";
    string s2 = "abcdefghijklmnopqrstuvwxyz1234567890";
    cout<<isUnique1(s1)<<" "<<isUnique1(s2)<<endl;
    cout<<isUnique2(s1)<<" "<<isUnique2(s2)<<endl;
    return 0;
}
