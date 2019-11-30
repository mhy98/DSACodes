#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFEASIBLE -1
#define OVERFLOW -2

using namespace std; 

typedef int Status;
typedef char Bool;

class Polynomial 
{
	private:
		typedef struct Term
		{
			double coe;
			int pow;
		}Term;
			
		typedef struct Node
		{
			Term data;
			struct Node* next;
		}Node;
		
		Node* head;

		Bool IsUndefined()
		{
			return head?FALSE:TRUE;
		}
		
		Status Insert(int i,Term e)
		{
			Node* p=head;
			Node* q;
			for (int j=1;j<i;j++) p=p->next;
			q=p->next;
			p->next=(Node*)malloc(sizeof(Node));
			p->next->data=e;
			p->next->next=q;
			return OK;
		}
		
		Status Delete(int i)
		{
			Node* p=head;
			Node* q;
			for (int j=1;j<i;j++) p=p->next;
			q=p->next;
			p->next=p->next->next;
			free(q);
			return OK;
		}
		
		Status Copy(Polynomial B)
		{
			if (B.head==head) return OK;
			Init();
			int i=1;
			Node* p=B.head->next;
			for (;p;i++,p=p->next)
				Insert(i,p->data);
			return OK;
		}
		
		Status StandardizedInsert(Term t)
		{
			Node* p=head->next;
			int i=1;
			for (;p;i++,p=p->next)
			{
				if (t.pow>p->data.pow)
				{
					Insert(i,t);
					return OK;
				}
				else if (t.pow==p->data.pow)
				{
					p->data.coe+=t.coe;
					if (p->data.coe<1e-8 && p->data.coe>-1e-8)
						Delete(i);
					return OK;
				}
			}
			Insert(i,t);
			return OK;
		}
		
	public:	
		Polynomial()
		{
			head=NULL;
		}

		Polynomial(int i)
		{
			Init();
			if (i)
			{
				Term temp;
				temp.coe=i;
				temp.pow=0;
				head->next=(Node*)malloc(sizeof(Node));
				head->next->data=temp;
				head->next->next=NULL;
			}
		}

		Polynomial(const Polynomial& B)
		{
			Init();
			int i=1;
			Node* p=B.head->next;
			for (;p;i++,p=p->next)
				Insert(i,p->data);
		}

		~Polynomial()
		{
			Destroy();
		}

		Status Init()
		{
			Term temp;
			temp.coe=temp.pow=0;
			head=(Node*)malloc(sizeof(Node));
			head->data=temp;
			head->next=NULL;
		}

		Status Destroy()
		{
			Node *p=head,*q;
			while (p)
			{
				q=p->next;
				free(p);
				p=q;
			}
			head=NULL;
			return OK;
		}

		Status Clear()
		{
			Destroy();
			Init();
			return OK;
		}

		Status Read(FILE* fin)
		{
			Clear();
			Term temp;
			while (TRUE)
			{
				fscanf(fin,"%lf%d",&temp.coe,&temp.pow);
				if (!temp.coe && !temp.pow) break;
				StandardizedInsert(temp);
			}
			return OK;
		}

		void Print(FILE* fout)
		{
			if (!head) 
				fprintf(fout,"NULL\n");
			else
			{
				Node* p=head->next;
				if (p)
				{
					if (p->data.pow>1)
						fprintf(fout,"%.4lfx^%d",p->data.coe,p->data.pow);
					else if (p->data.pow==1)
						fprintf(fout,"%.4lfx",p->data.coe);
					else
						fprintf(fout,"%.4lf",p->data.coe);
					p=p->next;
					while (p)
					{
						if (p->data.coe>0)
							fprintf(fout,"+");
						if (p->data.pow>1)
							fprintf(fout,"%.4lfx^%d",p->data.coe,p->data.pow);
						else if (p->data.pow==1)
							fprintf(fout,"%.4lfx",p->data.coe);
						else
							fprintf(fout,"%.4lf",p->data.coe);
						p=p->next;
					}
				}
				else
					fprintf(fout,"%.4lf",0);
				fprintf(fout,"\n");
			}
		}

		Polynomial & operator=(const Polynomial& B)
		{
			Copy(B);
			return *this;
		}
	
		Polynomial operator+(const Polynomial& B)
		{
			Polynomial T=*this;
			Node* p=B.head->next;
			for (;p;p=p->next)
				T.StandardizedInsert(p->data); 
			return T;
		}
		
		Polynomial operator-(const Polynomial& B)
		{
			Polynomial T=*this;
			Term temp;
			Node* p=B.head->next;
			for (;p;p=p->next)
			{
				temp.coe=-p->data.coe;
				temp.pow=p->data.pow;
				T.StandardizedInsert(temp);
			}
			return T;
		}
		
