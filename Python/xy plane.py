list = []
for y in range(10):
    listy = []
    for x in range(10):
        listy.append()
x = 5
y = 4
max_x = 10
max_y = 10
endline = "  "
horizontal_legend = "  "
for row in reversed(range(max_y)) :
    layer = f"{row}|"
    if row == y :
        for column in range(max_x) :
            if column == x :
                layer += "()"
                endline += "--"
                horizontal_legend += f"{column} "
            else :
                layer += "  "
                endline += "--"
                horizontal_legend += f"{column} "
        print(layer)
    else :
        print(f"{row}|")
print(endline)
print(horizontal_legend)