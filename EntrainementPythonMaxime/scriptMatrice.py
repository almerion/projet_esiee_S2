import csv
import requests
import numpy as np
import time

start_time = time.time()

tableauCoord = []
tableau = np.empty((86, 86), dtype=object)
ville1adresse = "600 Rue des Madeleines"
ville1 = "Mareuil-lès-Meaux"
adresseTTville1 = ville1adresse + "," + ville1

try:
    response = requests.get(f"https://nominatim.openstreetmap.org/search?q={adresseTTville1}&format=json", headers={"User-Agent": "MyApp"})
    data = response.json()
    latitude = data[0]['lat']
    longitude = data[0]["lon"]
    coord = f"{latitude},{longitude}"
    tableauCoord.append(coord)
except requests.exceptions.RequestException as e:
    print(f"Erreur de requête pour la ville 1: {e}")

with open('livraison85.csv', newline='', encoding='utf-8') as file:
    reader = csv.reader(file)
    for row in reader:
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

api_key = "14608b1e-9bf1-490d-80a7-624bfae5935f"

def get_info(start_coord, end_coord):
    urlgraphhopper = f"https://graphhopper.com/api/1/route?point={start_coord}&point={end_coord}&vehicle=car&key={api_key}"
    time.sleep(1.5)
    try:
        response = requests.get(urlgraphhopper)
        data = response.json()
        if 'paths' not in data:
            print(f"Erreur API GraphHopper pour {start_coord} : {end_coord}: {data}")
            return [float('inf'), float('inf')]
        route = data['paths'][0]
        time_sec = route['time'] // 1000 // 60
        distance = route['distance'] / 1000.0 
        return [round(distance, 2), time_sec]
    except requests.exceptions.RequestException as e:
        print(f"Erreur avec l'API GraphHopper: {e}")
        return [float('inf'), float('inf')]

idx = 0
tailleTableauCoord = len(tableauCoord)
for i in range(tailleTableauCoord):
    for j in range(tailleTableauCoord):
        idx += 1
        print(idx)
        if i != j:
            infos = get_info(tableauCoord[i], tableauCoord[j])
            distance = infos[0]
            time_sec = infos[1]
            tableau[i][j] = f"{distance}:{time_sec}"
        else:
            tableau[i][j] = 0,0

with open('matrice_distances86_3.csv', mode='w', newline='', encoding='utf-8') as file:
    writer = csv.writer(file)
    for i in range(tailleTableauCoord):
        writer.writerow(list(tableau[i]))

print("\nMatrice des distances et temps (km, s) :")
for row in tableau:
    print(",".join(row))  

end_time = time.time()
print(f"\nTemps d'exécution du script: {end_time - start_time:.2f} secondes")
