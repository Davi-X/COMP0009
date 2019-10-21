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