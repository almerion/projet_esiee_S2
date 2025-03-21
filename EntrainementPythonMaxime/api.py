import requests

url = "https://jsonplaceholder.typicode.com/posts"

response = requests.get(url)

data = response.json()

print(data)

for el in data:
    print(f"id : {el['id']} - {el['title']} - {el['body']}")
    print("\n")
