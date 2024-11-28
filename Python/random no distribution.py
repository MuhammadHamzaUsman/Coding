import random

no_of_sample = 1000
sample_size = 6
sample_result = {}
sample_values = []

for sample_element in range(1,sample_size + 1) :
    sample_result[sample_element] = 0

for sample in range(no_of_sample) :
    sample = []
    for i in range(1,sample_size + 1) :
        sample.append(random.randint(1,sample_size))
    for j in range(1,sample_size + 1) :
        count = sample.count(j)
        sample_result[j] += count

for value in sample_result.values():
    sample_values.append(value)

for element, value in sample_result.items():
    str = ""
    if element < 10 :
        str += f"0{element}: {value}"
    else :
        str += f"{element}: {value}"
    print(str)
    
print(f"diff b\w highest and lowest : {max(sample_values) - min(sample_values)}, {round(min(sample_values) / max(sample_values) * 100 , 2)}%")    