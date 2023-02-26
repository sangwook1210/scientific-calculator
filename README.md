# scientific-calculator

이 공학용 계산기는 사칙연산, 승수계산, 음수, 삼각함수, 지수함수, 로그함수의 계산을 수행할 수 있다. 음수를 입력할 때는 (-1)과 같이 항상 앞뒤에 소괄호를 써서 입력해야 한다. 또한 삼각함수, 지수함수, 로그함수를 계산할 때는 각각의 첫 글자인 s,c,t,e,l과 숫자를 입력해주어야 한다. 예를 들어 sin(5)를 계산하고 싶다면 s5 혹은 s(5)와 같이 입력해야 한다. 삼각함수의 세타값을 입력할 때는 라디안 단위로 입력해야 한다.

공학용 계산기를 만든 과정은 크게 네 가지 단계로 나눌 수 있다.

1. 중위 표기식을 입력받아 이를 후위표기식으로 바꾸는 단계

최대 255문자를 입력받을 수 있으므로 #define MAX\_STACK\_SIZE 255를 적는다.

main.c의 int prec(char op)함수는 연산자들의 우선순위를 정해주는 함수이다. '(', ')'는 0, '+', '-'는 1, '\*', '/'는 2, '^'는 3, sin, cos, tan, exp, log는 4를 반환한다.

main.c의 const char\* infix\_to\_postfix(char infix[])함수는 매개변수로 입력받은 중위표기식을 후위 표기 수식으로 바꿔주는 함수이다. infix문자열을 한 문자씩 끊어서 반복문을 이용하여 모든 문자에 대하여 다음을 수행한다.

끊은 문자가 ')'를 제외한 연산기호라면 스택에 넣고, 연산기호가 아닌 숫자라면 postfix문자열에 저장한다.
만약 끊은 문자가 s,c,t,e,l

# 1
중 하나라면 스택에서 pop하여 postfix문자열에 저장한다. 또한 스택이 비어있지 않고, 연산기호의 우선순위 스택에서 가장 위의 연산기호보다 작거나 같다면 postfix문자열에 스택에서 pop한 것을 저장한다.
만약 끊은 문자가 '('이고, 다음에 끊을 문자가 -라면, 음수가 입력된 것이다. 따라서 (-1)이라면, "0 1 – "가 postfix문자열에 저장되도록 한다.
만약 끊은 문자가 ')'라면 '('가 나오기 전까지 스택에 저장되어 있는 모든 연산기호들을 pop하여 postfix문자열에 저장한다. 만약 ')'가 나왔을 때, 스택의 가장 위에 저장되어 있는 원소가 sctel 중 하나라면 postfix에 pop한 것을 저장한다.

반복이 끝났다면 스택에 남아있는 모든 연산기호들을 postfix에 저장하고, postfix의 남은 비어있는 부분들을 '\0'으로 채워준 후 postfix를 반환한다.

1. 바뀐 후위 표기식을 절차에 따라 이진 트리에 집어넣는 단계

tree\_stack.h에서 tree\_Stack이라는 tree를 원소로 가지는 스택을 생성한다.

Tree.h의 TreeNode\* CreateNode(element\_t\* a, TreeNode\* b, TreeNode\* c)라는 함수는 NewNode라는 트리를 동적할당으로 생성하여 a를 NewNode-\>data에, b를 NewNode-\>left에, c를 NewNode-\>right에 저장한다.

main.c의 TreeNode\* make\_exp\_Tree(char\* postfix)라는 함수는 tree\_Stack ts로 tree\_Stack변수를 만들고, char\* tmp변수에 strtok(postfix, " ")를 이용하여 매개변수로 입력받은 postfix문자열을 띄어쓰기를 단위로 끊는다.
끊어진 문자열이 +-\*/^와 같은 연산기호라면, ts에서 pop한 것을 TreeNode\* right에 저장하고, ts에서 그다음으로 pop한 것을 TreeNode\*left에 저장한다. 그리고 CreatNode(tmp, left, right)를 ts에 push한다.
만약 끊어진 문자열이 삼각함수 혹은 지수, 로그함수라면 TreeNode\* right에 ts에서 pop한 것을 저장한다. 그리고 CreatNode(tmp, NULL, right)를 ts에 push한다.
만약 끊어진 문자열이 그 외의 숫자라면 CreatNode(tmp, NULL, NULL)을 ts에 push한다.
이를 tmp가 NULL이 될 때까지 반복합니다. 반복이 끝나면 ts에서 트리를 pop해 반환한다.

1. 만들어진 트리를 이용하여 결괏값을 계산하는 단계

tree.h의 double calculate\_exp\_Tree(TreeNode\* root)함수는 연산 트리를 계산하는 함수이다.
만약 root가 단말 노드라면, root-\>data를 atof를 사용하여 double값으로 바꿔 반환한다.
만약 root가 root-\>right만 NULL이 아니라면, double right에 calculate\_exp\_Tree(root-\>right)를 대입한다. sin(right), cos(right), tan(right), exp(right), log(right) 중 root-\>data에 해당하는 것을 계산하여 반환한다.
나머지라면 double left에 calculate\_exp\_Tree(root-\>left), double right에
 calculate\_exp\_Tree(root-\>right)를 대입하고, +,-,\*,/,^ 중 root-\>data에 해당하는 것을 left와 right를 사용하여 계산하여 반환한다.

1. 이 트리를 전위순회, 중위순회, 후위순회, 레벨순회한 것을 출력하는 단계

전위순회는 Node-\>data, Node-\>left, Node-\>right 순으로 출력하고, 중위순회는 Node-\>left, Node-\>data, Node-\>right 순으로 출력하고, 후위순회는 Node-\>left, Node-\>right, Node-\>data 순으로 출력한다.

레벨순회는 트리를 원소로 저장할 수 있는 원형 큐를 이용하여 출력할 수 있다. 우선 트리의 root값을 원형큐에 집어넣는다. 루트 값을 dequeue\_tq하여 출력한 후, Node의 left와 right를 enqueue\_tq한다. 이를 원형큐가 빌 때까지 반복하면 레벨순회가 완료된다.

결과화면

