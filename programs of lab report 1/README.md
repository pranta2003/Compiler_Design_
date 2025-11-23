# Lex Lab Programs (10 Tasks)

- **Task 1** → `task1.l`
- **Task 2** → `task2.l`
- **Task 3** → `task3.l`
- **Task 4** → `task4.l`
- **Task 5** → `task5.l`
- **Task 6** → `task6.l`
- **Task 7** → `task7.l`
- **Task 8** → `task8.l`
- **Task 9** → `task9.l`
- **Task 10** → `task10.l`

## How to build & run (with flex + gcc)
For a task file like `task1.l`:
```bash
flex task1.l
gcc lex.yy.c -o task1
echo "your input here" | ./task1
```
On Windows (MSYS2/WSL) commands are similar.
