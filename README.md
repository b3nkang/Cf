<ins>**premièrement...en français. anglais ci-dessous.**</ins>

# Compilateur Cf (C-français)

Voici Cf, un compilateur en cours de développement qui forme un langage de programmation avec des mots-clés français et, actuellement, une syntaxe similaire à C. À l'avenir, l'intention est d'intégrer une syntaxe plus élégante inspirée de Python. Le compilateur génère du code assembleur x86_64 pour macOS.

## Fonctionnalités du Langage

Cf prend actuellement en charge:

- Déclarations et affectations de variables avec `soit` (équivalent sémantique approximatif de `let`)
- Opérations arithmétiques de base (+, -, \*, /)
- Opérations de comparaison (==, !=, <, <=, >, >=)
- Littéraux entiers
- Regroupement d'expressions avec parenthèses
- Références de variables dans les expressions
- Gestion des erreurs:
  - Détection des erreurs de syntaxe avec numéros de ligne et de colonne
  - Vérifications de redéclaration de variables
  - Détection d'utilisation de variables non définies
  - Détection de point-virgule manquant
  - Détection d'utilisation d'opérateur invalide
  - Protection contre le débordement de pile pour les expressions complexes
- Instructions de retour avec `retourner`

### Syntaxe

- Les variables sont déclarées avec le mot-clé `soit`
- Les instructions de retour utilisent le mot-clé `retourner`
- Les instructions doivent se terminer par un point-virgule
- Les expressions suivent les règles standard de précédence des opérateurs

### Précédence des Opérateurs (du plus haut au plus bas)

1. Parenthèses `()`
2. Multiplication et division `*`, `/`
3. Addition et soustraction `+`, `-`
4. Opérateurs de comparaison `==`, `!=`, `<`, `<=`, `>`, `>=`

## Exemples

### Arithmétique de Base

```Cf
retourner (((6 + 6) / 2) * 3) / 9 - 2;
```

Cet exemple démontre les expressions arithmétiques imbriquées et la précédence des opérateurs.

### Déclaration de Variables

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

Cet exemple calcule le carré de la distance entre deux points.

### Opérations de Comparaison

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

Cet exemple démontre tous les opérateurs de comparaison et les expressions composées.

### Fichiers de Référence

À la racine du dépôt se trouve une collection de fichiers `asm` et `.cf`, respectivement `tests1-4.asm` et `v1-4CfSample.cf` qui contiennent des extraits de code Cf et leurs fichiers assembleur compilés associés.

## Compilation et Exécution

### Prérequis

- gcc
- nasm
- Make
- macOS

### Compiler le Compilateur

```bash
make
```

### Compiler un Programme Cf

```bash
./cf input.cf
```

Cela générera un fichier assembleur nommé `test4.asm`.

### Exécuter le Pipeline de Compilation Complet

```bash
make full TEST_FILE_INPUT=votre_fichier.cf
```

Cela va:

1. Compiler votre programme Cf en assembleur
2. Assembler en fichier objet
3. Lier en exécutable
4. Exécuter le programme et afficher sa valeur de retour

### Nettoyer les Fichiers de Compilation

```bash
make clean
```

## Détails d'Implémentation

Le compilateur suit un pipeline de compilation traditionnel:

1. Analyse lexicale (tokenizer)
2. Analyse syntaxique (parseur à descente récursive)
3. Génération de l'AST
4. Génération de code (assembleur x86_64)

## Grammaire

![grammar_latex_cogs](<https://latex.codecogs.com/png.image?%5Cinline%20%5Clarge%20%5Cdpi%7B150%7D%5Cbg%7Bblack%7D$$%5Cbegin%7Balign*%7D%5Ctext%7Bprogram%7D&%5Cto%5Ctext%7Bstatement%7D*%5Ctext%7BEOF%7D%5C%5C%5Ctext%7Bstatement%7D&%5Cto%5Ctext%7Breturn%7D%5C;%7C%5C;%5Ctext%7BvarDecl%7D%5C%5C%5Ctext%7Breturn%7D&%5Cto%5Bretourner%5D%5Ctext%7Bexpr%5B;%5D%7D%5C%5C%5Ctext%7BvarDecl%7D&%5Cto%5Bsoit%5D%5Ctext%7Bidentifier%5B=%5Dexpr%5B;%5D%7D%5C%5C%5Ctext%7Bexpr%7D&%5Cto%5Ctext%7Barithmetic%7D%5C((%5Ctext%7B==%7D%7C%5Ctext%7B!=%7D%7C%3C%7C%5Cleq%7C%3E%7C%5Cgeq)%5Ctext%7Barithmetic%7D)*%5C%5C%5Ctext%7Barithmetic%7D&%5Cto%5Ctext%7Bterm%7D%5C((%5B+%5D%7C%5B-%5D)%5Ctext%7Bterm%7D)*%5C%5C%5Ctext%7Bterm%7D&%5Cto%5Ctext%7Bfactor%7D%5C((%5B*%5D%7C%5B/%5D)%5Ctext%7Bfactor%7D)*%5C%5C%5Ctext%7Bfactor%7D&%5Cto%5B(%5D%5Ctext%7Bexpr%7D%5B)%5D%5C;%7C%5C;%5Ctext%7Bprimary%7D%5C%5C%5Ctext%7Bprimary%7D&%5Cto%5Ctext%7Bnumber%7D%5C;%7C%5C;%5Ctext%7Bidentifier%7D%5Cend%7Balign*%7D$$>)

<ins>**now...in English:**</ins>

# Cf (C-french) Compiler

This is Cf, an in-progress compiler that forms a programming language with French keywords and, currently, C-like syntax. In the future, the intention is to integrate nicer Python-like syntax. The compiler generates x86_64 assembly code for macOS.

## Language Features

Cf currently supports:

- Variable declarations and assignments with `soit` (roughly sematically equivalent to `let`)
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

### Variable Declaration

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

### Reference Files

At the first level of the repository there are a collection of `asm` and `.cf` files, respectively `tests1-4.asm` and `v1-4CfSample.cf` which contain both Cf code snippets and their associated compiled assembly files.

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


