import requests

# Définissez vos coordonnées de départ et d'arrivée
start_point = "48.8588443,2.2943506"  # Coordonnées de Paris (exemple)
end_point = "51.5074,-0.1278"  # Coordonnées de Londres (exemple)

# Remplacez 'YOUR_API_KEY' par votre véritable clé API de GraphHopper
api_key = "14608b1e-9bf1-490d-80a7-624bfae5935f"

# URL de l'API GraphHopper pour l'itinéraire
url = f"https://graphhopper.com/api/1/route?point={start_point}&point={end_point}&vehicle=car&key={api_key}"

# Effectuer la requête GET
response = requests.get(url)

# Vérifiez si la requête a réussi (code 200)
if response.status_code == 200:
    # Analysez la réponse JSON
    data = response.json()
    if 'paths' in data:
        # La distance et la durée sont dans la première route trouvée
        route = data['paths'][0]
        distance = route['distance']  # Distance en mètres
        time = route['time']  # Durée en millisecondes

        print(f"Distance: {distance / 1000} km")  # Convertir en kilomètres
        print(f"Durée: {time / 60000} minutes")  # Convertir en minutes
    else:
        print("Aucune route trouvée.")
else:
    print(f"Erreur lors de la requête: {response.status_code}")
