#pragma once

#include <initializer_list>
#include <vector>
#include <cassert>
#include <iostream>

using std::cout;
using std::endl;

namespace CONSTRUCTOR
{
	/***********************************************************************/
	/*			  				��� �ʱ�ȭ ����Ʈ ���� 			       */
	/***********************************************************************/
	namespace MEMBER_INITIALIZATION_LIST
	{
		class Matrix
		{
		private:
			int nrows;
			int ncols;
		public:
			Matrix(int nrows, int ncols) : nrows(nrows), ncols(ncols) {}
		};

		class Solver
		{
		public:
			// Error
			/*Solver(int nrows, int ncols)
			{
				matrix = Matrix(nrows, ncols);
			}*/
			Solver(int nrows, int ncols) : matrix(nrows, ncols) {}

		private:
			Matrix matrix;
		};
	}

	namespace COPY_CONSTRUCTOR
	{
		/***********************************************************************/
		/*			  				  ���� ������ ���� 						   */
		/***********************************************************************/
		namespace ex1
		{
			class Matrix
			{
			public:
				int nrows;
				int ncols;
			public:
				Matrix(int nrows, int ncols) : nrows(nrows), ncols(ncols) {}
				// �������� �ʾƵ� �Ϲ������� ���� �����ڸ� ����
				// ���� ���簡 �Ͼ
				//Matrix(const Matrix & rhs) : nrows(rhs.nrows), ncols(rhs.ncols) {}
			};

			void Run()
			{
				Matrix m(1, 1);
				cout << "m.ncols : " << m.ncols << endl;
				cout << "m.nrows : " << m.nrows << endl;

				Matrix m2(m);
				cout << "m2.ncols : " << m2.ncols << endl;
				cout << "m2.nrows : " << m2.nrows << endl;
			}
		}

		/***********************************************************************/
		/*                     �Ʒ� �ڵ�� ������ �߻���Ų��                   */
		/*                   ���� ���ΰ� �ذ����� �����Ͻÿ�                 */
		/***********************************************************************/
		namespace DIY
		{
			class foo
			{
			public:
				double* pd;
				//std::unique_ptr<double> pd;
			public:
				foo(double val) : pd(new double) { *pd = val; }
				foo(const foo& rhs) : pd(new double) { *pd = *rhs.pd; }
				~foo() { delete pd; }
			};

			void Run()
			{
				foo f(10.0);
				cout << "f.pd : " << f.pd << " f.*pd : " << *f.pd << endl;
				foo f2(f);

				cout << "f2.pd : " << f2.pd << " f2.*pd : " << *f2.pd << endl;
			}
		}
	}

	namespace EXPLICIT
	{
		/***********************************************************************/
		/*			  				   explicit ���� 1						   */
		/***********************************************************************/
		namespace ex1
		{
			class Foo
			{
			public:
				int m_foo;
				Foo(int foo) : m_foo(foo) {}
			};

			void Print_Foo(Foo f) // �Ͻ��� ��ȯ���� ���Ͽ� �ڵ����� �� ��ȯ�� ��
			{
				cout << f.m_foo << endl;
			}

			void Run()
			{
				int num = 43;
				Print_Foo(num);
			}
		}

		/***********************************************************************/
		/*			  				   explicit ���� 2						   */
		/***********************************************************************/
		namespace ex2
		{
			using std::cout;
			using std::endl;

			class Foo
			{
			public:
				int m_foo;
				explicit Foo(int foo) : m_foo(foo) {} // �Ͻ��� ��ȭ�� ����
			};

			void Print_Foo(Foo f)
			{
				cout << f.m_foo << endl;
			}

			void Run()
			{
				int num = 43;
				// Error
				//Print_Foo(num);
			}
		}
	}

	namespace Delegating
	{
		/***********************************************************************/
		/*			  				   ���� ������ ���� 					   */
		/***********************************************************************/
		class Matrix_Modern
		{
		public:
			int nrows;
			int ncols;
		public:
			Matrix_Modern(int nrows, int ncols) : nrows{ nrows }, ncols{ ncols } {}
			Matrix_Modern(int nrows) : Matrix_Modern{ nrows, 10 } {}
			Matrix_Modern() : Matrix_Modern{ 10 } {}

		};

		void Run()
		{
			Matrix_Modern m;
			cout << "m.nrows : " << m.nrows << " m.ncols : " << m.ncols << endl;
		}
	}

	namespace MEMBER_DEFAULT
	{
		/***********************************************************************/
		/*			  				   ����� �⺻ �� ���� 					   */
		/***********************************************************************/
		class Matrix_Modern
		{
		public:
			int nrows = 10;
			int ncols = 10;
		public:
			Matrix_Modern(int nrows, int ncols) : nrows{ nrows }, ncols{ ncols } {}
			Matrix_Modern(int nrows) : nrows{ nrows } {}
			Matrix_Modern() {}

		};

		void Run()
		{
			Matrix_Modern m;
			cout << "m.nrows : " << m.nrows << " m.ncols : " << m.ncols << endl;
		}
	}

	namespace INITIALIZER_LIST
	{
		/***********************************************************************/
		/*			  				   ������ �ʱ�ȭ ���� 1					   */
		/***********************************************************************/
		namespace ex1
		{
			void Run()
			{
				int a[] = { 1, 2, 3 };
				int b[]{ 1, 2, 3 };

				cout << "a : ";
				for (auto v : a)
					cout << v << ", ";
				cout << endl;

				cout << "b : ";
				for (auto v : b)
					cout << v << ", ";
				cout << endl;
			}
		}

