#include <stdio.h>
#include <stdlib.h>

#define TAPESIZE 9999
#define FE 48

void op(char* snippet, int len, unsigned char* tape, int* ptr);
int ap(char* snippet, int i);
int intcat(int x, int y);

int main(int argc, char* argv[]){
	char* snippet = NULL;
	size_t len = 0;
	unsigned char tape[TAPESIZE] = {0};
	int read, loop, ptr = loop = 0;

	read = getline(&snippet, &len, stdin);
	op(snippet, read, tape, &ptr);

	free(snippet);
	return 0;
}

void op(char* snippet, int len, unsigned char* tape, int* ptr){
	int i, lc, mul;
	for(i = 0; i < len; i++){
		switch(snippet[i]){
			case '.':
				putchar(tape[*ptr]);
				break;
			case ',':
				tape[*ptr] = getchar();
				break;
			case '+':
				mul = ap(snippet, i);
				tape[*ptr] += mul;
				break;
			case '-':
				mul = ap(snippet, i);
				tape[*ptr] -= mul;
				break;
			case '>':
				mul = ap(snippet, i);
				(*ptr) += mul;
				break;
			case '<':
				mul = ap(snippet, i);
				(*ptr) -= mul;
				break;
			case ']':
				if(tape[*ptr] != 0){
					lc = 1;
					while(lc > 0){
						i--;
						if(snippet[i] == '['){
							lc--;
						}
						else if(snippet[i] == ']'){
							lc++;
						}
					}
				}
				break;
		}
	}
}

int ap(char* snippet, int i){
	int j = 1;
	int mul = 0;
	if('0' <= snippet[i+j] && snippet[i+j] <= '9'){
		while('0' <= snippet[i+j] && snippet[i+j] <= '9'){
			mul = intcat(mul, snippet[i+j] - FE);
			j++;
		}
	}
	else{
		mul = 1;
	}
	return mul;
}

int intcat(int x, int y){
	int pow = 10;
	while(y >= pow){
		pow *= 10;
	}
	return x * pow + y;        
}
