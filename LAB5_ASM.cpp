#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>

signed char a, b, c, d, e, y;
char input_str[16];
char output_str[16];
char* p_input = input_str;
void* addr_a, * addr_b, * addr_c, * addr_d, * addr_e;

const char* fmt_prompt = "Введите %c (ЗнЦЦЦ): ";
const char* fmt_scan = "%s";

int main() {
    setlocale(LC_ALL, "Russian");

    signed char* vars[] = { &a, &b, &c, &d, &e };
    char names[] = { 'a', 'b', 'c', 'd', 'e' };

    printf("Функция: y = a / b * c - d + e\n\n");

    __asm {
        xor edi, edi            
        input_loop :
        cmp edi, 5
            je input_done
            movsx eax, names[edi]
            push eax
            push fmt_prompt
            call printf
            add esp, 8
            push p_input
            push fmt_scan
            call scanf
            add esp, 8

            call proc_ascbin      

            mov edx, vars[edi * 4]  
            mov[edx], al          

            inc edi
            jmp input_loop

            input_done :
        jmp main_logic 

        proc_ascbin:
        push ebp
            mov ebp, esp
            push esi
            push ebx
            mov esi, p_input
            xor eax, eax
            xor ebx, ebx
            mov bl, 1
            mov al, [esi]
            cmp al, '-'
            jne ascbin_check_plus
            mov bl, -1
            inc esi
            jmp ascbin_start_conv
            ascbin_check_plus :
        cmp al, '+'
            jne ascbin_start_conv
            inc esi
            ascbin_start_conv :
        xor ecx, ecx
            ascbin_parse_loop :
        mov al, [esi]
            test al, al
            jz ascbin_done
            cmp al, 10
            je ascbin_done
            sub al, '0'
            imul cx, 10
            movsx ax, al
            add cx, ax
            inc esi
            jmp ascbin_parse_loop
            ascbin_done :
        mov ax, cx
            imul bl
            pop ebx
            pop esi
            pop ebp
            ret

            proc_func :
        push ebp
            mov ebp, esp
            push ebx
            mov eax, [ebp + 8]   
            mov al, [eax]        
            cbw
            mov ecx, [ebp + 12]  
            mov bl, [ecx]
            idiv bl             
            mov ecx, [ebp + 16]  
            mov bl, [ecx]
            imul bl              
            mov ecx, [ebp + 20]  
            sub al, [ecx]        
            mov ecx, [ebp + 24]  
            add al, [ecx]        
            mov y, al
            pop ebx
            pop ebp
            ret

            proc_binasc :
        push ebp
            mov ebp, esp
            push edi
            push ebx
            mov edx, [ebp + 8]   
            mov al, [edx]      
            lea edi, output_str
            mov ebx, edi
            test al, al
            jns binasc_pos
            mov byte ptr[edi], '-'
            neg al
            inc edi
            jmp binasc_start_digit
            binasc_pos :
        mov byte ptr[edi], '+'
            inc edi
            binasc_start_digit :
        movsx ax, al
            mov cl, 10
            div cl
            mov dl, ah
            xor ah, ah
            div cl
            add al, '0'
            mov[edi], al
            add ah, '0'
            mov[edi + 1], ah
            add dl, '0'
            mov[edi + 2], dl
            mov byte ptr[edi + 3], 0
            mov eax, ebx
            pop ebx
            pop edi
            pop ebp
            ret

            main_logic :
    }

    addr_a = &a; addr_b = &b; addr_c = &c; addr_d = &d; addr_e = &e;
    char* final_str;

    __asm {

        push addr_e
        push addr_d
        push addr_c
        push addr_b
        push addr_a
        call proc_func
        add esp, 20
        lea eax, y         
        push eax            
        call proc_binasc
        add esp, 4
        mov final_str, eax  
    }

    printf("\nРезультат y = %d (Строка: %s)\n", (int)y, final_str);
    return 0;
}

