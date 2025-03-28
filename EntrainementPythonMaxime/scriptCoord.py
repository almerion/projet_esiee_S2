import csv
import requests
import numpy as np
import time

start_time = time.time()

tableauCoord = []
ville1adresse = "600 Rue des Madeleines"
ville1 = "Mareuil-lès-Meaux"
adresseTTville1 = ville1adresse + "," + ville1

# Récupérer les coordonnées de la première ville
try:
    response = requests.get(f"https://nominatim.openstreetmap.org/search?q={adresseTTville1}&format=json", headers={"User-Agent": "MyApp"})
    data = response.json()
    latitude = data[0]['lat']
    longitude = data[0]["lon"]
    coord = f"{latitude},{longitude}"
    tableauCoord.append(coord)
except requests.exceptions.RequestException as e:
    print(f"Erreur de requête pour la ville 1: {e}")


idx = 0
# Récupérer les coordonnées des autres villes depuis le fichier CSV
with open('livraison85.csv', newline='', encoding='utf-8') as file:
    reader = csv.reader(file)
    for row in reader:
        idx = idx+1
        print(idx)
        rue = row[1]
        ville = row[3]
        adresse = rue + "," + ville
        url = f"https://nominatim.openstreetmap.org/search?q={adresse}&format=json"

        try:
            response = requests.get(url, headers={"User-Agent": "MyApp"})
            data = response.json()

            if data:
                latitude = data[0]['lat']
                longitude = data[0]["lon"]
            else:
                url = f"https://nominatim.openstreetmap.org/search?q={ville}&format=json"
                response = requests.get(url, headers={"User-Agent": "MyApp"})
                response.raise_for_status()
                data = response.json()
                
                latitude = data[0]['lat'] if data else "N/A"
                longitude = data[0]["lon"] if data else "N/A"
                
            coord = f"{latitude},{longitude}"
            tableauCoord.append(coord)
        except requests.exceptions.RequestException as e:
            print(f"Erreur de requête pour la ville {ville}: {e}")
            
tailleTableauCoord = len(tableauCoord)
with open('tab_coord.csv', mode='w', newline='', encoding='utf-8') as file:
    writer = csv.writer(file)
    writer.writerow(list(tableauCoord))
