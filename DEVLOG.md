 ### Entry 1
**Date:** 2026-03-20  
**Entry Type:** Engineering Decision \
**Task worked on:** Tokenization \
**Issue or decision:** Deciding on how to split the input and what format to require. \
**Error message / symptom (if applicable):** N/A \
**What I tried:**  What I tried was what I ended up with. \
**Fix / resolution (or final decision):** I decided to split the input by spaces and evaluate the parenthesis 
differently as parenthesis aren't normally separated by spaces. \
**Commit(s):**  
tokenize() foundation
---

### Entry 2
**Date:** 2026-26-03  \
**Entry Type:** Engineering Decision  \
**Task worked on:**  evalPostfix\
**Issue or decision:**  Deciding how to evaluate the postfix with the ArrayStack\
**Error message / symptom (if applicable):**  N/A
**What I tried:**  This was done in one attempt.\
**Fix / resolution (or final decision):**  I create a stack and add numbers to it and do the 
operation found to the top two elements in the stack, we flip the numbers as the top number is always placed 
before in the equation than the number below it in the stack.\
**Commit(s):**  
evalPostfix()
---

### Entry 3
**Date:** 2026-03-28  \
**Entry Type:** Bug Fix \
**Task worked on:**  infixToPostfix \
**Issue or decision:**  Understanding how to evaluate infixToPostfix. \
**Error message / symptom (if applicable):**  Parenthesis weren't handled correctly. \
**What I tried:**  First I tried just swaping the operators and numbers but, that only worked in very niche scenarios
, so I ended up having to research how people convert infix to postfix and I found a website explaining what happens in
every possible path, so I could understand the idea better, https://csis.pace.edu/~wolf/CS122/infix-postfix.htm \
**Fix / resolution (or final decision):**  With this better understanding of what I needed to program I decided to use
the ArrayStack already created to allow for correct evaluation of the parenthesis to control where the operators are 
placed in the postfix. \
**Commit(s):**  
infixToPostfix \
infixToPostfix attempt-2 \
Corrected InfixToPostfix
---

### Entry 4
**Date:** 2026-03-29  
**Entry Type:** Edge Case
**Task worked on:**  ArrayStack's top and pop, empty cases \
**Issue or decision:**  Choosing how to handle calling on an empty stack. \
**Error message / symptom (if applicable):**  Caused a runtime error when called no edge case
**What I tried:**  I tried printing and returning but Token can't be returned as a nullptr or nullopt. \
**Fix / resolution (or final decision):**  I looked up error handling in C++ and cerr came up along with the standard 
library having an exit method that would just exit the program allowing for correct and safe error handling. \
**Commit(s):**  
Edge Case ArrayStack + InfixToPostfix with ArrayStack
---

### Entry 5
**Date:** 2026-03-30  
**Entry Type:** Bug Fix 
**Task worked on:**  isValidPostfix
**Issue or decision:**  How to interpret what is valid postfix. \
**Error message / symptom (if applicable):** Allowed invalid entries such as 7 - as postfix.  \
**What I tried:** Only allowing operators when operators < numbers + 1. \
**Fix / resolution (or final decision):**  I realized it should have been numbers - 1 > operators as previously given
one operator and one number it would allow it as 0 < 1 + 1 but with 1 - 1 > 0 it returns false matching postfixes conditions.
**Commit(s):**  
Corrected isValidPostfix
---

### Entry 6
**Date:** YYYY-MM-DD  
**Entry Type:** Bug Fix / Edge Case / Engineering Decision  
**Task worked on:**  
**Issue or decision:**  
**Error message / symptom (if applicable):**  
**What I tried:**  
**Fix / resolution (or final decision):**  
**Commit(s):**  
