import random
def randomlist(no_elem_list,max_value) :
    list = []
    for elem_list in range(0,no_elem_list):
        list.append(random.randint(0,max_value))
    return list
    
    
def bar_graph (no_elem_list,max_value) :
    list = randomlist(no_elem_list,max_value)
    endline = ""
    legend = ""
    for elem_list in range(0,no_elem_list):
        endline += "---"
        if elem_list < 10 :
            legend += f" {elem_list + 1} "
        else :
            legend += f"{elem_list + 1} "
    for layer in range(max_value,0,-1) :
        layer_print = ""
        for value in list :
            if value >= layer :
                layer_print += " | "
            else :
                layer_print += "   "
        print(layer_print)
    print(f"{legend}\n{endline}")
    
    
def cluster_graph (no_elem_list,max_value) :
    list = randomlist(no_elem_list,max_value)
    endline = ""
    legend = ""
    for elem_list in range(0,no_elem_list):
        endline += "---"
        if elem_list < 10 :
            legend += f" {elem_list + 1} "
        else :
            legend += f"{elem_list + 1} "
    for layer in range(max_value,0,-1) :
        layer_print = ""
        for value in list :
            if value == layer :
                layer_print += " o "
            else :
                layer_print += "   "
        print(layer_print)
    print(f"{legend}\n{endline}")  
    
    
def horizontal_chart_graph (no_elem_list,max_value) :
    legend_value = 1
    legend_string =""
    list = randomlist(no_elem_list,max_value)
    for value in list :
        string = ""
        column = 1
        while column <= value :
            string += "-"
            column += 1
        if legend_value < 10 :
            legend_string = f"  {legend_value}"
        elif legend_value < 100 :
            legend_string = f" {legend_value}"
        else :
            legend_string = f"{legend_value}"    
        legend_value += 1           
        print(f"{legend_string}|{string}")   
        
        
def horizontal_cluster_graph (no_elem_list,max_value) :
    legend_value = 1
    legend_string =""
    list = randomlist(no_elem_list,max_value)
    for value in list :
        string = ""
        for column in range(max_value + 1) :
            if column == value :
                string += "o"
            else :
                string += " "
        if legend_value < 10 :
            legend_string = f"  {legend_value}"
        elif legend_value < 100 :
            legend_string = f" {legend_value}"
        else :
            legend_string = f"{legend_value}"    
        legend_value += 1           
        print(f"{legend_string}|{string}")        
         
    
no_graph = 100
no_elem_list = 10
max_value = 30
for i in range(no_graph) :
    print(f"Graph number: {i + 1}")
    horizontal_cluster_graph(no_elem_list,max_value)