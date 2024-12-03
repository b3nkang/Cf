# Cf (C-french) Compiler

An implementation of Cf, an in-progress compiler that forms a programming language with French keywords and, currently, C-like syntax, but the intention is to integrate nicer Python-like syntax in the future. The compiler generates x86_64 assembly code for macOS.

## Language Features

Cf currently supports:

- Variable declarations and assignments with `soit` (roughly equivalent to `let`)
- Basic arithmetic operations (+, -, \*, /)
- Comparison operations (==, !=, <, <=, >, >=)
- Integer literals
- Expression grouping with parentheses
- Variable references in expressions
- Error handling:
  - Syntax error detection with line and column numbers
  - Variable redeclaration checks
  - Undefined variable usage detection
  - Missing semicolon detection
  - Invalid operator usage detection
  - Stack overflow protection for complex expressions
- Return statements with `retourner`

### Syntax

- Variables are declared using the `soit` keyword
- Return statements use the `retourner` keyword
- Statements must end with semicolons
- Expressions follow standard operator precedence rules

### Operator Precedence (highest to lowest)

1. Parentheses `()`
2. Multiplication and division `*`, `/`
3. Addition and subtraction `+`, `-`
4. Comparison operators `==`, `!=`, `<`, `<=`, `>`, `>=`

## Examples

### Basic Arithmetic

```Cf
retourner (((6 + 6) / 2) * 3) / 9 - 2;
```

This example demonstrates nested arithmetic expressions and operator precedence.

### Variable Declaration and Distance Calculation

```Cf
soit x1 = 7;
soit y1 = 11;
soit x2 = 4;
soit y2 = 8;
soit dx = x2 - x1;
soit dy = y2 - y1;
soit distanceCarre = dx * dx + dy * dy;
retourner distanceCarre;
```

This example calculates the squared distance between two points.

### Comparison Operations

```Cf
soit valeur1 = 2;
soit valeur2 = 3;

soit resultatEgal = valeur1 == valeur2;
soit resultatDifferent = valeur1 != valeur2;
soit resultatInferieur = valeur1 < valeur2;
soit resultatSuperieur = valeur1*4 > valeur2;
soit resultatInferieurOuEgal = valeur1 <= valeur2;
soit resultatSuperieurOuEgal = valeur1*3 >= valeur2*2;

retourner resultatEgal + resultatDifferent +
         resultatInferieur + resultatSuperieur +
         resultatInferieurOuEgal + resultatSuperieurOuEgal;
```

This example demonstrates all comparison operators and compound expressions.

## Building and Running

### Prerequisites

- gcc
- nasm
- Make
- macOS

### Building the Compiler

```bash
make
```

### Compiling a Cf Program

```bash
./cf input.cf
```

This will generate an assembly file named `test4.asm`.

### Running a Complete Build Pipeline

```bash
make full TEST_FILE_INPUT=your_input.cf
```

This will:

1. Compile your Cf program to assembly
2. Assemble it to an object file
3. Link it into an executable
4. Run the executable and display its return value

### Cleaning Build Files

```bash
make clean
```

## Implementation Details

The compiler follows a traditional compilation pipeline:

1. Lexical analysis (tokenizer)
2. Parsing (recursive descent parser)
3. AST generation
4. Code generation (x86_64 assembly)

The generated assembly code uses proper stack management for variables and temporary values, ensuring correct evaluation of complex expressions.

## Grammar

