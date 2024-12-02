## grammar

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
