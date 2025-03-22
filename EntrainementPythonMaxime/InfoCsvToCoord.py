import csv
import requests

idx = 0

ville1adresse = "600 Rue des Madeleines"
ville1 = "Mareuil-lès-Meaux"

with open('livraison10.csv', newline='', encoding='utf-8') as file:
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
                    response.raise_for_status()  # Vérifie aussi le statut de la réponse ici
                    data = response.json()

                    if data:
                        latitude = data[0]['lat']
                        longitude = data[0]["lon"]
                    else:
                        print(f"Problème avec la ville {ville}")
                        latitude = longitude = "N/A"
                idx = idx+1
            except requests.exceptions.RequestException as e:
                print(f"Erreur de requete {e}")
                latitude = longitude = "N/A"

            print(f"{idx}. | {adresse} | {latitude} | {longitude}")
        