		/***********************************************************************/
		/*			  				   ������ �ʱ�ȭ ���� 2					   */
		/***********************************************************************/
		namespace ex2
		{
			void Run()
			{
				std::vector<int> vec{ 1, 2, 3 };

				cout << "vec : ";
				for (auto v : vec)
					cout << v << ", ";
				cout << endl;
			}
		}

		/***********************************************************************/
		/*			  				   �ʱ�ȭ ����Ʈ ���� 1					   */
		/***********************************************************************/
		namespace ex3
		{
			class list
			{
			public:
				int size;
				std::unique_ptr<double[]>data;

			public:
				list(int size) : size(size), data(new double[size]) {}

				list(std::initializer_list<double> values) : size(values.size()), data(new double[size])
				{
					std::copy(std::begin(values), std::end(values), &data[0]);
				}

				list& operator=(std::initializer_list<double> values)
				{
					assert(size == values.size());
					std::copy(std::begin(values), std::end(values), &data[0]);
					return *this;
				}

				void Print()
				{
					cout << "List : ";
					for (int i = 0; i < size; ++i)
						cout << data[i] << ", ";
					cout << endl;
				}
			};

			void Run()
			{
				list l{ 1, 2, 3 };
				l.Print();

				l = { 3, 4, 5 };
				l.Print();
			}
		}

		/***********************************************************************/
		/*           �Ʒ� �ڵ�� ũ�Ⱑ �ٸ� ��� ������ �߻��Ѵ�.             */
		/*           �Ʒ� �ڵ尡 ����ǵ��� ���α׷��� �����Ͻÿ�              */
		/*  Hint : unique_ptr�� �Լ� release()�� �� ��� ��� �޸𸮰� ������  */
		/***********************************************************************/

		namespace DIY
		{
			class list
			{
			public:
				int size;
				std::unique_ptr<double[]>data;

			public:
				list(int size) : size(size), data(new double[size]) {}

				list(std::initializer_list<double> values) : size(values.size()), data(new double[size])
				{
					std::copy(std::begin(values), std::end(values), &data[0]);
				}

				list& operator=(std::initializer_list<double> values)
				{
					if (size != values.size())
					{
						size = values.size();
						data.release();
						data = std::unique_ptr<double[]>(new double[size]);
					}
					std::copy(std::begin(values), std::end(values), &data[0]);
					return *this;
				}

				void Print()
				{
					cout << "List : ";
					for (int i = 0; i < size; ++i)
						cout << data[i] << ", ";
					cout << endl;
				}
			};

			void Run()
			{
				list l{ 1, 2, 3 };
				l.Print();

				l = { 3, 4, 5, 6 };
				l.Print();
			}
		}
	}

	namespace MOVE
	{
		/***********************************************************************/
		/*				  				  Move ���� 1						   */
		/***********************************************************************/
		namespace ex1
		{
			void Run()
			{
				std::vector<int> vec{ 1, 2, 3, 4, 5 };
				cout << "vec.size : " << vec.size() << endl << endl;;
				cout << "vec" << endl;
				for (auto val : vec)
					cout << val << ", ";
				cout << endl << endl;

				std::vector<int> vec2 = std::move(vec);
				cout << "vec.size : " << vec.size() << endl;
				cout << "vec2.size : " << vec2.size() << endl;

				cout << endl;

				cout << "vec" << endl;
				for (auto val : vec)
					cout << val << ", ";
				cout << endl;

				cout << "vec2" << endl;
				for (auto val : vec2)
					cout << val << ", ";
				cout << endl;
			}
		}

		/***********************************************************************/
		/*				  				  Move ���� 2						   */
		/***********************************************************************/
		namespace ex2
		{
			class list
			{
			public:
				int size;
				std::unique_ptr<double[]>data;

			public:
				list(int size) : size(size), data(new double[size]) {}

				list& operator=(list&& rhs)
				{
					assert(size == 0 || size == rhs.size);
					std::swap(data, rhs.data);
					rhs.data.release();
					rhs.size = 0;
					return *this;
				}

				list(list&& rhs) : size(rhs.size), data(new double[size])
				{
					std::swap(data, rhs.data);
					rhs.data.release();
					rhs.size = 0;
				}

				list(std::initializer_list<double> values) : size(values.size()), data(new double[size])
				{
					std::copy(std::begin(values), std::end(values), &data[0]);
				}

				void Print()
				{
					for (int i = 0; i < size; ++i)
						cout << data[i] << ", ";
					cout << endl;
				}
			};

			void Run()
			{
				list l{ 1, 2, 3 };
				list l2{ 3, 4, 5 };
				cout << "List1 : ";  l.Print();
				cout << "List2 : ";  l2.Print();
				cout << "List1 data Addr : " << l.data << endl;
				cout << "List2 data Addr : " << l2.data << endl;

				cout << endl;

				l2 = std::move(l);
				cout << "List1 : "; l.Print();
				cout << "List2 : "; l2.Print();
				cout << "List1 data Addr : " << l.data << endl;
				cout << "List2 data Addr : " << l2.data << endl;

				list l3{ std::move(l2) };
				cout << "List3 : ";  l3.Print();
				cout << "List2 data Addr : " << l2.data << endl;
				cout << "List3 data Addr : " << l3.data << endl;
			}
		}
	}
}