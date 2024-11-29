global _main
section .text
_main:
    push rbp
    mov rbp, rsp
    sub rsp, 128
    mov rax, 6
    mov [rbp - 8], rax
    mov rax, 6
    mov rbx, rax
    mov rax, [rbp - 8]
    add rax, rbx
    mov [rbp - 8], rax
    mov rax, 2
    mov rbx, rax
    mov rax, [rbp - 8]
    cqo
    idiv rbx
    mov [rbp - 8], rax
    mov rax, 3
    mov rbx, rax
    mov rax, [rbp - 8]
    imul rax, rbx
    mov [rbp - 8], rax
    mov rax, 9
    mov rbx, rax
    mov rax, [rbp - 8]
    cqo
    idiv rbx
    mov [rbp - 8], rax
    mov rax, 2
    mov rbx, rax
    mov rax, [rbp - 8]
    sub rax, rbx
    leave
    and rsp, -16
    mov rdi, rax
    mov rax, 0x2000001
    syscall