<!-- ![grammar_latex_cogs](https://latex.codecogs.com/png.latex?%5Cdpi%7B100%7D&space;%5Cbegin%7Balign*%7D&space;%5Ctext%7Bprogram%7D&space;&%5Cto&space;%5Ctext%7Bstatement*%7D&space;%5Ctext%7BEOF%7D&space;%5C%5C&space;%5Ctext%7Bstatement%7D&space;&%5Cto&space;%5Ctext%7Breturn%7D&space;%5C%5C&space;%5Ctext%7Breturn%7D&space;&%5Cto&space;%5Bretourner%5D%5Ctext%7B&space;expr&space;%5B;%5D%7D&space;%5C%5C&space;%5Ctext%7Bexpr%7D&space;&%5Cto&space;%5Ctext%7Bliteral%7D&space;%5C%5C&space;%5Ctext%7Bliteral%7D&space;&%5Cto&space;%5Ctext%7Bnumber%7D&space;%5C%5C&space;%5Cend%7Balign*%7D) -->

<!-- ![grammar_latex_cogs](<https://latex.codecogs.com/png.image?%5Cinline%20%5Clarge%20%5Cdpi%7B150%7D%5Cbg%7Bblack%7D$$%5Cbegin%7Balign*%7D%5Ctext%7Bprogram%7D&%5Cto%5Ctext%7Bstatement%7D*%5Ctext%7BEOF%7D%5C%5C%5Ctext%7Bstatement%7D&%5Cto%5Ctext%7Breturn%7D%5C%5C%5Ctext%7Breturn%7D&%5Cto%5B%5Ctext%7Bretourner%7D%5D%5Ctext%7Bexpr%5B;%5D%7D%5C%5C%5Ctext%7Bexpr%7D&%5Cto%5Ctext%7Bterm%7D%5C((%5B+%5D%7C%5B-%5D)%5Ctext%7Bterm%7D)*%5C%5C%5Ctext%7Bterm%7D&%5Cto%5Ctext%7Bfactor%7D%5C((%5B*%5D%7C%5B/%5D)%5Ctext%7Bfactor%7D)*%5C%5C%5Ctext%7Bfactor%7D&%5Cto%5B(%5D%5Ctext%7Bexpr%7D%5B)%5D%5C;%7C%5C;%5Ctext%7Bprimary%7D%5C%5C%5Ctext%7Bprimary%7D&%5Cto%5Ctext%7Bnumber%7D%5Cend%7Balign*%7D$$>) -->

<!-- $$
\begin{align*}
\text{program} &\to \text{statement}* \text{ EOF} \\
\text{statement} &\to \text{return} \;|\; \text{varDecl} \\
\text{return} &\to [retourner]\text{ expr [;]} \\
\text{varDecl} &\to [soit]\text{ identifier [=] expr [;]} \\
\text{expr} &\to \text{term}\ (([+]|[-])\text{ term})* \\
\text{term} &\to \text{factor}\ (([*]|[/])\text{ factor})* \\
\text{factor} &\to [(]\text{ expr }[)] \;|\; \text{primary} \\
\text{primary} &\to \text{number} \;|\; \text{identifier}
\end{align*}
$$ -->

<!-- ![grammar_latex_cogs](<https://latex.codecogs.com/png.image?%5Cinline%20%5Clarge%20%5Cdpi%7B150%7D%5Cbg%7Bblack%7D$$%5Cbegin%7Balign*%7D%5Ctext%7Bprogram%7D&%5Cto%5Ctext%7Bstatement%7D*%5Ctext%7BEOF%7D%5C%5C%5Ctext%7Bstatement%7D&%5Cto%5Ctext%7Breturn%7D%5C;%7C%5C;%5Ctext%7BvarDecl%7D%5C%5C%5Ctext%7Breturn%7D&%5Cto%5Bretourner%5D%5Ctext%7Bexpr%5B;%5D%7D%5C%5C%5Ctext%7BvarDecl%7D&%5Cto%5Bsoit%5D%5Ctext%7Bidentifier%5B=%5Dexpr%5B;%5D%7D%5C%5C%5Ctext%7Bexpr%7D&%5Cto%5Ctext%7Bterm%7D%5C((%5B+%5D%7C%5B-%5D)%5Ctext%7Bterm%7D)*%5C%5C%5Ctext%7Bterm%7D&%5Cto%5Ctext%7Bfactor%7D%5C((%5B*%5D%7C%5B/%5D)%5Ctext%7Bfactor%7D)*%5C%5C%5Ctext%7Bfactor%7D&%5Cto%5B(%5D%5Ctext%7Bexpr%7D%5B)%5D%5C;%7C%5C;%5Ctext%7Bprimary%7D%5C%5C%5Ctext%7Bprimary%7D&%5Cto%5Ctext%7Bnumber%7D%5C;%7C%5C;%5Ctext%7Bidentifier%7D%5Cend%7Balign*%7D$$>) -->

<!-- $$
\begin{align*}
\text{program} &\to \text{statement}* \text{ EOF} \\
\text{statement} &\to \text{return} \;|\; \text{varDecl} \\
\text{return} &\to [retourner]\text{ expr [;]} \\
\text{varDecl} &\to [soit]\text{ identifier [=] expr [;]} \\
\text{expr} &\to \text{arithmetic}\ ((\text{==}|\text{!=}|< |\leq |> |\geq )\text{ arithmetic})* \\
\text{arithmetic} &\to \text{term}\ (([+]|[-])\text{ term})* \\
\text{term} &\to \text{factor}\ (([*]|[/])\text{ factor})* \\
\text{factor} &\to [(]\text{ expr }[)] \;|\; \text{primary} \\
\text{primary} &\to \text{number} \;|\; \text{identifier}
\end{align*}
$$ -->

![grammar_latex_cogs](<https://latex.codecogs.com/png.image?%5Cinline%20%5Clarge%20%5Cdpi%7B150%7D%5Cbg%7Bblack%7D$$%5Cbegin%7Balign*%7D%5Ctext%7Bprogram%7D&%5Cto%5Ctext%7Bstatement%7D*%5Ctext%7BEOF%7D%5C%5C%5Ctext%7Bstatement%7D&%5Cto%5Ctext%7Breturn%7D%5C;%7C%5C;%5Ctext%7BvarDecl%7D%5C%5C%5Ctext%7Breturn%7D&%5Cto%5Bretourner%5D%5Ctext%7Bexpr%5B;%5D%7D%5C%5C%5Ctext%7BvarDecl%7D&%5Cto%5Bsoit%5D%5Ctext%7Bidentifier%5B=%5Dexpr%5B;%5D%7D%5C%5C%5Ctext%7Bexpr%7D&%5Cto%5Ctext%7Barithmetic%7D%5C((%5Ctext%7B==%7D%7C%5Ctext%7B!=%7D%7C%3C%7C%5Cleq%7C%3E%7C%5Cgeq)%5Ctext%7Barithmetic%7D)*%5C%5C%5Ctext%7Barithmetic%7D&%5Cto%5Ctext%7Bterm%7D%5C((%5B+%5D%7C%5B-%5D)%5Ctext%7Bterm%7D)*%5C%5C%5Ctext%7Bterm%7D&%5Cto%5Ctext%7Bfactor%7D%5C((%5B*%5D%7C%5B/%5D)%5Ctext%7Bfactor%7D)*%5C%5C%5Ctext%7Bfactor%7D&%5Cto%5B(%5D%5Ctext%7Bexpr%7D%5B)%5D%5C;%7C%5C;%5Ctext%7Bprimary%7D%5C%5C%5Ctext%7Bprimary%7D&%5Cto%5Ctext%7Bnumber%7D%5C;%7C%5C;%5Ctext%7Bidentifier%7D%5Cend%7Balign*%7D$$>)
