#pragma once
namespace Comment
{
	/***********************************************************************/
	/*                    아무 함수 및 클래스를 만든 후                    */
	/*                  Doxygen Comment를 작성하여 보시오                  */
	/***********************************************************************/

	/*!
	 * \class HelloWorldPrinter
	 *
	 * \brief 
	 *
	 * \author jungin500
	 * \date July 2019
	 */
	template<typename T>
	class HelloWorldPrinter
	{
	private:
		string message;

	public:

		//************************************
		// Method:    HelloWorldPrinter
		// FullName:  Comment::HelloWorldPrinter<T>::HelloWorldPrinter
		// Access:    public 
		// Returns:   
		// Qualifier: : message(message)
		// Parameter: const string & message
		//************************************
		HelloWorldPrinter(const string& message) : message(message)
		{

		}

		//************************************
		// Method:    ~HelloWorldPrinter
		// FullName:  Comment::HelloWorldPrinter<T>::~HelloWorldPrinter
		// Access:    public 
		// Returns:   
		// Qualifier:
		//************************************
		~HelloWorldPrinter()
		{

		}

		//************************************
		// Method:    operator=
		// FullName:  Comment::HelloWorldPrinter<T>::operator=
		// Access:    public 
		// Returns:   Comment::HelloWorldPrinter&
		// Qualifier:
		// Parameter: const HelloWorldPrinter & rhs
		//************************************
		HelloWorldPrinter& operator=(const HelloWorldPrinter& rhs)
		{
			for(int i = 0; i < hello_world_message_size; i++)
				hello_world
		}
	};
}