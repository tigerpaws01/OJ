#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXLEN 512
#define TBLSIZE 65535
//#define DEBUG



typedef enum {UNKNOWN, END, INT, ID, ADDSUB, ANDORXOR, MULDIV, ASSIGN,
LPAREN, RPAREN, EOFTOKEN} TokenSet;
typedef enum {MISPAREN, NOTNUMID, NOTFOUND, RUNOUT, NAN} ErrorType;


typedef struct {
	char name[MAXLEN];
	int val;
	bool recognized;
} Symbol;

typedef struct evaluation{
	bool isReg;
	int data;
} Evaluation;

bool regInUse[8];

typedef struct _Node {
	char lexeme[MAXLEN];
	TokenSet token;
	int val;
	struct _Node *left, *right;
} BTNode;

Symbol table[TBLSIZE];
int sbcount = 0;

extern int match (TokenSet token);
extern void advance(void);
extern char* getLexeme(void);
static TokenSet getToken(void);
static TokenSet lookahead = UNKNOWN;
static char lexeme[MAXLEN];
void statement(void);
BTNode* expr(void);
BTNode* term(void);
BTNode* factor(void);
int getval(void);
int setval(char*, int);
bool isAssignExpr(BTNode *root);
void AssemblyTranslation(BTNode *root);
void Exit(int num);
int Find(char *name, bool establishIfNone);

void error(ErrorType errorNum);


bool endingSign = false, errorMark = false;
TokenSet getToken(void)
{
    int i;
    char c;

    while ( (c = fgetc(stdin)) == ' ' || c== '\t' );  // 忽略空白字元
	if(c == EOF)
	{
		endingSign = true;
		return EOFTOKEN;
	}
    if (isdigit(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i<MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    } else if (c == '+' || c == '-') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return ADDSUB;
	} else if(c == '&' || c == '|' || c == '^'){
		lexeme[0] = c;
        lexeme[1] = '\0';
        return ANDORXOR;
    } else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    } else if (c == '\n') {
        lexeme[0] = '\0';
        return END;
    } else if (c == '=') {
        strcpy(lexeme, "=");
        return ASSIGN;
    } else if (c == '(') {
        strcpy(lexeme, "(");
        return LPAREN;
    } else if (c == ')') {
        strcpy(lexeme, ")");
        return RPAREN;
    } else if (isalpha(c) || c == '_') {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isalpha(c) || isdigit(c) || c == '_') {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;
    } else {
        return UNKNOWN;
    }
}

void advance(void)
{
    lookahead = getToken();
    if(lookahead == UNKNOWN) Exit(1);
    else if(lookahead == EOFTOKEN) endingSign = true;
}

int match(TokenSet token)
{
    if (lookahead == UNKNOWN) advance();
    return token == lookahead;
}

char* getLexeme(void)
{
    return lexeme;
}

/* create a node without any child */
BTNode* makeNode(TokenSet tok, const char *lexe)
{
	BTNode *node = (BTNode*) malloc(sizeof(BTNode));
	strcpy(node->lexeme, lexe);
	node->token= tok;
	node->val = 0;
	node->left = NULL;
	node->right = NULL;
	return node;
}

/* clean a tree */
void freeTree(BTNode *root)
{
	if (root!=NULL) {
		freeTree(root->left);
		freeTree(root->right);
		free(root);
	}
}

/* print a tree by pre-order */
void printPrefix(BTNode *root)
{
	if (root != NULL) {
		printf("%s ", root->lexeme);
		printPrefix(root->left);
		printPrefix(root->right);
	}
}

/* traverse the syntax tree by pre-order
   and evaluate the underlying expression */
int evaluateTree(BTNode *root)
{
	int retval = 0, lv, rv;
	if (root != NULL) {
		switch (root->token) {
		case ID:
		case INT:
			retval = root->val;
			break;
		case ASSIGN:
		case ADDSUB:
		case MULDIV:
		case ANDORXOR:
			lv = evaluateTree(root->left);
			rv = evaluateTree(root->right);
			if (strcmp(root->lexeme, "+") == 0)
				retval = lv + rv;
			else if (strcmp(root->lexeme, "-") == 0)
				retval = lv - rv;
			else if(strcmp(root->lexeme, "&") == 0)
				retval = lv & rv;
			else if(strcmp(root->lexeme, "|") == 0)
				retval = lv | rv;
			else if(strcmp(root->lexeme, "^") == 0)
				retval = lv ^ rv;
			else if (strcmp(root->lexeme, "*") == 0)
				retval = lv * rv;
			else if (strcmp(root->lexeme, "/") == 0) {
				if (rv==0)
					error(NAN);
				else
					retval = lv / rv;
			} else if (strcmp(root->lexeme, "=") == 0)
				retval = setval(root->left->lexeme, rv);
			break;
		default:
			retval = 0;
		}
	}
	return retval;
}

