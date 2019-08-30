icons = {
    "green": "http://maps.google.com/mapfiles/ms/icons/green-dot.png",
    "blue": "http://maps.google.com/mapfiles/ms/icons/blue-dot.png",
    "red": "http://maps.google.com/mapfiles/ms/icons/red-dot.png"
}
halls = [
    {
        "name": "Leonard Dining Hall",
        "lat": 44.224267,
        "lng": -76.500690,
        "infobox": "",
        "icon": icons["blue"],
        "people": 0
    },
    {
        "name": "Ban Righ Dining Hall",
        "lat": 44.224628,
        "lng": -76.496264,
        "infobox": "",
        "icon": icons["blue"],
        "people": 0
    },
    {
        "name": "Jean-Royce Dining Hall",
        "lat": 44.224243,
        "lng": -76.515335,
        "infoBox": "",
        "icon": icons["blue"],
        "people": 0
    },
    {
        "name": "Lazy Scholar",
        "lat": 44.225633,
        "lng": -76.498783,
        "infobox": "",
        "icon": icons["green"],
        "people": 0
    },
    {
        "name": "Location 21",
        "lat": 44.223575,
        "lng": -76.498995,
        "infoBox": "",
        "icon": icons["green"],
        "people": 0
    },
    {
        "name": "The ARC",
        "lat": 44.229325,
        "lng": -76.494231,
        "infoBox": "",
        "icon": icons["green"],
        "people": 0
    },
    {
        "name": "The JDUC",
        "lat": 44.228472,
        "lng": -76.494675,
        "infoBox": "",
        "icon": icons["green"],
        "people": 0
    },
    {
        "name": "Tim Horton's (BioSci)",
        "lat": 44.226444,
        "lng": -76.491273,
        "infoBox": "",
        "icon": icons["green"],
        "people": 0
    },
    {
        "name": "Tim Horton's (BioSci)",
        "lat": 44.226444,
        "lng": -76.491273,
        "infoBox": "",
        "icon": icons["green"],
        "people": 0
    },
    {
        "name": "MC Square",
        "lat": 44.226615,
        "lng": -76.497020,
        "infoBox": "",
        "icon": icons["green"],
        "people": 0
    },
    {
        "name": "Market Street",
        "lat": 44.224566,
        "lng": -76.491620,
        "infoBox": "",
        "icon": icons["green"],
        "people": 0
    },
    {
        "name": "Market Street",
        "lat": 44.224566,
        "lng": -76.491620,
        "infoBox": "",
        "icon": icons["green"],
        "people": 0
    },
    {
        "name": "Recharge",
        "lat": 44.225394,
        "lng": -76.491291,
        "infoBox": "",
        "icon": icons["green"],
        "people": 0
    },
    {
        "name": "Goodes Hall",
        "lat": 44.228306,
        "lng": -76.497559,
        "infoBox": "",
        "icon": icons["green"],
        "people": 0
    },
    {
        "name": "Gord's Cafe",
        "lat": 44.223129,
        "lng": -76.500764,
        "infoBox": "",
        "icon": icons["green"],
        "people": 0
    }

]


def addPerson(latlng):
    people.append({
        "name": "",
        "lat": latlng[0],
        "lng": latlng[1],
        "infobox": "",
        "icon": icons["blue"],
    })

def remove(lat,lng):
    for v in people:
        if v["lat"] == lat and v["lng"] == lng:
            people.remove(v)
            break;

people = []
lat = 44.226122
lng = -76.495110

for p in halls:
    p["infobox"] = p["name"]
