void Eval(Expression e) {

	//e는 마지막 토큰이 ‘#’이라고 가정

	Stack<Token> stack;

	for (Token x = NextToken(e); x != ’#’; x = NextToken(e))

		if (x is an operand)

			stack.Push(x)

		else {

			remove the correct number of operands for operator x from stack;

			perform the operation xand store the result(if any) onto the stack;

		}

}



void Postfix(Expression e)

{

	Stack<Token> stack;

	stack.Push(‘#’);

	for (Token x = NextToken(e); x = ’#’; x = NextToken(e))

		if (x is an operand) cout << x;

		else if (x == ‘)’)

{//unstack until ‘(’

for (; stack.Top() != ‘(’; stack.Pop())

	cout << stack.Top();

}

		else {//x is an operator

			for (; isp(stack.Top()) <= icp(x); stack.Pop())

				cout << stack.Top();

				stack.Push(x);

		}

	// empty the stack

	for (; !stack.IsEmpty(); cout << stack.Top(), stack.Pop());

	cout << endl;

}