int getval(void)
{
	int i, retval, found;

	if (match(INT)) {
		retval = atoi(getLexeme());
	} else if (match(ID)) {
		i = 0;
		found = 0;
		retval = 0;
		while (i<sbcount && !found) {
			if (strcmp(getLexeme(), table[i].name)==0) {
				retval = table[i].val;
				found = 1;
				break;
			} else {
				i++;
			}
		}
		if (!found) {
			if (sbcount < TBLSIZE) {
				strcpy(table[sbcount].name, getLexeme());
				table[sbcount].val = 0;
				sbcount++;
			} else {
				error(RUNOUT);
			}
		}
	}
	return retval;
}

int setval(char *str, int val)
{
	int i, retval = 0;
	i = 0;
	while (i<sbcount) {
		if (strcmp(str, table[i].name)==0) {
			table[i].val = val;
			retval = val;
			break;
		} else {
			i++;
		}
	}
	return retval;
}

//  expr        := term expr_tail
//  expr_tail   := ADDSUB term expr_tail | NIL | ANDOR term expr_tail
// todo
BTNode* expr(void)
{
	BTNode *retp, *left;
	retp = left = term();
	while (match(ADDSUB) || match(ANDORXOR)) { // tail recursion => while
		retp = makeNode(match(ADDSUB) ? ADDSUB : ANDORXOR, getLexeme());
		advance();
		retp->right = term();
		retp->left = left;
		left = retp;
	}
	return retp;
}

//  term        := factor term_tail
//  term_tail := MULDIV factor term_tail | NIL
BTNode* term(void)
{
	BTNode *retp, *left;
	retp = left = factor();
	while (match(MULDIV)) { // tail recursion => while
		retp = makeNode(MULDIV, getLexeme());
		advance();
		retp->right = factor();
		retp->left = left;
		left = retp;
	}
	return retp;
}

BTNode* factor(void)
{
	BTNode* retp = NULL;
	char tmpstr[MAXLEN];

	if (match(INT)) {
		retp =  makeNode(INT, getLexeme());
		retp->val = getval();
		advance();
	} else if (match(ID)) {
		BTNode* left = makeNode(ID, getLexeme());
		left->val = getval();
		strcpy(tmpstr, getLexeme());
		advance();
		if (match(ASSIGN)) {
			retp = makeNode(ASSIGN, getLexeme());
			advance();
			retp->right = expr();
			retp->left = left;
		} else {
			retp = left;
		}
	} else if (match(ADDSUB)) {
		strcpy(tmpstr, getLexeme());
		advance();
		if (match(ID) || match(INT)) {
			retp = makeNode(ADDSUB, tmpstr);
			if (match(ID))
				retp->right = makeNode(ID, getLexeme());
			else
				retp->right = makeNode(INT, getLexeme());
			retp->right->val = getval();
			retp->left = makeNode(INT, "0");
			retp->left->val = 0;
			advance();
		} else {
			error(NOTNUMID);
		}
	} else if (match(LPAREN)) {
		advance();
		retp = expr();
		if (match(RPAREN)) {
			advance();
		} else {
			error(MISPAREN);
		}
	} else if(match(EOFTOKEN)){
		return NULL;
	} else {
		error(NOTNUMID);
	}
	return retp;
}

void error(ErrorType errorNum)
{
	Exit(1);
	return;
	
	switch (errorNum) {
	case MISPAREN:
		fprintf(stderr, "Mismatched parenthesis\n");
		break;
	case NOTNUMID:
		fprintf(stderr, "Number or identifier expected\n");
		break;
	case NOTFOUND:
		fprintf(stderr, "%s not defined\n", getLexeme());
		break;
	case RUNOUT:
		fprintf(stderr, "Out of memory\n");
		break;
	case NAN:
		fprintf(stderr, "Not a number\n");
	}
	exit(0);
}

int NumOfAssign(BTNode *root)
{
	if(root == NULL) return 0;
	return NumOfAssign(root->left) + (root->token == ASSIGN ? 1 : 0) + NumOfAssign(root->right);
}

bool isValidAssignExpr(BTNode *root)
{
	return ((root->token == ASSIGN) && (NumOfAssign(root) == 1) ||
		(root->token != ASSIGN) && (NumOfAssign(root) == 0));
}

