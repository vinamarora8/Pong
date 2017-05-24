# PONG
===========================

Remember this? Oc

## Installation Instructions
1. Install ncurses: `sudo apt-get install libncurses5-dev libncursesw5-dev`
2. Compile pong.c: `gcc pong.c -o pong`
3. Run: `./pong`

### Notes
1. It currently runs only in 80x24 mode, So size your terminal accordinly

2. Tapping keys is preferred over holding down keys

3. Control layout:

| Controls |	Player a   |	Player b   |
| -------- |:-------------:|:-------------:|
| UP	   |	  'w'	   |	  'o'	   |
| DOWN	   |	  's'	   |	  'l'	   |
| QUIT	   |	  'q'	   |	  'q'	   |

## TODO
- [x] Bare bones
- [x] Scorekeeping bar
- [x] Scorekeeping mechanic
- [ ] Terminal size compatibility
- [x] Install instructions

### Future Features
- [ ] Level system
