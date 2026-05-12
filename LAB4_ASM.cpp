#include <stdio.h>

int main() {

    const char* input = "-1234";

    int result = 0;          
    char binaryStr[33];       
    binaryStr[32] = '\0';   

    __asm {
        mov esi, input        
        xor eax, eax         
        xor ebx, ebx          
        xor edi, edi          

        mov bl, [esi]
        cmp bl, '-'
        jne parse_digits
        mov edi, 1            
        inc esi               

        parse_digits :
        mov bl, [esi]
            test bl, bl           
            jz apply_sign

           
            lea eax, [eax + eax * 4]
            sub bl, '0'
            add eax, ebx

            inc esi
            jmp parse_digits

            apply_sign :
        test edi, edi
            jz store_val
            neg eax              

            store_val :
        mov result, eax       
 
        mov eax, result       
        lea edi, binaryStr   
        mov ecx, 32           

        binary_loop:
        rol eax, 1           
            jc set_one            

            mov byte ptr[edi], '0'
            jmp next_step

            set_one :
        mov byte ptr[edi], '1'

            next_step :
            inc edi              
            loop binary_loop      
    }

    printf("Input:  %s\n", input);
    printf("Result: %s\n", binaryStr);
    printf("Result: %d\n", result);

    return 0;
}