data segment
	a8 db 41h
	a16 dw 41h
	a32 dd 41h

	b8 db 0A8h
	b16 dw 0FFA8h
	b32 dd 0FFFFFFA8h
data ends

code segment
assume cs:code, ds:data, ss:nothing

start:		mov ax, data
		mov ds, ax

quit:		mov ax, 4c00h
		int 21
code ends
end start		