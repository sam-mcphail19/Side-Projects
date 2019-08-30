from app import app, data
from flask import Flask, render_template
from flask_googlemaps import GoogleMaps
from flask_googlemaps import Map


@app.route('/')
@app.route('/index')
@app.route('/index/<lat>/<lng>')
def index(lat=-1,lng=-1):
    if not lng == -1:
        data.remove(lat, lng)
    return render_template('index.html')


@app.route("/map")
@app.route('/map/<lat>/<lng>')
def map(lat=-1,lng=-1):
    if not lng == -1:
        data.addPerson((lat,lng))
    myMap = Map(
        identifier="map",
        lat=data.lat,
        lng=data.lng,
        markers=data.people,
        zoom=16,
        style="height:600px;width:600px;margin:0 auto"
    )
    return render_template('map.html', mymap=myMap)


@app.route('/leonard')
def leonard():
    return render_template("leonard.html")


@app.route('/banrigh')
def banrigh():
    return render_template("banrigh.html")


@app.route('/jeanroyce')
def jeanroyce():
    return render_template("jeanroyce.html")

@app.route("/places")
def places():
    myMap = Map(
        identifier="map",
        lat=data.lat,
        lng=data.lng,
        markers=data.halls ,
        zoom=16,
        style="height:600px;width:600px;margin:0 auto"
    )
    return render_template("places.html", mymap=myMap)