Evaluation* Evaluate(BTNode *root, bool regOnly)
{
	if(root == NULL)
	{
		endingSign = true;
		return NULL;
	}
	int i, id, validReg = -1;
	Evaluation *result, *left, *right;
	// todo
	if(regOnly || true)
	{
		switch(root->token)
		{
			case ID:
				// Find the ID
				id = Find(root->lexeme, false);
				
				result = (Evaluation*)malloc(sizeof(Evaluation));
				result->isReg = true;
				// Find a valid register
				for(i = 7; i>=0; i--) if(!regInUse[i]) validReg = i;
				if(id == -1 || validReg == -1)
				{
					Exit(1);
					return NULL;
				}
				regInUse[validReg] = true;
				result->data = validReg;
				printf("MOV r%d [%d]\n", validReg, id*4);
				return result;
				break;
			case INT:
				result = (Evaluation*)malloc(sizeof(Evaluation));
				result->isReg = true;
				// Find a valid register
				for(i = 7; i>=0; i--) if(!regInUse[i]) validReg = i;
				if(validReg == -1)
				{
					Exit(1);
					return NULL;
				}
				regInUse[validReg] = true;
				result->data = validReg;
				printf("MOV r%d %d\n", validReg, root->val);
				return result;
				break;
   			case ADDSUB:
   				left =  Evaluate(root->left, true);
   				right = Evaluate(root->right, true);
   				
   				if(left == NULL || right == NULL)
   				{
   					free(left);
   					free(right);
   					endingSign = true;
   					return NULL;
				}
   				if(strcmp(root->lexeme, "+") == 0)
   					printf("ADD r%d r%d\n", left->data, right->data);
				else
					printf("SUB r%d r%d\n", left->data, right->data);
				regInUse[right->data] = false;
				free(right);
				return left;
				break;
   			case ANDORXOR:
   				left =  Evaluate(root->left, true);
   				right = Evaluate(root->right, true);
   				
   				if(left == NULL || right == NULL)
   				{
   					free(left);
   					free(right);
   					endingSign = true;
   					return NULL;
				}
   				if(strcmp(root->lexeme, "&") == 0)
   					printf("AND r%d r%d\n", left->data, right->data);
				else if(strcmp(root->lexeme, "|") == 0)
					printf("OR r%d r%d\n", left->data, right->data);
				else
					printf("XOR r%d r%d\n", left->data, right->data);
				regInUse[right->data] = false;
				free(right);
				return left;
				break;
   			case MULDIV:
   				left =  Evaluate(root->left, true);
   				right = Evaluate(root->right, true);
   				if(left == NULL || right == NULL)
   				{
   					free(left);
   					free(right);
   					endingSign = true;
   					return NULL;
				}
   				if(strcmp(root->lexeme, "*") == 0)
   					printf("MUL r%d r%d\n", left->data, right->data);
				else
					printf("DIV r%d r%d\n", left->data, right->data);
				regInUse[right->data] = false;
				free(right);
				return left;
				break;
		}
		//Evaluation *right = Evaluate(root->right, false);
	}
}

int Find(char *name, bool establishIfNone)
{
	int i;
	for(i = 0; i<sbcount; i++)
	{
		if(strcmp(table[i].name, name) == 0)
		{
			if(table[i].recognized)
			{
				return i;
			}
			else if(!table[i].recognized && establishIfNone)
			{
				table[i].recognized = true;
				return i;
			}
		}
	}
	// todo: memory overflow?
	if(establishIfNone)
	{
		if(sbcount*4 >= 256) Exit(1);
		strcpy(table[sbcount++].name, name);
		return sbcount-1;
	}
	else
	{
		return -1;
	}
}

void AssemblyTranslation(BTNode *root)
{
	// Assign right to left
	// Find the left value
	int id = Find(root->left->lexeme, true);
	// Find the right value
	Evaluation *right = Evaluate(root->right, true);
	if(right == NULL)
	{
		endingSign = true;
		return;
	}
	printf("MOV [%d] r%d\n", id*4, right->data);
	regInUse[right->data] = false;
	free(right);
}

void Exit(int num)
{
	if(num == 1 && !errorMark)printf("EXIT %d\n", num);
	if(num == 1) errorMark = true;
}

void statement(void)
{	
	if(endingSign) return;
	BTNode* retp;

	if (match(END)) {
		if(endingSign || errorMark) return;
		#ifdef DEBUG
			printf(">> ");
		#endif
		advance();
	} else {
		retp = expr();
		if (match(END)) {
			#ifdef DEBUG
				printf("  Result: %d\n  Prefix Expression:", evaluateTree(retp));
				printPrefix(retp);
				printf("\n");
				printf("Assembly Code: \n");
			#endif
			// Check if this is an assign expr
			if(!isValidAssignExpr(retp))
			{
				Exit(1);
				freeTree(retp);
				return;
			}
			if(endingSign || errorMark || NumOfAssign(retp) == 0)
			{
				freeTree(retp);
				return;
			}
			
			AssemblyTranslation(retp);
			freeTree(retp);
			#ifdef DEBUG
				printf(">> ");
			#endif
			if(!endingSign && !errorMark) advance();
		}
	}
}

int main()
{
	//freopen("output.txt","w",stdout);
	sbcount = 3;
	strcpy(table[0].name, "x");
	strcpy(table[1].name, "y");
	strcpy(table[2].name, "z");
	table[0].recognized = true;
	table[1].recognized = true;
	table[2].recognized = true;
	#ifdef DEBUG
		printf(">> ");
	#endif
	while (!endingSign && !errorMark) {
		statement();
	}
	if(!errorMark)
	{
		printf("MOV r0 [0]\n");
		printf("MOV r1 [4]\n");
		printf("MOV r2 [8]\n");
		printf("EXIT 0\n");
	}
	
	return 0;
}