		Polynomial operator*(const Polynomial& B)
		{
			Polynomial T;
			T.Init();
			Node *p=head->next,*q;
			Term temp;
			for (;p;p=p->next)
			{
				q=B.head->next;
				for (;q;q=q->next)
				{
					temp.coe=p->data.coe*q->data.coe;
					temp.pow=p->data.pow+q->data.pow;
					T.StandardizedInsert(temp);
				}
			}
			return T;
		}

		Polynomial operator/(const Polynomial& B)
		{
			if (!B.head->next)
			{
				printf("ERROR: division by zero.\n");
				return 0;
			}
			Polynomial T,Y(*this);
			T.Init();
			Term temp;
			while (Y.head->next && B.head->next && Y.head->next->data.pow>=B.head->next->data.pow)
			{
				temp.coe=Y.head->next->data.coe/B.head->next->data.coe;
				temp.pow=Y.head->next->data.pow-B.head->next->data.pow;
				T.StandardizedInsert(temp);
				Y=*this-T*B;
			}
			return T;
		}

		Polynomial operator/(double n)
		{
			if (!n)
			{
				printf("ERROR: division by zero.\n");
				return 0;
			}
			Polynomial T(*this);
			Node *p=T.head->next;
			for (;p;p=p->next)
				p->data.coe/=n;
			return T;
		}
		
		Polynomial operator%(const Polynomial& B)
		{
			if (!B.head->next)
			{
				printf("ERROR: division by zero.\n");
				return 0;
			}
			return *this-*this/B*B;
		}
		
		Polynomial FastPower(int n)
		{
			if (n<0)
			{
				printf("ERROR: exponent less than 0.\n");
				return 0;
			}
			Polynomial A(*this);
			Polynomial T(1);
			while (n)
			{
				if (n&1)
					T=T*A;
				n>>=1;
				A=A*A;
			}
			return T;
		}

		static Polynomial GreatestCommonDivisor(Polynomial A,Polynomial B)
		{
			if (!A.head->next || !B.head->next)
			{
				printf("ERROR: input including zero.\n");
				return 0;
			}
			Polynomial T;
			T=A%B;
			while (T.head->next)
			{
				A=B;
				B=T;
				T=A%B;
			}
			B=B/B.head->next->data.coe;
			return B;
		}
		
		static Polynomial LeastCommonMultiple(Polynomial A,Polynomial B)
		{
			if (!A.head->next || !B.head->next)
			{
				printf("ERROR: input including zero.\n");
				return 0;
			}
			Polynomial T(A*B/GreatestCommonDivisor(A,B));
			T=T/T.head->next->data.coe;
			return T;
		}

		Polynomial Differential()
		{
			Polynomial T;
			T.Init();
			Node *p=head->next;
			Term temp;
			for (;p;p=p->next)
			{
				if (!p->data.pow) continue;
				temp.coe=p->data.coe*p->data.pow;
				temp.pow=p->data.pow-1;
				T.StandardizedInsert(temp);
			}
			return T;
		}
		
		Polynomial Integral()
		{
			Polynomial T;
			T.Init();
			Node *p=head->next;
			Term temp;
			for (;p;p=p->next)
			{
				temp.coe=p->data.coe/(p->data.pow+1);
				temp.pow=p->data.pow+1;
				T.StandardizedInsert(temp);
			}
			return T;
		}
		
		double Integral(double x1,double x2)
		{
			Polynomial T(this->Integral());
			return T.Value(x2)-T.Value(x1);
		}

		double Value(double x)
		{
			double s=0;
			for (Node*p=head;p;p=p->next)
				s+=p->data.coe*pow(x,p->data.pow);
			return s;
		}
};

class PolynomialCalculator
{
	private:
		Polynomial polynomial[10];

	public:
		PolynomialCalculator()
		{
			printf("Polynomial Calculator Lite\nWritten by Jeffrey Xiang\n\n");
		}

		~PolynomialCalculator()
		{
			printf("\nDoing cleanup...\nThanks for using!\n");
		}

		Status Read(FILE* fin)
		{
			int pos;
			fscanf(fin,"%d",&pos);
			polynomial[pos].Read(fin);
			return OK;
		}

		Status Print(FILE* fin,FILE* fout)
		{
			int pos;
			fscanf(fin,"%d",&pos);
			polynomial[pos].Print(fout);
			return OK;
		}

		Status Copy(FILE* fin)
		{
			int pos1,pos2;
			fscanf(fin,"%d%d",&pos1,&pos2);
			polynomial[pos2]=polynomial[pos1];
			return OK;
		}

		Status Add(FILE* fin)
		{
			int pos1,pos2,pos3;
			fscanf(fin,"%d%d%d",&pos1,&pos2,&pos3);
			polynomial[pos3]=polynomial[pos1]+polynomial[pos2];
			return OK;
		}

