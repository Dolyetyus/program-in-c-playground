.data
    CLOCKS_PER_SEC: .quad 1000000
    
.text
    output_format: .asciz "Time taken to perform operations: %f seconds"
    
.global main
main:
    pushq       %rbp
    movq        %rsp, %rbp
    
    movq        $5, %r12
    movq        $10, %r13
    
    call        clock
    movq        %rax, %r8
    
    movq        $0, %rcx
    
loop:
    cmpq        $250000000, %rcx
    je          result
    
    addq        %r12, %r13
    subq        %r12, %r13
    imulq       %r12, %r13
    cvtsi2sd    %r13d, %xmm0
    cvtsi2sd    %r12d, %xmm1
    divsd       %xmm1, %xmm0
    cvttsd2si   %xmm0, %r13d
    
    incq        %rcx
    jmp         loop

result:
    call        clock
    subq        %r8, %rax
    
    cvtsi2sd    %rax, %xmm0
    cvtsi2sd    CLOCKS_PER_SEC(%rip), %xmm1
    divsd       %xmm1, %xmm0
    
    mov         $64, %al
    leaq        output_format(%rip), %rdi
    call        printf            
    
    movq        %rbp, %rsp
    popq        %rbp
    
    movq        $0, %rax
    ret
