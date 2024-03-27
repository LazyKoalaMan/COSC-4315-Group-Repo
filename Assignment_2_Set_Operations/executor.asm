section .text
global p
    
p:
    push ebp             ; Save the base pointer
    mov ebp, esp         ; Set up the base pointer

    mov eax, [ebp+8]     ; Move the argument x into eax
    cmp eax, 0           ; Compare x with 0
    jle else_block       ; Jump to else_block if x <= 0
    dec eax              ; Decrement x by 1
    jmp end_if           ; Jump to the end of the if-else block
else_block:
    xor eax, eax         ; Set eax to 0 if x <= 0
end_if:
    pop ebp              ; Restore the base pointer
    ret                  ; Return from the function
