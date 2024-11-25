% Facts
player(kohli).
player(dhoni).
player(rohit).
player(bumrah).
player(jadeja).
player(pant).
player(shami).
player(ishant).
player(rahul).
player(ashwin).

batsman(kohli).
batsman(dhoni).
batsman(rohit).
batsman(rahul).
batsman(pant).

bowler(bumrah).
bowler(jadeja).
bowler(shami).
bowler(ishant).
bowler(ashwin).

% Defining wicket-keepers
wicket_keeper(dhoni).
wicket_keeper(pant).


batting_average(kohli, 50).
batting_average(dhoni, 45).
batting_average(rohit, 40).
batting_average(bumrah, 15).
batting_average(jadeja, 35).
batting_average(pant, 38).
batting_average(rahul, 42).
batting_average(shami, 12).
batting_average(ishant, 10).
batting_average(ashwin, 30).

bowling_average(bumrah, 25).
bowling_average(kohli, 50).
bowling_average(dhoni, 55).
bowling_average(rohit, 60).
bowling_average(jadeja, 30).
bowling_average(pant, 100).
bowling_average(rahul, 80).
bowling_average(shami, 27).
bowling_average(ishant, 29).
bowling_average(ashwin, 24).

% Rules

% A player is considered a good batsman if they have a batting average >= 40.
is_batsman(Player) :-
    batsman(Player),
    batting_average(Player, Avg),
    Avg >= 40.

% A player is considered a good bowler if they have a bowling average < 31.
is_bowler(Player) :-
    bowler(Player),
    bowling_average(Player, Avg),
    Avg < 31.

% An all-rounder is a player who is both a good batsman and a good bowler.
is_all_rounder(Player) :-
    is_batsman(Player),
    is_bowler(Player).

% A wicket-keeper batsman is a player who is a batsman and has a specific role.
is_wicket_keeper(Player) :-
    batsman(Player),
    wicket_keeper(Player).

% A top-order batsman has a batting average >= 45.
is_top_order_batsman(Player) :-
    batsman(Player),
    batting_average(Player, Avg),
    Avg >= 45.

% A tailender is a bowler with a batting average < 20.
is_tailender(Player) :-
    bowler(Player),
    batting_average(Player, Avg),
    Avg < 20.
