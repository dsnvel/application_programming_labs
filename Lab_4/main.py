import json
import matplotlib.pyplot as plt
from scipy import stats


x_list: list = []  # Rating
y_list: list = []  # Count of symbols

with open('Cell_Phones_and_Accessories_5_copy.json', 'r') as file:
    file_data = json.load(file)

dict_elems: dict = {}
for i in range(len(file_data)):
    # print(int(file_data[i]['overall']), len(file_data[i]['reviewText']))
    if dict_elems.get(int(file_data[i]['overall'])) is None:
        dict_elems[int(file_data[i]['overall'])] = []
    dict_elems[int(file_data[i]['overall'])].append(len(file_data[i]['reviewText']))

dict_elems: dict = dict(sorted(dict_elems.items()))
lot_of_sym, less_of_sym = [], []
key_value: int = 300
for key in dict_elems.keys():
    dict_elems[key] = sorted(dict_elems[key])
    for i in range(len(dict_elems[key])):
        # print(dict_elems[key][i])
        if dict_elems[key][i] >= key_value:
            lot_of_sym.append(key)
        else:
            less_of_sym.append(key)
        x_list.append(key)
        y_list.append(dict_elems[key][i])

# print(dict_elems)
# print(len(x_list), len(y_list))
plt.title('Count of symbols depends of rating')
plt.xlabel('Rating')
plt.ylabel('Count of symbols')
plt.plot(x_list, y_list)
plt.show()

t_stat, p_value = stats.ttest_ind(lot_of_sym, less_of_sym)
print(f"T-stats: {t_stat}")
print(f"P-value: {p_value}")
if p_value < 0.05:
    print("Hypothesis about count of symbols depends of rating is wrong.")
else:
    print("Hypothesis about count of symbols depends of rating is true.")

