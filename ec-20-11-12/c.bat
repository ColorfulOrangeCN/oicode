@echo off
:back
gen > hand.in
hand
move hand.out hand.ans
hand_sol
fc hand.ans hand.out
if not errorlevel 1 goto back
pause