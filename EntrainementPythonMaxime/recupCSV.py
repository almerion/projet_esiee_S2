import csv

# Ouvrir le fichier CSV
with open('livraison10.csv', newline='', encoding='utf-8') as file:
    reader = csv.reader(file)
    
    # Parcourir chaque ligne du fichier
    for row in reader:
        rue = row[1]
        ville = row[3]
        print(f"rue : {rue}, ville : {ville}") 
