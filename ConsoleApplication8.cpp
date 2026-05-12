#include <stdio.h>



#define RANGE1(i,b,res) __asm {\
  __asm  {mov al, b} \
  __asm  {imul al,13} \
  __asm { sub al, byte ptr i }\
  __asm {mov res, al}; \
}
#define RANGE2(i, res) __asm { \
__asm {mov al, byte ptr i} \
__asm {cbw} \
__asm {mov bl, 2} \
__asm {idiv bl} \
__asm {imul al, 7}  \
__asm {mov res, al}; \
}



int main() {
    
    signed char a, b = 3, c = 4, d = 2, e = 1, y;
    signed char args[10];
    signed char funcs[10]; 

    printf("y = a + b/c * d - e\n");
    printf("b = %d, c = %d, d = %d, e = %d\n\n", b, c, d, e);

    for (int i = 1; i <= 10; i++) {
        int range = 1;
        __asm {
            cmp i, 5
            jg r2
            mov range, 1
            jmp next
            r2 :
            mov range, 2
                next :
        }

        if (range == 1) {
            a = RANGE1(i, b, y)
        }
        else {
            a = RANGE2(i, y)
        }

        y = FUNC_Y(a, b, c, d, e);

        args[i - 1] = a;
        funcs[i - 1] = y;
        printf("%d - %d\n", args[i - 1], funcs[i - 1]);
    }
    return 0;
}