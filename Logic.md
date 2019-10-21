formal logic
* synatx
* semantics
* inference system
  
### Propositional logic
always include brackets to avoid ambuigity

(propositional)parser reads a string to tell whether is a (propositional) formula or not

e.g. ((p ^ q) v ~(q > r))
1. check the main connective is (v)
2. check 1st part (p ^ q)
3. check 2nd part ~(p > r)
(4.) check the right bracket

Note: Use recursion to check the subformula

logically equivalent a ≡ b




#### Propositional Tableaux

##### Features
* Given a propositional formula, it can tell you whether it is satisfiable or not

* If the tableau closes then the formula is __unsatisfiable__
* Note:   
  being at the root of an popen tableau is not enough to be considered satisfiable,
  maybe just not being fully decomposed

* If a branch contains p & ~p, then it is __closed__, otherwise it is __open__
* If every branch is closed, then the tableux is closed

* If the subformula is decomposed, it is ticked 
* A tableau is __complete__ if every node is either ticked or a literal
* If the formula at the root of a __complete open__ tableau, then itis __satisfiable__


##### Rules to decompose
In propositional logic
fmla := lit | ~lit  | 
        ~~fmla
        (fmla  v  fmla)
        (fmla  ^  fmla)
        (fmla  -> fmla)
       ~(fmla  v  fmla)
       ~(fmla  ^  fmla)
       ~(fmla  -> fmla)

[Tableaux rules](https://images.slideplayer.com/39/10967039/slides/slide_8.jpg)       
* α formula 
    * ~~fmla
    *  (fmla  ^  fmla)
    * ~(fmla  v  fmla)
    * ~(fmla  -> fmla)
* β formula
    *  (fmla  v  fmla)
    *  (fmla  -> fmla)
    * ~(fmla  ^  fmla)  
  
To justify the formula using α or β rule, just mind the main connective and negation

Note: In a proff system, we are more interested in validity, not just satisfiability
-->
φ is satisfiable <=> ~φ is not valid
φ is valid       <=> ~φ is not satisfiable
--> 
* Negate the given formula
* Using α or β to decompose
* Check if there are contradictions
* Check if every formulas are ticked
* Finally justify