import requests

adresse = "40 Rue de la Clef des Champs, Magny-le-Hongre"
url = f"https://nominatim.openstreetmap.org/search?q={adresse}&format=json"

response = requests.get(url, headers={"User-Agent": "MyApp"})
data = response.json()

if data:
    latitude = data[0]["lat"]
    longitude = data[0]["lon"]
    print(f"Coordonnées: lat : {latitude}, long : {longitude}")
else:
    print("Adresse non trouvée")