		Status Subtract(FILE* fin)
		{
			int pos1,pos2,pos3;
			fscanf(fin,"%d%d%d",&pos1,&pos2,&pos3);
			polynomial[pos3]=polynomial[pos1]-polynomial[pos2];
			return OK;
		}

		Status Multiply(FILE* fin)
		{
			int pos1,pos2,pos3;
			fscanf(fin,"%d%d%d",&pos1,&pos2,&pos3);
			polynomial[pos3]=polynomial[pos1]*polynomial[pos2];
			return OK;
		}

		Status Value(FILE* fin,FILE* fout)
		{
			int pos;
			double x;
			fscanf(fin,"%d%lf",&pos,&x);
			fprintf(fout,"%.4lf\n",polynomial[pos].Value(x));
			return OK;
		}

		Status Destroy(FILE* fin)
		{
			int pos;
			fscanf(fin,"%d",&pos);
			polynomial[pos].Destroy();
			return OK;
		}

		Status Clear(FILE* fin)
		{
			int pos;
			fscanf(fin,"%d",&pos);
			polynomial[pos].Clear();
			return OK;
		}

		Status Differential(FILE* fin)
		{
			int pos1,pos2;
			fscanf(fin,"%d%d",&pos1,&pos2);
			polynomial[pos2]=polynomial[pos1].Differential();
			return OK;
		}

		Status IndefiniteIntegral(FILE* fin)
		{
			int pos1,pos2;
			fscanf(fin,"%d%d",&pos1,&pos2);
			polynomial[pos2]=polynomial[pos1].Integral();
			return OK;
		}

		Status DefiniteIntegral(FILE* fin,FILE* fout)
		{
			int pos;
			double x1,x2;
			fscanf(fin,"%d%lf%lf",&pos,&x1,&x2);
			fprintf(fout,"%.4lf\n",polynomial[pos].Integral(x1,x2));
			return OK;
		}

		Status GreatestCommonDivisor(FILE* fin)
		{
			int pos1,pos2,pos3;
			fscanf(fin,"%d%d%d",&pos1,&pos2,&pos3);
			polynomial[pos3]=Polynomial::GreatestCommonDivisor(polynomial[pos1],polynomial[pos2]);
			return OK;
		}

		Status LeastCommonMultiple(FILE* fin)
		{
			int pos1,pos2,pos3;
			fscanf(fin,"%d%d%d",&pos1,&pos2,&pos3);
			polynomial[pos3]=Polynomial::LeastCommonMultiple(polynomial[pos1],polynomial[pos2]);
			return OK;
		}

		Status Divide(FILE* fin)
		{
			int pos1,pos2,pos3;
			fscanf(fin,"%d%d%d",&pos1,&pos2,&pos3);
			polynomial[pos3]=polynomial[pos1]/polynomial[pos2];
			return OK;
		}

		Status Modulo(FILE* fin)
		{
			int pos1,pos2,pos3;
			fscanf(fin,"%d%d%d",&pos1,&pos2,&pos3);
			polynomial[pos3]=polynomial[pos1]%polynomial[pos2];
			return OK;
		}

		Status Power(FILE* fin)
		{
			int pos1,pos2,n;
			fscanf(fin,"%d%d%d",&pos1,&pos2,&n);
			polynomial[pos2]=polynomial[pos1].FastPower(n);
			return OK;
		}

		Status Run(const char* Fin,const char* Fout)
		{
			printf("Running with input file \"%s\", output file \"%s\"\n",Fin,Fout);
			FILE *fin,*fout;
			if (!(fin=fopen(Fin,"r")))
			{
				printf("ERROR: failed to open the input file.\n");
				return ERROR;
			}
			if (!(fout=fopen(Fout,"w")))
			{
				printf("ERROR: failed to open the output file.\n");
				return ERROR;
			}
			int cmd;
			while (TRUE)
			{
				fscanf(fin,"%d",&cmd);
				if (!cmd) break;
				switch (cmd)
				{
					case 1: Read(fin);break;
					case 2: Print(fin,fout);break;
					case 3: Copy(fin);break;
					case 4: Add(fin);break;
					case 5: Subtract(fin);break;
					case 6: Multiply(fin);break;
					case 7: Value(fin,fout);break;
					case 8: Destroy(fin);break;
					case 9: Clear(fin);break;
					case 10: Differential(fin);break;
					case 11: IndefiniteIntegral(fin);break;
					case 12: DefiniteIntegral(fin,fout);break;
					case 13: GreatestCommonDivisor(fin);break;
					case 14: LeastCommonMultiple(fin);break;
					case 15: Divide(fin);break;
					case 16: Modulo(fin);break;
					case 17: Power(fin);break;
				}
			}
			fclose(fin);
			fclose(fout);
			printf("Processing finished.\n");
			return OK;
		}
};

main()
{
	PolynomialCalculator App;
	App.Run("polyn.in","polyn.out");
}
