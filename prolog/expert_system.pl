% Players
player(kohli). player(dhoni). player(rohit). player(bumrah).
player(jadeja). player(pant). player(shami). player(ishant).
player(rahul). player(ashwin).

% Roles
batsman(kohli). batsman(dhoni). batsman(rohit).
batsman(rahul). batsman(pant).

bowler(bumrah). bowler(jadeja). bowler(shami).
bowler(ishant). bowler(ashwin).

wicket_keeper(dhoni). wicket_keeper(pant).

% Batting averages
batting_average(kohli,50). batting_average(dhoni,45).
batting_average(rohit,40). batting_average(rahul,42).
batting_average(pant,38). batting_average(jadeja,35).
batting_average(ashwin,30). batting_average(bumrah,15).
batting_average(shami,12). batting_average(ishant,10).

% Bowling averages
bowling_average(bumrah,25). bowling_average(jadeja,30).
bowling_average(shami,27). bowling_average(ishant,29).
bowling_average(ashwin,24). bowling_average(kohli,50).
bowling_average(dhoni,55). bowling_average(rohit,60).
bowling_average(rahul,80). bowling_average(pant,100).

% Good batsman
good_batsman(P) :-
    batsman(P),
    batting_average(P,Avg),
    Avg >= 40.

% Good bowler
good_bowler(P) :-
    bowler(P),
    bowling_average(P,Avg),
    Avg < 30.

% All-rounder
all_rounder(P) :-
    batting_average(P,Bat),
    bowling_average(P,Bowl),
    Bat >= 35,
    Bowl =< 30.

% Wicket keeper (with batting ability)
good_wicket_keeper(P) :-
    wicket_keeper(P),
    batting_average(P,Avg),
    Avg >= 35.

% Tailender
tailender(P) :-
    bowler(P),
    batting_average(P,Avg),
    Avg < 20.

select_player(P) :- good_batsman(P).
select_player(P) :- good_bowler(P).
select_player(P) :- all_rounder(P).
select_player(P) :- good_wicket_keeper(P).

team(List) :-
    setof(P, select_player(P), List).

why(P, "Selected as top batsman") :-
    good_batsman(P).

why(P, "Selected as top bowler") :-
    good_bowler(P).

why(P, "Selected as all-rounder") :-
    all_rounder(P).

why(P, "Selected as wicket-keeper") :-
    good_wicket_keeper(P).

