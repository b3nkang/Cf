global _main
section .text
_main:
    push rbp
    mov rbp, rsp
    sub rsp, 208
    mov rax, 2
    mov [rbp - 8], rax
    mov rax, 3
    mov [rbp - 16], rax
    mov rax, [rbp - 8]
    mov [rbp - 1008], rax
    mov rax, 4
    mov rbx, rax
    mov rax, [rbp - 1008]
    imul rax, rbx
    mov [rbp - 1016], rax
    mov rax, [rbp - 16]
    mov rbx, rax
    mov rax, [rbp - 1016]
    cmp rax, rbx
    mov rax, 0
    setge al
    movzx rax, al
    mov [rbp - 24], rax
    mov rax, [rbp - 8]
    mov [rbp - 1008], rax
    mov rax, 3
    mov rbx, rax
    mov rax, [rbp - 1008]
    imul rax, rbx
    mov [rbp - 1016], rax
    mov rax, [rbp - 16]
    mov [rbp - 1008], rax
    mov rax, 2
    mov rbx, rax
    mov rax, [rbp - 1008]
    imul rax, rbx
    mov rbx, rax
    mov rax, [rbp - 1016]
    cmp rax, rbx
    mov rax, 0
    setge al
    movzx rax, al
    mov [rbp - 32], rax
    mov rax, [rbp - 8]
    mov [rbp - 1016], rax
    mov rax, [rbp - 16]
    mov rbx, rax
    mov rax, [rbp - 1016]
    cmp rax, rbx
    mov rax, 0
    setle al
    movzx rax, al
    mov [rbp - 40], rax
    mov rax, [rbp - 8]
    mov [rbp - 1008], rax
    mov rax, 3
    mov rbx, rax
    mov rax, [rbp - 1008]
    imul rax, rbx
    mov [rbp - 1016], rax
    mov rax, [rbp - 16]
    mov [rbp - 1008], rax
    mov rax, 2
    mov rbx, rax
    mov rax, [rbp - 1008]
    imul rax, rbx
    mov rbx, rax
    mov rax, [rbp - 1016]
    cmp rax, rbx
    mov rax, 0
    setle al
    movzx rax, al
    mov [rbp - 48], rax
    mov rax, [rbp - 8]
    mov [rbp - 1008], rax
    mov rax, 3
    mov rbx, rax
    mov rax, [rbp - 1008]
    imul rax, rbx
    mov [rbp - 1016], rax
    mov rax, [rbp - 16]
    mov [rbp - 1008], rax
    mov rax, 2
    mov rbx, rax
    mov rax, [rbp - 1008]
    imul rax, rbx
    mov rbx, rax
    mov rax, [rbp - 1016]
    cmp rax, rbx
    mov rax, 0
    sete al
    movzx rax, al
    mov [rbp - 56], rax
    mov rax, [rbp - 8]
    mov [rbp - 1016], rax
    mov rax, [rbp - 16]
    mov rbx, rax
    mov rax, [rbp - 1016]
    cmp rax, rbx
    mov rax, 0
    sete al
    movzx rax, al
    mov [rbp - 64], rax
    mov rax, [rbp - 8]
    mov [rbp - 1016], rax
    mov rax, [rbp - 16]
    mov rbx, rax
    mov rax, [rbp - 1016]
    cmp rax, rbx
    mov rax, 0
    setne al
    movzx rax, al
    mov [rbp - 72], rax
    mov rax, [rbp - 8]
    mov [rbp - 1008], rax
    mov rax, 3
    mov rbx, rax
    mov rax, [rbp - 1008]
    imul rax, rbx
    mov [rbp - 1016], rax
    mov rax, [rbp - 16]
    mov [rbp - 1008], rax
    mov rax, 2
    mov rbx, rax
    mov rax, [rbp - 1008]
    imul rax, rbx
    mov rbx, rax
    mov rax, [rbp - 1016]
    cmp rax, rbx
    mov rax, 0
    setne al
    movzx rax, al
    mov [rbp - 80], rax
    mov rax, [rbp - 8]
    mov [rbp - 1008], rax
    mov rax, 4
    mov rbx, rax
    mov rax, [rbp - 1008]
    imul rax, rbx
    mov [rbp - 1016], rax
    mov rax, [rbp - 16]
    mov rbx, rax
    mov rax, [rbp - 1016]
    cmp rax, rbx
    mov rax, 0
    setg al
    movzx rax, al
    mov [rbp - 88], rax
    mov rax, [rbp - 8]
    mov [rbp - 1008], rax
    mov rax, 3
    mov rbx, rax
    mov rax, [rbp - 1008]
    imul rax, rbx
    mov [rbp - 1016], rax
    mov rax, [rbp - 16]
    mov [rbp - 1008], rax
    mov rax, 2
    mov rbx, rax
    mov rax, [rbp - 1008]
    imul rax, rbx
    mov rbx, rax
    mov rax, [rbp - 1016]
    cmp rax, rbx
    mov rax, 0
    setg al
    movzx rax, al
    mov [rbp - 96], rax
    mov rax, [rbp - 8]
    mov [rbp - 1016], rax
    mov rax, [rbp - 16]
    mov rbx, rax
    mov rax, [rbp - 1016]
    cmp rax, rbx
    mov rax, 0
    setl al
    movzx rax, al
    mov [rbp - 104], rax
    mov rax, [rbp - 8]
    mov [rbp - 1008], rax
    mov rax, 3
    mov rbx, rax
    mov rax, [rbp - 1008]
    imul rax, rbx
    mov [rbp - 1016], rax
    mov rax, [rbp - 16]
    mov [rbp - 1008], rax
    mov rax, 2
    mov rbx, rax
    mov rax, [rbp - 1008]
    imul rax, rbx
    mov rbx, rax
    mov rax, [rbp - 1016]
    cmp rax, rbx
    mov rax, 0
    setl al
    movzx rax, al
    mov [rbp - 112], rax
    mov rax, [rbp - 24]
    mov [rbp - 936], rax
    mov rax, [rbp - 32]
    mov rbx, rax
    mov rax, [rbp - 936]
    add rax, rbx
    mov [rbp - 944], rax
    mov rax, [rbp - 40]
    mov rbx, rax
    mov rax, [rbp - 944]
    add rax, rbx
    mov [rbp - 952], rax
    mov rax, [rbp - 48]
    mov rbx, rax
    mov rax, [rbp - 952]
    add rax, rbx
    mov [rbp - 960], rax
    mov rax, [rbp - 56]
    mov rbx, rax
    mov rax, [rbp - 960]
    add rax, rbx
    mov [rbp - 968], rax
    mov rax, [rbp - 64]
    mov rbx, rax
    mov rax, [rbp - 968]
    add rax, rbx
    mov [rbp - 976], rax
    mov rax, [rbp - 72]
    mov rbx, rax
    mov rax, [rbp - 976]
    add rax, rbx
    mov [rbp - 984], rax
    mov rax, [rbp - 80]
    mov rbx, rax
    mov rax, [rbp - 984]
    add rax, rbx
    mov [rbp - 992], rax
    mov rax, [rbp - 88]
    mov rbx, rax
    mov rax, [rbp - 992]
    add rax, rbx
    mov [rbp - 1000], rax
    mov rax, [rbp - 96]
    mov rbx, rax
    mov rax, [rbp - 1000]
    add rax, rbx
    mov [rbp - 1008], rax
    mov rax, [rbp - 104]
    mov rbx, rax
    mov rax, [rbp - 1008]
    add rax, rbx
    mov [rbp - 1016], rax
    mov rax, [rbp - 112]
    mov rbx, rax
    mov rax, [rbp - 1016]
    add rax, rbx
    leave
    and rsp, -16
    mov rdi, rax
    mov rax, 0x2000001
    syscall
