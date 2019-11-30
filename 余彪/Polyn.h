#ifndef _POLYN_H
#define _POLYN_H

#define OK 1
#define ERROR 0
#define OVERFLOW -1

typedef int Status;
typedef struct polyn
{
	int index;
	double coeff;
	struct polyn *next;
} Polyn,*PolynList;

/**
 *清除多项式内容，仅保留头结点
 *@param L:要操作的多项式
 *@return 状态码
 */
Status clear(PolynList &L);

/**
 *创建多项式
 *@param L:要操作的多项式
 *@param input:输入流
 *@return 状态码
 */
Status create(PolynList &L,FILE *input);

/**
 *按照指定格式显示多项式
 *@param L:要操作的多项式
 *@param output:输出流
 *@return 状态码
 */
Status print(PolynList L,FILE *output);

/**
 *复制多项式
 *@param from:被复制的多项式
 *@param to:复制到的多项式
 *@return 状态码
 */
Status copy(PolynList from,PolynList &to);

/**
 *多项式求和
 *@param polyn1:求和的第一个多项式
 *@param polyn2:求和的第二个多项式
 *@param result:求和的结果
 *@return 状态码
 */
Status add(PolynList polyn1,PolynList polyn2,PolynList &result);

/**
 *多项式求差
 *@param polyn1:多项式1，被减数
 *@param polyn2:多项式2，减数
 *@param result:求差的结果
 *@return 状态码
 */
Status substract(PolynList polyn1,PolynList polyn2,PolynList &result);

/**
 *多项式求积
 *@param polyn1:求积的第一个多项式
 *@param polyn2:求积的第二个多项式
 *@param result:求积的结果
 *@return 状态码
 */
Status multiply(PolynList polyn1,PolynList polyn2,PolynList &result);

/**
 *多项式求值
 *@param L:求值的多项式
 *@param x:求值带入的数字
 *@param output:输出流
 *@return 状态码
 */
Status result(PolynList L,double x,FILE *output);

/**
 *销毁多项式
 *@param L:销毁的多项式
 *@return 状态码
 */
Status destroy(PolynList &L);

/**
 *多项式求微分
 *@param from:原多项式
 *@param to:求微分的结果
 *@return 状态码
 */
Status dx(PolynList from,PolynList &to);

/**
 *多项式求不定积分
 *@param from:原多项式
 *@param to:求不定积分的结果
 *@return 状态码
 */
Status indefiniteIntegral(PolynList from,PolynList &to);

/**
 *多项式求定积分
 *@param L:原多项式
 *@param lower:定积分下界
 *@param upper:定积分上界
 *@param output:输出流
 *@return 状态码
 */
Status definiteIntegral(PolynList L,double lower,double upper,FILE *output);

/**
 *最大公约式
 *@param polyn1:多项式1
 *@param polyn2:多项式2
 *@param result:保存结果
 *return 状态码
 */
Status gcd(PolynList polyn1,PolynList polyn2,PolynList &result);

/**
 *最小公倍式
 *@param polyn1:多项式1
 *@param polyn2:多项式2
 *@param result:保存结果
 *return 状态码
 */
Status lcm(PolynList polyn1,PolynList polyn2,PolynList &result);

/**
 *除法
 *@param polyn1:多项式1，被除数
 *@param polyn2:多项式2，除数
 *@param result:保存结果
 *@return 状态码
 */
Status divide(PolynList polyn1,PolynList polyn2,PolynList &result);

/**
 *取余
 *@param polyn1:多项式1，被除数
 *@param polyn2:多项式2，除数
 *@param result:保存结果
 *@return 状态码
 */
Status mod(PolynList polyn1,PolynList polyn2,PolynList &result);

/**
 *快速幂算法算多项式乘方
 *@param base:底数
 *@param result:保存结果
 *@param pow:指数
 *@return 状态码
 */
Status fastPow(PolynList base,PolynList &result,int pow);

/**
 *本来应该主程序文件与Polyn.cpp一起编译的
 *嗯，不会
 *干脆就include完事
 */
#include "Polyn.cpp"
#endif
