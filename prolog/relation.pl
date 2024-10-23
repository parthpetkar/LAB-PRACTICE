:- initialization(main).
main :- 
        (father(ajay, bobby) -> write('yes father'), nl;
        write('no father'), nl),
        (mother(mary, lisa) -> write('yes mother'), nl;
        write('no mother'), nl),
        halt.

%Facts
male(ajay).
male(bobby).
male(chatur).
male(david).
male(akash).
female(emma).
female(lisa).
female(mary).
female(jerry).
female(miya).
parent(ajay,bobby).
parent(bobby,lisa).
parent(mary,jerry).
parent(jerry,lisa).
parent(akash,miya).
parent(ajay,david).



%Rules
father(X,Y):- parent(X,Y),
        male(X).

mother(X,Y):- parent(X,Y),
         female(X).

brother(X,Y):- parent(Z,X),
          parent(Z,Y),
          male(X),
          Y\==Z.

sister(X,Y):- parent(Z,X),
          parent(Z,Y),
          female(X),
          Y\==Z.

grandfather(X,Y):- father(X,Z),
              parent(Z,Y).